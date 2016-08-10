#include "../dbfilelib/file_structure.h"
#include "../dbfilelib/dbtable.h"
#include "../dbfilelib/dbfield.h"
#include "../dbfilelib/dbfile.h"

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

void main()
{
    database_descriptor *db = NULL;

    ihs_table *tb;
    ihs_table_page *table;
    ihs_field_page field;
    
    table = calloc(1, sizeof(ihs_table_page));

    db = db_init();
    db->file_name = "c:\\temp\\teste.ihs";

    
    if ((db->database = fopen(db->file_name, "wb")) != NULL)
    {
        int i;
        db->header.page_size = 4096;

        for (i = 0; i < 3; i++)
        {
            strcpy(table->name, "usuario");

            // Cria tabela.
            tb = create_table(db, table);
            
            strcpy(field.name, "login");    
            field.type = 3;
            field.size = 15;

            create_field(tb, &field);
            
            strcpy(field.name, "senha");
            field.type = 2;
            field.size = 13;

            create_field(tb, &field);
        }

        write_file(db);

        fclose(db->database);
    } else
        printf("Impossível abrir arquivo !!!\n");

    free(db);
    free(table);
}