/************************************************************************/
/* iH�rcules - vers�o 0.0.0.1                                           */
/* file_util.c - Utilit�rios de acesso a arquivos                       */
/* Luiz Antonio Gomes Pican�o - www.luizantonio.com                     */
/************************************************************************/

#include "file_util.h"

#include <memory.h>
#include <stdlib.h>
#include <malloc.h>

void copy_bytes(const byte *ori, byte *dest, int count)
{
    memcpy(dest, ori, count); strncpy
}