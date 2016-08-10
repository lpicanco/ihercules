#include "dbtable.h"

#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

ihs_table *get_last_table(database_descriptor *db);
uint new_table_page(database_descriptor *db);

ihs_table *create_table(database_descriptor *db, ihs_table_page *ptr_table)
{    
    ihs_table *ptr = NULL;

    if (db->header.table_count == 0)
    {
        ptr = &db->first_table;
        new_table_page(db);
    }
    else
    {                    
        // Pega a última tabela.
        ihs_table *ptr_last = get_last_table(db);        

        // Cria um novo objeto tabela e ajusta encadeamento.
        ptr_last->next = calloc(1, sizeof(ihs_table));
        ptr = ptr_last->next;

        ptr->prior = ptr_last;
    }

    memcpy(&ptr->descriptor, ptr_table, sizeof(ihs_table_page));
    db->header.table_count++;
    
    // Cria página para os campos.
    new_field_page(db, ptr);

    // TODO: Ajustar os espaços de dados.

    return ptr;
}

uint new_table_page(database_descriptor *db)
{
    uint page = -1;
    ihs_table *table_ptr = get_last_table(db);

    // Cria uma nova página.
    page = new_page(db);
    
    // Ajusta encadeamento das páginas.
    db->header.offset_table_pages = page;

    return page;
}

// Retorna a última página.
ihs_table *get_last_table(database_descriptor *db)
{
    ihs_table *ptr = &db->first_table;

    // Busca a última tabela.
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    return ptr;
}