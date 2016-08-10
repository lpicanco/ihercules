/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "../FileTier/FileStructure.h"
    
void WriteToFile(FILE *pszFile);
void FillData(struct DatabaseDescriptor *db);
void FillFields(struct DatabaseDescriptor *db);

void WriteFileDescriptor(const char *pszFileName)
{
    FILE *arq;

    if ((arq = fopen(pszFileName, "wb")) != NULL)
    {
        WriteToFile(arq);

        fclose(arq);
    } else
    {
        printf("Erro tentando criar o arquivo %s.\n", pszFileName);
        getchar();
    }

}

void WriteToFile(FILE *ptrFile)
{
    struct DatabaseDescriptor db;
    db.File = ptrFile;

    FillData(&db);

    // Grava o header.
    fwrite(&db.DBHeader, sizeof(db.DBHeader), 1, ptrFile);

    // Grava as tabelas.
    fseek(ptrFile, db.DBHeader.OffsetTablesData, SEEK_SET);
    fwrite(&db.FirstTable.TableDesc, sizeof(struct TableDescriptor), 1, ptrFile);

    // Grava os campos.
    fseek(ptrFile, db.FirstTable.TableDesc.OffsetFieldsData, SEEK_SET);
    fwrite(&db.FirstTable.FirstField.FieldDesc, sizeof(struct FieldDescriptor), 1, ptrFile);
    fwrite(&db.FirstTable.FirstField.Next->FieldDesc, sizeof(struct FieldDescriptor), 1, ptrFile);
    fseek(ptrFile, (db.DBHeader.PageCount * db.DBHeader.PageSize) - 1, SEEK_SET);
    fwrite("\0", 1, 1, ptrFile);
}

void FillData(struct DatabaseDescriptor *db)
{
    /************************************************************************/
    /* Tabela: "Usuario"                                                    */
    /* Campo: "id"    - Tipo: INT                                           */
    /* Campo: "Login" - Tipo: VARCHAR(15)                                   */
    /************************************************************************/

    // Preenchendo Header. 
/*    strcpy(db->DBHeader.Signature, "ihs");
    db->DBHeader.Version = 1;
    db->DBHeader.TableCount = 1;
    db->DBHeader.PageSize = 1024;
    db->DBHeader.OffsetFreePages = 0;
    db->DBHeader.OffsetTablesData = db->DBHeader.PageSize + 1;
    db->DBHeader.PageCount = 2;
    db->DBHeader.OverflowPage = 0;

    // Preenchendo Tabela.
    db->FirstTable.Next = NULL;
    db->FirstTable.Prior = NULL;
    db->Tables = &db->FirstTable;
    db->FirstTable.Fields = &db->FirstTable.FirstField;
    db->FirstTable.FirstField.Prior = NULL;
    db->FirstTable.FirstField.Next = NULL;

    db->FirstTable.TableDesc.OffsetNextPage = 0;
    db->FirstTable.TableDesc.OffsetPriorPage = 0;
    strcpy(db->FirstTable.TableDesc.TableName, "Login");
    db->FirstTable.TableDesc.FieldCount = 2;
    db->FirstTable.TableDesc.OffsetFieldsData = (db->DBHeader.PageCount * db->DBHeader.PageSize) + 1;
    db->DBHeader.PageCount++;
    db->FirstTable.TableDesc.OffsetTableData = 0;
    db->FirstTable.TableDesc.OverflowPage = 0;
    
    // Preenchendo os campos.
    FillFields(db);    
}    

void FillFields(struct DatabaseDescriptor *db)
{
    struct Field *ptr = db->FirstTable.Fields;

    // Preenchendo o primeiro campo.
    ptr->FieldDesc.OffsetNextPage = 0;
    ptr->FieldDesc.OffsetPriorPage = 0;
    strcpy(ptr->FieldDesc.FieldName, "id");
    ptr->FieldDesc.FieldType = 1; // INT
    ptr->FieldDesc.FieldSize = 0;
    strcpy(ptr->FieldDesc.Reserved, "");
    strcpy(ptr->FieldDesc.Reserved2, "");
    ptr->FieldDesc.OverflowPage = 0;

    // Preenchendo o segundo campo.
    ptr->Next = malloc(sizeof(struct Field));
    ptr = ptr->Next;
    ptr->Prior = &db->FirstTable.FirstField;
    ptr->FieldDesc.OffsetNextPage = 0;
    ptr->FieldDesc.OffsetPriorPage = 0;
    strcpy(ptr->FieldDesc.FieldName, "Usuario");
    ptr->FieldDesc.FieldType = 3; // VARCHAR
    ptr->FieldDesc.FieldSize = 15;
    strcpy(ptr->FieldDesc.Reserved, "");
    strcpy(ptr->FieldDesc.Reserved2, "");
    ptr->FieldDesc.OverflowPage = 0;
}

*/