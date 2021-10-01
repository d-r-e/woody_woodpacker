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

void write_payload()
{
    Elf64_Addr offset;

    offset = g_elf.woody_offset + 1;
    g_elf.woodyfd = open("woody", O_RDWR);
    printf("file infected from offset %lu:0x%08lx\n", offset, offset);
// #ifdef DEBUG
//     print_elf_header(g_elf.hdr);
// #endif
    // g_elf.hdr.e_entry = offset;

    g_elf.hdr.e_shoff += sizeof(payload);
    g_elf.hdr.e_shnum++;
#ifdef DEBUG
    print_elf_header(g_elf.hdr);
#endif
#ifndef COPY_HEADERS
    g_elf.hdr.e_shoff = 0;
    g_elf.hdr.e_shnum = 0;
#endif
    lseek(g_elf.woodyfd, 0, SEEK_SET);
    write(g_elf.woodyfd, (void *)&g_elf.hdr, sizeof(g_elf.hdr));
    close(g_elf.woodyfd);
}

void write_woody_section(Elf64_Shdr *shdr)
{
    (void)shdr;
    g_elf.woody_offset = g_elf.woodysz;
    write_to_woody(payload, sizeof(payload));
#ifdef DEBUG
    printf("%s: payload written at 0x%lx\n", BIN, g_elf.woody_offset);
#endif
    return;
}