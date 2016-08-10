#include "TestInsert.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "../FileTier/FileLevel.h"
#include "../FileTier/FileStructure.h"

void FillHeaders(struct DatabaseDescriptor *db);
void FillTables(struct DatabaseDescriptor *db);
void FillField(struct DatabaseDescriptor *db, struct Table *ptr);
uint newPages(struct DatabaseDescriptor *db);


void buildData(struct DatabaseDescriptor *db)
{
    FillHeaders(db);
    FillTables(db);

    writeDB(db);
}


void TestInsert(char *pszFileName)
{
    struct DatabaseDescriptor db;

    db.pszFileName = pszFileName;
    if ((db.File = fopen(db.pszFileName, "wb")) != NULL)
    {
        //buildData(&db);

    } else
    {
        printf("Erro ao abrir arquivo");
        getchar();
    }
}

void FillHeaders(struct DatabaseDescriptor *db)
{    
    struct Header *ptr = &db->DBHeader;

    ptr->OffsetFreePages = 0;
    ptr->PageCount = 1;
    ptr->PageSize = 128;
    strcpy(ptr->Signature, "ihs");
    ptr->TableCount = 3;
    ptr->Version = 1;
    ptr->OverflowPage = 0;
    ptr->OffsetTablesData = newPages(db);
}

void FillTables(struct DatabaseDescriptor *db)
{
    struct Table *ptr = &db->FirstTable;
    
    ptr->PageNumber = 0;
    ptr->Prior = 0;
    ptr->TableDesc.FieldCount = 2;
    ptr->TableDesc.OffsetFieldsData = newPages(db);
    ptr->TableDesc.OffsetPriorPage = 0;
    ptr->TableDesc.OverflowPage = 0;
    ptr->TableDesc.PageOffset = 0;
    strcpy(ptr->TableDesc.TableName, "Usuario");
    FillField(db, ptr);

    ptr->Next = malloc(sizeof(struct Table));
    ptr->Next->Prior = ptr;
    ptr = ptr->Next;
    
    ptr->PageNumber = 0;
    ptr->TableDesc.FieldCount = 2;
    ptr->TableDesc.OffsetFieldsData = newPages(db);
    ptr->TableDesc.OffsetPriorPage = 0;
    ptr->TableDesc.OverflowPage = 0;
    ptr->TableDesc.PageOffset = 0;
    strcpy(ptr->TableDesc.TableName, "Cliente");
    FillField(db, ptr);

    ptr->Next = malloc(sizeof(struct Table));
    ptr->Next->Prior = ptr;
    ptr = ptr->Next;

    ptr->PageNumber = 0;
    ptr->TableDesc.FieldCount = 2;
    ptr->TableDesc.OffsetFieldsData = newPages(db);
    ptr->TableDesc.OffsetPriorPage = 0;
    ptr->TableDesc.OverflowPage = 0;
    ptr->TableDesc.PageOffset = 0;
    strcpy(ptr->TableDesc.TableName, "Teste");
    FillField(db, ptr);
}

void FillField(struct DatabaseDescriptor *db, struct Table *ptr)
{
    return;
}

uint newPages(struct DatabaseDescriptor *db)
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


/************************************************************************/
/* Tabela: "Usuario"                                                    */
/* Campo: "id"    - Tipo: INT                                           */
/* Campo: "Login" - Tipo: VARCHAR(15)                                   */
/* Valores: (1, luiz), (2,teste), (3,teste3)                            */
/************************************************************************/
/* Tabela: "Cliente"                                                    */
/* Campo: "id"    - Tipo: INT                                           */
/* Campo: "Nome" - Tipo: VARCHAR(50)                                    */
/************************************************************************/
/* Tabela: "Teste"                                                      */
/* Campo: "id"    - Tipo: INT                                           */
/* Campo: "Login" - Tipo: VARCHAR(15)                                   */
/************************************************************************/
