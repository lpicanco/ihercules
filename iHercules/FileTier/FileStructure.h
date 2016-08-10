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
    ushort Version;          // Vers�o do arquivo.
    ushort TableCount;      // N�mero de tabelas no arquivo.
    uint OffsetTablesData;  // Ponteiro para o descritor de tabelas.
    uint OffsetFreePages;   // Ponteiro para as p�ginas vazias.
    ushort PageSize;        // Tamanho da p�gina.
    uint PageCount;         // N�mero de p�ginas utilizadas.
    uint OverflowPage;      // P�gina de Overflow.
};                          

// Estrutura do descritor de tabelas.
struct TableDescriptor
{
    uint OffsetNextPage;    // Ponteiro para a pr�xima p�gina.
    uint OffsetPriorPage;   // Ponteiro para a p�gina anterior.
    ushort PageOffset;      // Offset dentro da p�gina.
    char TableName[31];     // Nome da tabela.
    ushort FieldCount;      // N�mero de campos.
    uint OffsetFieldsData;  // Ponteiro para o descritor de campos.
    uint OffsetTableData;   // Ponteiro para os dados da tabela.
    uint OverflowPage;      // P�gina de Overflow.
};

// Estrutura do descritor de campos.
struct FieldDescriptor
{
    uint OffsetNextPage;    // Ponteiro para a pr�xima p�gina.
    uint OffsetPriorPage;   // Ponteiro para a p�gina anteiror.
    ushort PageOffset;      // Offset dentro da p�gina.
    uchar FieldName[31];    // Nome do campo.
    uchar FieldType;        // Tipo do campo.
    uint FieldSize;         // Tamanho do campo.
    uchar Reserved[7];      // Reservado para uso futuro.    
    uchar Reserved2[17];    // Reservado para uso futuro.    
    uint OverflowPage;      // P�gina de Overflow.
};

// Estrutura dos dados.
struct Data
{
    uint OffsetNextPage;    // Ponteiro para a pr�xima p�gina.
    uint OffsetPriorPage;   // Ponteiro para a p�gina anteiror.
    ushort PageOffset;      // Offset dentro da p�gina.
    uint DataLength;        // Tamanho dos dados.
    uchar IsNull;           // Flag de nulo.
    uchar Reserved[5];      // Reservado para uso futuro.    
    uint OverflowPage;      // P�gina de Overflow.
    //uchar TableData[];      // uchar TableData[PAGE_SIZE - (sizeof(uint)*3) - (sizeof(uchar)*5)]; // Dados da tabela.  
};

// P�gina de dados adicionais.
struct OverflowPage
{
    uint OverflowPage;      // P�gina de Overflow.
    uchar Page_Data[];      // Dados da p�gina.
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

// Estrutura do banco de dados em mem�ria.
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