/************************************************************************/
/* iHércules - versão 0.0.0.1                                           */
/* file_spec.h - Especificação do formato do arquivo.                   */
/* Luiz Antonio Gomes Picanço - www.luizantonio.com                     */
/************************************************************************/

#pragma once

#include "types.h"
#include <stdio.h>

typedef struct _ihs_db_header
{
    byte signature[3];
    ushort file_version;
    ushort table_count;
} ihs_db_header;

typedef struct _ihs_table_header
{
    byte name[30];
    ushort field_count;
} ihs_table_header;

typedef struct _ihs_field_header
{
    byte name[30];
    byte type;
    uint length;
} ihs_field_header;

typedef struct _ihs_data_header
{
    byte deleted;
    ushort field_count;
} ihs_data_header;


typedef struct _database
{
    ihs_db_header header;
    ihs_table_header table;
    ihs_field_header first_field;
    ihs_field_header *next_field;
    FILE *db_file;
} database;

