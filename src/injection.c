#include "../inc/woody_woodpacker.h"

char payload[] = { '\x50','\x57','\x56','\x52','\xb8','\x01','\x00','\x00','\x00','\xbf','\x01','\x00','\x00','\x00','\x48','\xbe','\x28','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\xba','\x0f','\x00','\x00','\x00','\x0f','\x05','\x5a','\x5e','\x5f','\x58','\xe9','\xb8','\x03','\x40','\x00','\x2e','\x2e','\x2e','\x2e','\x57','\x4f','\x4f','\x44','\x59','\x2e','\x2e','\x2e','\x2e','\x2e','\x0a','\x00'};

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

    if (g_elf.cave_offset)
        return;
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
        if (max >= min)
            break;
    }
    if (max >= min)
    {
        printf("max cave in %s found for character %d: %lu bytes\n", get_section_name(shdr.sh_name), c, max);
        g_elf.cave_offset = shdr.sh_offset + i;
    }
    // if (!infected)
    //     ft_memcpy()
}

void write_payload()
{
    Elf64_Addr offset;
    Elf64_Addr woody;

    offset = g_elf.cave_offset;
    woody = offset + 40;
    g_elf.woodyfd = open("woody", O_RDWR);
    lseek(g_elf.woodyfd, offset, SEEK_SET);
    ft_memcpy((void*)&payload + 16, &woody, sizeof(offset));
    //write(1, payload + 38, 15);
    for (int i = 0; i < 53; ++i)
        write(g_elf.woodyfd, &payload[i], 1);
    printf("file infected from offset %lu: %08lx. woody offset: %08lx\n", offset, offset, woody);
    lseek(g_elf.woodyfd, 0x18, SEEK_SET);
    write(g_elf.woodyfd, &offset, sizeof(offset));
    close(g_elf.woodyfd);
}