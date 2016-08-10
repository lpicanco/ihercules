/* dbfile.h - Fun�oes de acesso ao arquivo de banco de dados.
 *
 * Luiz Antonio Gomes Pican�o
 */

#pragma once

#include "file_structure.h"

// Cria uma nova p�gina.
uint new_page(database_descriptor *db);


// Grava o header no banco de dados.
void write_file(database_descriptor *db);

// Inicializa o banco de dados.
database_descriptor *db_init(void);