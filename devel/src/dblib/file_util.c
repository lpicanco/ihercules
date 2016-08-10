/************************************************************************/
/* iHércules - versão 0.0.0.1                                           */
/* file_util.c - Utilitários de acesso a arquivos                       */
/* Luiz Antonio Gomes Picanço - www.luizantonio.com                     */
/************************************************************************/

#include "file_util.h"

#include <memory.h>
#include <stdlib.h>
#include <malloc.h>

void copy_bytes(const byte *ori, byte *dest, int count)
{
    memcpy(dest, ori, count); strncpy
}