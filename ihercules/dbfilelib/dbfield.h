/* dbfield.h - Funçoes de gerenciamento de campos no banco de dados.
*
* Luiz Antonio Gomes Picanço
*/

#pragma once

#include "file_structure.h"
#include "dbfile.h"

// Cria um nova campo na tabela do banco de dados.
ihs_field *create_field(ihs_table *ptr_table, ihs_field_page *ptr_field);

// Cria uma nova página para o campo.
uint new_field_page(database_descriptor *db, ihs_table *ptr_table);
