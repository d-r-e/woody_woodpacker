#include "../inc/woody_woodpacker.h"

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

    offset = g_elf.woody_offset;
    g_elf.woodyfd = open("woody", O_RDWR);
    printf("file infected from offset %lu:0x%08lx\n", offset, offset);
// #ifdef DEBUG
//     print_elf_header(g_elf.hdr);
// #endif
    // g_elf.hdr.e_entry = offset;
#ifdef MODIFY
    g_elf.hdr.e_shoff += sizeof(payload);
    g_elf.hdr.e_shnum++;
#endif
#ifndef COPY_HEADERS
    g_elf.hdr.e_shoff = 0;
    g_elf.hdr.e_shnum = 0;
#endif
    printf("base image: 0x%lx\n", g_elf.baseimage);
    g_elf.hdr.e_entry = g_elf.woody_offset + g_elf.baseimage;
#ifdef DEBUG
    print_elf_header(g_elf.hdr);
#endif
    lseek(g_elf.woodyfd, 0, SEEK_SET);
    write(g_elf.woodyfd, (void *)&g_elf.hdr, sizeof(g_elf.hdr));
    close(g_elf.woodyfd);
}

void write_woody_section(Elf64_Shdr *shdr)
{
    (void)shdr;
    char *payload_return_to_entry;
    const char address[] = {0x11, 0x11, 0x11, 0x11};

    for (uint i = 0; i < sizeof(payload) - 3; ++i)
    {
        if (!ft_strncmp(&payload[i], address, 4))
            payload_return_to_entry = &payload[i];
    }
    for (int i = 0; i < 4; ++i)
        printf("%02x", payload_return_to_entry[i]);
    printf("\n");
    ft_memcpy((void*)payload_return_to_entry, (void*)&g_elf.hdr.e_entry, 4);
    for (int i = 0; i < 4; ++i)
        printf("%02x", payload_return_to_entry[i]);
    printf("\n");
    g_elf.woody_offset = g_elf.woodysz;
    uint pad = g_elf.woodysz % 16;
    printf("woody padding: %lu\n", g_elf.woodysz % 16);
    if (pad)
        pad_to_woody(pad);
    write_to_woody(payload, sizeof(payload));
#ifdef DEBUG
    printf("%s: payload written at 0x%lx: after %s section\n", BIN, g_elf.woody_offset, get_section_name(shdr->sh_name));
#endif
    return;
}