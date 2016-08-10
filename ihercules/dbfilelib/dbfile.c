/* dbfile.c
*
* Luiz Antonio Gomes Picanço
*/

#include "dbfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

void write_header(database_descriptor *db);
void write_tables(database_descriptor *db);
void write_fields(database_descriptor *db, ihs_table *ptr_table);

database_descriptor *db_init(void)
{
    database_descriptor *db = calloc(1, sizeof(database_descriptor));

    db->header.page_count = 1;
    strcpy(db->header.signature, "ihs");
    db->header.version = 1;

    return db;
}

void write_file(database_descriptor *db)
{
    write_header(db);
    write_tables(db);
}

void write_header(database_descriptor *db)
{
    fseek(db->database, 0, SEEK_SET);
    fwrite(&db->header, sizeof(db->header), 1, db->database);
}

void write_tables(database_descriptor *db)
{
    ihs_table *ptr = &db->first_table;
    fpos_t file_pos;

    // Posiciona o arquivo na primeira tabela.
    fseek(db->database, db->header.offset_table_pages, SEEK_SET);

    while (ptr != NULL)
    {       
        // Grava dados da tabela.
        fwrite(&ptr->descriptor, sizeof(ptr->descriptor), 1, db->database);

        // Salva posição atual no arquivo.
        fgetpos(db->database, &file_pos);

        // Grava campos.
        write_fields(db, ptr);

        // Restaura posição do arquivo.
        fsetpos(db->database, &file_pos);

        ptr = ptr->next;
    }
}

void write_fields(database_descriptor *db, ihs_table *ptr_table)
{
    ihs_field *ptr = &ptr_table->first_field;
    
    // Posiciona o arquivo no primeiro campo.
    fseek(db->database, ptr_table->descriptor.offset_field_pages, SEEK_SET);    

    while (ptr != NULL)
    {
        // Grava dados do campo.
        fwrite(&ptr->descriptor, sizeof(ptr->descriptor), 1, db->database);

        ptr = ptr->next;
    }
}

void write_data(database_descriptor *db, ihs_table *ptr_table)
{
    
}


uint new_page(database_descriptor *db)
{
    uint page = -1;

    if (db->header.offset_free_pages != 0)
    {
        // TODO: Implementar.
        // Recupera a página requisitada.
    } else
    {
        // Cria uma nova página.
        page = (db->header.page_count * db->header.page_size) + 1;

        // Atualiza informações de páginas.
        db->header.page_count++;
    }

    return page;
}