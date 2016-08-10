#if !defined(FileLevel_h)
#define FileLevel_h
#include "FileStructure.h"

int writeDB(struct DatabaseDescriptor *db); // Grava os dados do banco de dados em arquivo.
void initData(struct DatabaseDescriptor *db);    // Inicializa os dados da strutura.
uint newPage(struct DatabaseDescriptor *db);    // Cria um nova página e devolve a sua posição no arquivo.
#endif