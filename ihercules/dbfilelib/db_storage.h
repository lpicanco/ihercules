#pragma once

#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef struct ihs_table ihs_table;
typedef struct ihs_field ihs_field;

/************************************************************************/
/* Estrutura do arquivo de banco de dados.                              */
/************************************************************************/
// Estrutura do header do arquivo.
typedef struct
{
    uchar signature[4];                 // Asinatura do arquivo "ihs".
    ushort version;                     // Vers�o do arquivo.
    ushort table_count;                 // N�mero de tabelas no arquivo.
    uint offset_table_descriptor;       // Offset do descritor de tabelas.
    uint offset_free_space_descriptor;  // Offset do descritor de espa�os vazios.
} ihs_header;

// Estrutura do descritor de tabelas.
typedef struct
{
    char name[31];                  // Nome da tabela.
    ushort field_count;             // N�mero de campos.
    uint offset_field_descriptor;   // Offset do descritor de campos.
    uint offset_data_descriptor;    // Offset do descritor de dados.
    uint offset_next;               // Offset do pr�ximo descritor de tabelas.
} ihs_table_descriptor;

// Estrutura do descritor de campos.
typedef struct
{
    uchar name[31];     // Nome do campo.
    uchar type;         // Tipo do campo.
    uint size;          // Tamanho do campo.
    uint offset_next;   // Offset do pr�ximo descritor de campos.
} ihs_field_descriptor;

typedef struct 
{
    uint offset_table_data; // Offset para os dados.
    uint offset_next;       // Offset do pr�ximo descritor de dados.
} ihs_data_descriptor;

typedef struct 
{
    ushort data_length;     // Tamanho do dado.
    char *data;             // Conte�do dos dados.
} ihs_table_data;

typedef struct 
{
    uint offset_free_space; // Offset do in�cio do espa�o livre.
    uint length;            // Tamanho do espa�o livre.
    uint offset_next;       // Offset do pr�ximo descritor de espa�o livre.
} ihs_free_space_descriptor;


/************************************************************************/
/* Estruturas de apoio                                                  */
/************************************************************************/

typedef struct {
    ihs_header header;      // Header do arquivo.
    struct 
    {
        ihs_table_descriptor *first_table;   // Primeira tabela.
        ihs_table_descriptor *last_table;    // �ltima tabela.
    } tables;               // Ponteiros para a primeira e �ltima tabela.   

} ihs_database;