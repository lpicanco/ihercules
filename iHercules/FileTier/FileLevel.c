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

    // Página anterior.
    uint priorPage = 0;

    //Executa o laço enquanto existirem tabelas para escrever.
    while(ptr != NULL)
    {      
        // Espaço ocupado por cada descritor de tabela.
        ushort tableSize = sizeof(struct TableDescriptor);

        // Se ainda não foi setado a página da tabela, significa que é nova.
        if (ptr->PageNumber == 0)
        {            
            // Verifica se existe uma tabela anterior e se existe espaço suficiente.
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
                // Pega uma nova página.
                ptr->PageNumber = newPage(db);

                if (ptr->Prior != NULL)
                    ptr->Prior->TableDesc.OffsetNextPage = ptr->PageNumber;
            }

            priorPage = ptr->PageNumber;
        };

        // Grava no arquivo.
        fseek(db->File, ptr->PageNumber, SEEK_SET);
        fwrite(&ptr->TableDesc, tableSize, 1, db->File);

        // Vai para a próxima tabela.
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
            // Se ainda não existe uma página definida, é porque é novo.
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
                    // Pega uma nova página.
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
        // Recupera a página requisitada.
    } else
    {
        // Cria uma nova página.
        page = (db->DBHeader.PageCount * db->DBHeader.PageSize) + 1;
        
        // Atualiza informações de páginas.
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