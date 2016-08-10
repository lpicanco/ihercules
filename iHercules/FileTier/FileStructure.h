// FileStructure.h: File Structure Definitions
//////////////////////////////////////////////////////////////////////
#if !defined(FileStructure_h)
#define FileStructure_h

#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

// Etrutura do header do arquivo.
struct Header
{
    uchar Signature[4];     // Asinatura do arquivo "ihs".
    ushort Version;          // Versão do arquivo.
    ushort TableCount;      // Número de tabelas no arquivo.
    uint OffsetTablesData;  // Ponteiro para o descritor de tabelas.
    uint OffsetFreePages;   // Ponteiro para as páginas vazias.
    ushort PageSize;        // Tamanho da página.
    uint PageCount;         // Número de páginas utilizadas.
    uint OverflowPage;      // Página de Overflow.
};                          

// Estrutura do descritor de tabelas.
struct TableDescriptor
{
    uint OffsetNextPage;    // Ponteiro para a próxima página.
    uint OffsetPriorPage;   // Ponteiro para a página anterior.
    ushort PageOffset;      // Offset dentro da página.
    char TableName[31];     // Nome da tabela.
    ushort FieldCount;      // Número de campos.
    uint OffsetFieldsData;  // Ponteiro para o descritor de campos.
    uint OffsetTableData;   // Ponteiro para os dados da tabela.
    uint OverflowPage;      // Página de Overflow.
};

// Estrutura do descritor de campos.
struct FieldDescriptor
{
    uint OffsetNextPage;    // Ponteiro para a próxima página.
    uint OffsetPriorPage;   // Ponteiro para a página anteiror.
    ushort PageOffset;      // Offset dentro da página.
    uchar FieldName[31];    // Nome do campo.
    uchar FieldType;        // Tipo do campo.
    uint FieldSize;         // Tamanho do campo.
    uchar Reserved[7];      // Reservado para uso futuro.    
    uchar Reserved2[17];    // Reservado para uso futuro.    
    uint OverflowPage;      // Página de Overflow.
};

// Estrutura dos dados.
struct Data
{
    uint OffsetNextPage;    // Ponteiro para a próxima página.
    uint OffsetPriorPage;   // Ponteiro para a página anteiror.
    ushort PageOffset;      // Offset dentro da página.
    uint DataLength;        // Tamanho dos dados.
    uchar IsNull;           // Flag de nulo.
    uchar Reserved[5];      // Reservado para uso futuro.    
    uint OverflowPage;      // Página de Overflow.
    //uchar TableData[];      // uchar TableData[PAGE_SIZE - (sizeof(uint)*3) - (sizeof(uchar)*5)]; // Dados da tabela.  
};

// Página de dados adicionais.
struct OverflowPage
{
    uint OverflowPage;      // Página de Overflow.
    uchar Page_Data[];      // Dados da página.
};

// Estruturas auxiliares.
struct Field {
    struct Field *Prior;
    struct Field *Next;
    struct FieldDescriptor FieldDesc;
    uint PageNumber;
};

struct Table {
    struct Table *Prior;
    struct Table *Next;
    struct TableDescriptor TableDesc;
    struct Field FirstField;
    struct Field *Fields;
    struct Data DBData;
    uint PageNumber;
};

// Estrutura do banco de dados em memória.
struct DatabaseDescriptor
{
    struct Header DBHeader;     // Ponteiro para o header do banco de dados.
    struct Table FirstTable;    // Primeira tabela do banco de dados.
    struct Table *Tables;       // Ponteiro para as tabelas do banco de dados.
    FILE *File;                 // Handler do arquivo de banco de dados.
    char *pszFileName;          // Nome do arquivo de banco de dados.
};


/************************************************************************/
/* Tamanho dos tipos de dados                                           */
/************************************************************************/
/*  Size of uchar: 1
 *  Size of ushort: 2
 *  Size of uint: 4
 *  Size of char: 1
 */
#endif