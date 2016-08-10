#include "../dblib/file_util.h"
#include <stdio.h>
#include <memory.h>

void main(void)
{
    byte *nome = "teste";
    byte nome2[5];

    memset(nome2, 0, 5);

    copy_bytes(nome, nome2, 5);
    printf("%s\n", nome2);

    copy_bytes("teste", nome2, 5);
    printf("%s\n", nome2);

}