#include "../inc/woody_woodpacker.h"

int is_infected(void)
{
    if (g_elf.hdr.e_shnum == 0)
        return (1);
    return (0);
}

void find_caves(Elf64_Shdr shdr, char c, size_t min)
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
    if (max >= min)
        printf("max cave in %s found for character %d: %lu bytes\n", get_section_name(shdr.sh_name), c, max);
}
