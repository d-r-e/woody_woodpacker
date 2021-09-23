#include "../inc/woody_woodpacker.h"

void find_caves(Elf64_Shdr shdr, char c)
{
    char *ptr;
    unsigned long max = 0;
    unsigned long i, j;

    j = 0;
    ptr = g_elf.mem + shdr.sh_offset;
    for (i =0; i < shdr.sh_size; ++i)
    {
        if (ptr[i] == c)
        {
            j = 0;
            while(ptr[i+j] == c)
                j++;
        }
        if (j >= max)
            max = j;
    }
    printf("max cave found for character %d: %lu\n", c, max);


}