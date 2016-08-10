#include "FileLevel.h"
#include <stdio.h>

int writeHeader(struct DatabaseDescriptor *db)
{
    fseek(db->File, 1, SEEK_SET);
    fwrite(&db->DBHeader, sizeof(db->DBHeader), 1, db->File);
    
    return 0;
}

int writeTables(struct DatabaseDescriptor *db)
{
    // Aponta para a primeira tabela.
    struct Table *ptr = &db->FirstTable;

    // P�gina anterior.
    uint priorPage = 0;

    //Executa o la�o enquanto existirem tabelas para escrever.
    while(ptr != NULL)
    {      
        // Espa�o ocupado por cada descritor de tabela.
        ushort tableSize = sizeof(struct TableDescriptor);

        // Se ainda n�o foi setado a p�gina da tabela, significa que � nova.
        if (ptr->PageNumber == 0)
        {            
            // Verifica se existe uma tabela anterior e se existe espa�o suficiente.
            if (ptr->Prior != NULL)
            {
                if (db->DBHeader.PageSize - ptr->Prior->TableDesc.PageOffset >= (tableSize * 2) - 1)
                {
                    ptr->TableDesc.PageOffset = ptr->Prior->TableDesc.PageOffset + tableSize - 1;
                    ptr->PageNumber = ptr->Prior->PageNumber;
                    priorPage = ptr->Prior->TableDesc.OffsetPriorPage;
                }
            }
            
            ptr->TableDesc.OffsetPriorPage = priorPage;

            if (ptr->PageNumber == 0)
            {
                // Pega uma nova p�gina.
                ptr->PageNumber = newPage(db);

                if (ptr->Prior != NULL)
                    ptr->Prior->TableDesc.OffsetNextPage = ptr->PageNumber;
            }

            priorPage = ptr->PageNumber;
        };

        // Grava no arquivo.
        fseek(db->File, ptr->PageNumber, SEEK_SET);
        fwrite(&ptr->TableDesc, tableSize, 1, db->File);

        // Vai para a pr�xima tabela.
        ptr = ptr->Next;
    }
    
    return 0;
}

int writeFields(struct DatabaseDescriptor *db)
{
    // Aponta para a primeira tabela.
    struct Table *ptrTable = &db->FirstTable;

    // Tamanho do descritor de campos.
    ushort fieldSize = sizeof(struct FieldDescriptor);

    uint priorPage = 0;

    //Realiza um loop por totas as tabelas.
    while(ptrTable != NULL)
    {
        // Aponta para o primeiro campo.
        struct Field *ptr = &ptrTable->FirstField;   

        //Realiza um loop por totos os campos.
        while(ptr != NULL)
        {
            // Se ainda n�o existe uma p�gina definida, � porque � novo.
            if (ptr->PageNumber == 0)
            {
                if (ptr->Prior != NULL)
                {
                    if (db->DBHeader.PageSize - ptr->FieldDesc.PageOffset >= (fieldSize * 2) - 1)
                    {
                        ptr->FieldDesc.PageOffset = ptr->Prior->FieldDesc.PageOffset + fieldSize - 1;
                        ptr->PageNumber = ptr->Prior->PageNumber;
                        priorPage = ptr->Prior->FieldDesc.OffsetPriorPage;
                    }
                }

                ptr->FieldDesc.OffsetPriorPage = priorPage;

                if (ptr->PageNumber == 0)
                {
                    // Pega uma nova p�gina.
                    ptr->PageNumber = newPage(db);

                    if (ptr->Prior != NULL)
                        ptr->Prior->FieldDesc.OffsetNextPage = ptr->PageNumber;
                }

            }

            // Grava no arquivo.
            fseek(db->File, ptr->PageNumber, SEEK_SET);
            fwrite(&ptr->FieldDesc, fieldSize, 1, db->File);
            ptr = ptr->Next;
        }
        
        ptrTable = ptrTable->Next;
    }

    return 0;
}

uint newPage(struct DatabaseDescriptor *db)
{
    uint page = -1;

    if (db->DBHeader.OffsetFreePages != 0)
    {
        // TODO: Implementar.
        // Recupera a p�gina requisitada.
    } else
    {
        // Cria uma nova p�gina.
        page = (db->DBHeader.PageCount * db->DBHeader.PageSize) + 1;
        
        // Atualiza informa��es de p�ginas.
        db->DBHeader.PageCount++;
    }

    return page;
}

void initData(struct DatabaseDescriptor *db)
{
    db->DBHeader.OffsetFreePages = 0;
    db->DBHeader.OffsetTablesData = 0;
    db->DBHeader.OverflowPage = 0;
    db->DBHeader.PageCount = 0;
    db->DBHeader.PageSize = 0;
    db->DBHeader.TableCount = 0;
    db->DBHeader.Version = 0;
    db->Tables = NULL;   
    
    db->FirstTable.Fields = NULL;
}

int writeDB(struct DatabaseDescriptor *db)
{
    // Escreve as tabelas.
    if (writeTables(db) != 0)
        return -1;

    // Escreve os campos.
    if (writeFields(db) !=0)
        return -1;

    // Escreve o header.
    if (writeHeader(db) != 0)
        return -1;

    return 0;
}

void main()
{
}