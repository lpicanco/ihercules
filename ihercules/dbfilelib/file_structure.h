#pragma once

#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef struct ihs_table ihs_table;
typedef struct ihs_field ihs_field;

// Estrutura do header do arquivo.
typedef struct
{
    uchar signature[4];         // Asinatura do arquivo "ihs".
    ushort version;             // Versão do arquivo.
    ushort table_count;         // Número de tabelas no arquivo.
    uint offset_table_pages;    // Ponteiro para o descritor de tabelas.
    uint offset_free_pages;     // Ponteiro para as páginas vazias.
    ushort page_size;           // Tamanho da página.
    uint page_count;            // Número de páginas utilizadas.
} ihs_header;

// Estrutura do descritor de tabelas.
typedef struct
{
    char name[31];              // Nome da tabela.
    ushort field_count;         // Número de campos.
    uint offset_field_pages;    // Ponteiro para o descritor de campos.
    uint offset_data_pages;     // Ponteiro para os dados da tabela.
} ihs_table_page;

// Estrutura do descritor de campos.
typedef struct
{
    uchar name[31];         // Nome do campo.
    uchar type;             // Tipo do campo.
    uint size;              // Tamanho do campo.
} ihs_field_page;

// Estrutura dos dados.
typedef struct
{
    uint offset_next_page;
    uint length;        // Tamanho dos dados.
} ihs_data_page;

// Estruturas auxiliares.
struct ihs_field
{
    ihs_field *prior;
    ihs_field *next;
    ihs_field_page descriptor;
};

struct ihs_table
{
    ihs_table *prior;
    ihs_table *next;
    ihs_table_page descriptor;
    ihs_field first_field;
    ihs_data_page data;
};

// Estrutura do banco de dados em memória.
typedef struct
{
    ihs_header header;     // Ponteiro para o header do banco de dados.
    ihs_table first_table;    // Primeira tabela do banco de dados.
    FILE *database;                 // Handler do arquivo de banco de dados.
    char *file_name;          // Nome do arquivo de banco de dados.
} database_descriptor;

/************************************************************************/
/* Tamanho dos tipos de dados                                           */
/************************************************************************/
/*  Size of uchar: 1
 *  Size of ushort: 2
 *  Size of uint: 4
 *  Size of char: 1
 */