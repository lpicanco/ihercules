/* dbtable.h - Funçoes de gerenciamento de tabelas no banco de dados.
*
* Luiz Antonio Gomes Picanço
*/

#pragma once

#include "file_structure.h"
#include "dbfile.h"
#include "dbtable.h"
#include "dbfield.h"

// Cria uma nova tabela no banco de dados.
ihs_table *create_table(database_descriptor *db, ihs_table_page *ptr_table);