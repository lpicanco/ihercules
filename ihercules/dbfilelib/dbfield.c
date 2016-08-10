#include "dbfield.h"

#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

ihs_field *get_last_field(ihs_table *ptr_table);

ihs_field *create_field(ihs_table *ptr_table, ihs_field_page *ptr_field)
{
    ihs_field *ptr = NULL;

    if (ptr_table->descriptor.field_count == 0)
    {
        ptr = &ptr_table->first_field;
    }
    else
    {                    
        // Pega o �ltimo campo.
        ihs_field *ptr_last = get_last_field(ptr_table);        

        // Cria um novo objeto campo e ajusta encadeamento.
        ptr_last->next = calloc(1, sizeof(ihs_field));
        ptr = ptr_last->next;

        ptr->prior = ptr_last;
    }

    memcpy(&ptr->descriptor, ptr_field, sizeof(ihs_field_page));
    ptr_table->descriptor.field_count++;

    return ptr;
}

// Retorna a �ltima p�gina.
ihs_field *get_last_field(ihs_table *ptr_table)
{
    ihs_field *ptr = &ptr_table->first_field;

    // Busca o �ltimo campo.
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    return ptr;
}

// Cria uma nova p�gina para o campo.
uint new_field_page(database_descriptor *db, ihs_table *ptr_table)
{
    uint page = -1;
    ihs_field *field_ptr = get_last_field(ptr_table);

    // Cria uma nova p�gina.
    page = new_page(db);

     // Ajusta encadeamento das p�ginas.
    ptr_table->descriptor.offset_field_pages = page;

    return page;
}