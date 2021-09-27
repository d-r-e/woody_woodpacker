#include "../inc/woody_woodpacker.h"

t_elf g_elf;

static int write_to_woody(void *mem, size_t size)
{
    if (g_elf.woodyfd < 0)
    {
        printf("read error: open\n");
        return (0);
    }
    size_t written = write(g_elf.woodyfd, mem, size);
    g_elf.woodysz += written;
    if (written < size)
        printf("written %ld, intended %lu\n", written, size);
    return (written);
}

static int pad_to_woody(size_t size)
{
    size_t written = 0;
    size_t len = MAX_BUFF_SIZE;

    while (size > len && written / len < size / len)
    {
        written += write(g_elf.woodyfd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", len);
    }
    for (size_t i = written; i < size; ++i)
        written += write(g_elf.woodyfd, "\0", 1);
    g_elf.woodysz += written;
    if (written < size)
        printf("written %ld, intended %lu\n", written, size);
    return (written);
}

static int write_header(Elf64_Ehdr *header)
{
    write_to_woody(header, sizeof(*header));
#ifdef DEBUG
    printf("Woody header written.\n");
#endif
    return (0);
}

// static void print_program_header(Elf64_Phdr phdr)
// {
//     if (phdr.p_type > 10)
//         printf("p_type:  0x%x|\t", phdr.p_type);
//     else
//         printf("p_type:\t%11u|\t", phdr.p_type);
//     printf("p_offset:\t%7lu|\t", phdr.p_offset);
//     printf("p_paddr:\t%7lu|\t", phdr.p_paddr);
//     printf("p_filesz:\t%7lu|\n", phdr.p_filesz);
// }

static int copy_elf_headers(void)
{
    Elf64_Phdr *phdr;
#ifdef DEBUG
    printf("------------------------------------------\n");
    printf("e_phoff: %lu\n", g_elf.hdr.e_phoff);
    printf("e_shoff: %lu\n", g_elf.hdr.e_shoff);
    printf("e_phentsize: %u\n", g_elf.hdr.e_phentsize);
    printf("e_ehsize: %u\n", g_elf.hdr.e_ehsize);
    printf("e_phnum: %u\n", g_elf.hdr.e_phnum);
    printf("e_entry: 0x%08lx\n", g_elf.hdr.e_entry);
    printf("------------------------------------------\n");
#endif
    for (int i = 0; i < g_elf.hdr.e_phnum; ++i)
    {
        phdr = (Elf64_Phdr *)(g_elf.mem + g_elf.hdr.e_phoff + i * g_elf.hdr.e_phentsize);
        if ((void *)phdr + sizeof(*phdr) > (void *)(g_elf.mem + g_elf.size))
            strerr("wrong file format");
#ifdef DEBUG
        printf("copying header 0x%.8lx -> 0x%.8lx size %d type: %4d\n",
               (char *)phdr - (char *)g_elf.mem,
               (char *)phdr - (char *)g_elf.mem + g_elf.hdr.e_phentsize,
               g_elf.hdr.e_phentsize,
               phdr->p_type);
#endif
        write_to_woody(phdr, g_elf.hdr.e_phentsize);
    }
    return (0);
}

const char *get_section_name(int index)
{
    char *ptr;

    if (index < 0 || g_elf.strtab == NULL)
        return ("");
    if (g_elf.strtab + index > g_elf.mem + g_elf.size)
        return ("");
    ptr = g_elf.strtab + index;
    return (ptr);
}

static void find_strtab(void)
{
    Elf64_Shdr *shdr;

    for (int i = 0; i < g_elf.hdr.e_shnum; ++i)
    {
        shdr = (Elf64_Shdr *)(g_elf.mem + g_elf.hdr.e_shoff + i * sizeof(*shdr));
        if (shdr->sh_type == SHT_STRTAB)
            g_elf.strtab = g_elf.mem + shdr->sh_offset;
    }
}

static void copy_program_sections(void)
{
    Elf64_Shdr *shdr;
    int pad = 0;

    for (int i = 0; i < g_elf.hdr.e_shnum; ++i)
    {
        shdr = (Elf64_Shdr *)(g_elf.mem + g_elf.hdr.e_shoff + i * sizeof(*shdr));
        if ((void *)shdr + sizeof(*shdr) > (void *)(g_elf.mem + g_elf.size))
            strerr("wrong file format");
        pad = 0;
        if (g_elf.woodysz < shdr->sh_offset)
            pad = (shdr->sh_offset - g_elf.woodysz);
        if (!ft_strncmp(".text", get_section_name(shdr->sh_name), 6))
        {
#ifdef DEBUG
            printf(".text section found. Size: %lu\n", shdr->sh_size);
#endif
        }
#ifdef DEBUG
        if (shdr->sh_type == PT_LOAD)
        {
            find_caves(*shdr, '\0', 100);
            printf("sect %3d %-20s 0x%.8lx -> 0x%.8lx size %7lu  type : %10d  alignment: %3lu pad: %4d\n",
               i,
               get_section_name(shdr->sh_name),
               shdr->sh_offset, shdr->sh_offset + shdr->sh_size,
               shdr->sh_size, shdr->sh_type, shdr->sh_addralign,
               pad);
        }
        //printf("size: %lu pad: %u sh_addralign %lu\n", shdr->sh_size, pad, shdr->sh_addralign);
#endif
        pad_to_woody(pad);
        if (shdr->sh_type != SHT_NOBITS)
            write_to_woody(g_elf.mem + shdr->sh_offset, shdr->sh_size);

        // printf("align: %ld, ret %d \n", phdr->p_align, ret);
    }
}

static void update_size(Elf64_Ehdr *hdr)
{
    ft_bzero(&hdr->e_shoff, sizeof(hdr->e_shoff));
    ft_bzero(&hdr->e_shnum, sizeof(hdr->e_shnum));
}

int is_elf(const char *file)
{
    Elf64_Ehdr *hdr;
    int fd;
    int iself = 0;

    ft_bzero(&g_elf, sizeof(g_elf));
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    g_elf.size = lseek(fd, 0, SEEK_END);

    g_elf.mem = mmap(NULL, g_elf.size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (g_elf.mem == MAP_FAILED)
    {
        printf("%s, error: \"%s\" not a regular file\n", BIN, file);
        close(fd);
        return (0);
    }
    hdr = (Elf64_Ehdr *)g_elf.mem;
    hdr = malloc(sizeof(Elf64_Ehdr));
    ft_memcpy(hdr, g_elf.mem, sizeof(Elf64_Ehdr));
    ft_memcpy(&g_elf.hdr, hdr, sizeof(*hdr));

    if (g_elf.size >= sizeof(*hdr) &&
        !ft_memcmp(ELFMAG, hdr->e_ident, ft_strlen(ELFMAG)) &&
        hdr->e_ident[EI_CLASS] == ELFCLASS64)
    {
        iself = 1;
        g_elf.woodyfd = open("woody", O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0755);
        if (g_elf.woodyfd < 0)
        {
            printf("%s: error: packed file could not be created.\n", BIN);
        }
        else if (!write_header(hdr))
        {
            copy_elf_headers();
            find_strtab();
            copy_program_sections();
            update_size(hdr);
        }
        close(g_elf.woodyfd);
    }
#ifdef DEBUG
    // printf("binary file g_elf.size: %ld bytes\n", g_elf.size);
    // printf("e_ident[EI_CLASS]: %d\n", hdr->e_ident[EI_CLASS]);
#endif
    munmap(g_elf.mem, g_elf.size);
    close(fd);
    free(hdr);
    return (iself);
}