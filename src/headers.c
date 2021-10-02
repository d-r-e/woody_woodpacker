#include "../inc/woody_woodpacker.h"

int copy_program_headers(void)
{
    Elf64_Phdr *phdr;
    Elf64_Phdr *prev;

#ifdef DEBUG
    print_elf_header(g_elf.hdr);
#endif
(void)payload;
    for (int i = 0; i < g_elf.hdr.e_phnum; ++i)
    {
        phdr = malloc(sizeof(*phdr));
        ft_memcpy(phdr, g_elf.mem + g_elf.hdr.e_phoff + i * g_elf.hdr.e_phentsize, sizeof(*phdr));
        if (!g_elf.baseimage && phdr->p_type == PT_LOAD)
            g_elf.baseimage = phdr->p_vaddr;
        // if (i == g_elf.hdr.e_phnum - 1)
        // {
        //     printf("modifying program header for last pt_load\n");
        //     // phdr->p_filesz += sizeof(payload);
        // }
        // phdr->p_flags = PF_X + PF_W + PF_R;
        if ((char *)phdr + sizeof(*phdr) > (char *)(g_elf.mem + g_elf.size))
            strerr("wrong file format");
#ifdef DEBUG
        printf("shdr 0x%.8lx -> 0x%.8lx size %d flags: [%c%c%c] type: %d\n",
               (char *)phdr - (char *)g_elf.mem,
               (char *)phdr - (char *)g_elf.mem + g_elf.hdr.e_phentsize,
               g_elf.hdr.e_phentsize,
               phdr->p_flags & PF_R ? 'r' : ' ',
               phdr->p_flags & PF_W ? 'w' : ' ',
               phdr->p_flags & PF_X ? 'x' : ' ',
               phdr->p_type < 10 ? phdr->p_type : 0);
#endif
        write_to_woody(phdr, g_elf.hdr.e_phentsize);
        (void)prev;
        prev = (Elf64_Phdr *)(g_elf.mem + g_elf.hdr.e_phoff + i * g_elf.hdr.e_phentsize);
        free(phdr);
    }
    return (0);
}

void copy_section_headers(void)
{
    Elf64_Shdr *shdr;
    Elf64_Shdr *prev;
    // int written = 0;

    for (int i = 0; i < g_elf.hdr.e_shnum; ++i)
    {
        shdr = malloc(sizeof(*shdr));
        ft_memcpy(shdr, g_elf.mem + g_elf.hdr.e_shoff + i * sizeof(*shdr), sizeof(*shdr));
// if (written)
// {
//     shdr->sh_offset += sizeof(*shdr) + sizeof(payload);
// }
#ifdef DEBUG
        if (!ft_strcmp(get_section_name(shdr->sh_name), ".shstrtab"))
            printf(".shstrtab offset: %lx\n", shdr->sh_offset);
#endif
        write_to_woody(shdr, sizeof(*shdr));
        prev = (Elf64_Shdr *)(g_elf.mem + g_elf.hdr.e_shoff + i * sizeof(*shdr));
        free(shdr);
        (void)prev;
        // if (!ft_strcmp(get_section_name(prev->sh_name), ".text") && written == 0)
        // {
        //     shdr = malloc(sizeof *shdr);
        //     shdr->sh_name = 0;
        //     shdr->sh_size = sizeof(payload);
        //     shdr->sh_addralign = 0x1;
        //     shdr->sh_addr = g_elf.hdr.e_shoff + (i + 1) * sizeof(*shdr);
        //     shdr->sh_flags = SHF_EXECINSTR & SHF_ALLOC;
        //     shdr->sh_type = SHT_PROGBITS;
        //     shdr->sh_type = 69;
        //     shdr->sh_entsize = sizeof(shdr);
        //     shdr->sh_offset = g_elf.woodysz;
        //     write_to_woody(shdr, sizeof(*shdr));
        //     free(shdr);
        //     written = 1;
        // }
    }
}