#include "../inc/woody_woodpacker.h"

// char payload[] = {"\x48\x31\xf6\x56\x48\xbf"
// 		  "\x2f\x62\x69\x6e\x2f"
// 		  "\x2f\x73\x68\x57\x54"
// 		  "\x5f\xb0\x3b\x99\x0f\x05"};
int is_infected(void)
{
    (void)payload;
    if (g_elf.hdr.e_shnum == 0)
        return (1);
    return (0);
}

// if (!infected)
//     ft_memcpy()

void write_payload()
{
    Elf64_Addr offset;
    // Elf64_Addr woody;

    offset = g_elf.woody_offset;
    //woody = offset + 38;
    g_elf.woodyfd = open("woody", O_RDWR);
    //ft_memcpy((void*)&payload + WOODY_LEN, &woody, sizeof(woody));
    printf("file infected from offset %lu: 0x%08lx\n", offset, offset);
    lseek(g_elf.woodyfd, 0, SEEK_SET);
#ifdef DEBUG
    print_elf_header(g_elf.hdr);
#endif
    g_elf.hdr.e_shoff += sizeof(payload);
    g_elf.hdr.e_shnum++;
    g_elf.hdr.e_shstrndx += sizeof(Elf64_Shdr) + sizeof(payload);
#ifdef DEBUG
    print_elf_header(g_elf.hdr);
#endif
    write(g_elf.woodyfd, (void *)&g_elf.hdr, sizeof(g_elf.hdr));
    //write(g_elf.woodyfd, &g_elf.hdr.e_entry, sizeof(offset));
    close(g_elf.woodyfd);
}

void write_woody_section(Elf64_Shdr *shdr)
{
    (void)shdr;
    g_elf.woody_offset = g_elf.woodysz;
    write_to_woody(payload, sizeof(payload));
#ifdef DEBUG
    printf("%s: payload written\n", BIN);
#endif
    return;
}