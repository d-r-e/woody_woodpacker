#include "../inc/woody_woodpacker.h"

t_elf g_elf;

static int write_header(Elf64_Ehdr *header)
{
    g_elf.woodyfd = open("woody", O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0755);
    if (g_elf.woodyfd < 0)
    {
        printf("%s: error: could not create new file\n", BIN);
        return (-1);
    }
    write(g_elf.woodyfd, header, sizeof(*header));
#ifdef DEBUG
    printf("Woody header written.\n");
#endif
    close(g_elf.woodyfd);
    return (0);
}

void print_program_header(Elf64_Phdr phdr)
{
    if (phdr.p_type > 10)
        printf("p_type:  0x%x|\t", phdr.p_type);
    else
        printf("p_type:\t%11u|\t", phdr.p_type);
    printf("p_offset:\t%7lu|\t", phdr.p_offset);
    printf("p_paddr:\t%7lu|\t", phdr.p_paddr);
    printf("p_filesz:\t%7lu|\n", phdr.p_filesz);
}

static int copy_elf_header(void)
{
    Elf64_Phdr *phdr;

    printf("------------------------------------------\n");
    printf("e_phoff: %lu\n", g_elf.hdr.e_phoff);
    printf("e_shoff: %lu\n", g_elf.hdr.e_shoff);
    printf("e_phentsize: %u\n", g_elf.hdr.e_phentsize);
    printf("e_ehsize: %u\n", g_elf.hdr.e_ehsize);
    printf("e_phnum: %u\n", g_elf.hdr.e_phnum);
    printf("------------------------------------------\n");
    g_elf.woodyfd = open("woody", O_RDWR | O_APPEND, 755);
    for (int i = 0; i < g_elf.hdr.e_phnum; ++i)
    {
        phdr = (Elf64_Phdr *)(g_elf.mem + g_elf.hdr.e_phoff + i * sizeof(Elf64_Phdr));
        if ((void *)phdr + sizeof(*phdr) > (void *)(g_elf.mem + g_elf.size))
            strerr("wrong file format");
#ifdef DEBUG
        //print_program_header(*phdr);
        printf("copying header %p -> %p size %ld %d\n", phdr, phdr + g_elf.hdr.e_phentsize, sizeof(*phdr), g_elf.hdr.e_phentsize);
#endif
        write(g_elf.woodyfd, phdr, g_elf.hdr.e_phentsize);
    }
    close(g_elf.woodyfd);
    return (0);
}

static void copy_program_headers(void)
{
    Elf64_Phdr *phdr;

    g_elf.woodyfd = open("woody", O_RDWR | O_APPEND, 755);

    for (int i = 0; i < g_elf.hdr.e_phnum; ++i)
    {
        phdr = (Elf64_Phdr *)(g_elf.mem + g_elf.hdr.e_phoff + i * sizeof(Elf64_Phdr));
        if ((void *)phdr + sizeof(*phdr) > (void *)(g_elf.mem + g_elf.size))
            strerr("wrong file format");
        printf("copying section %p -> %p size %lu\n", (g_elf.mem + phdr->p_offset), (g_elf.mem + phdr->p_offset + phdr->p_filesz), phdr->p_filesz);
        write(g_elf.woodyfd, g_elf.mem + phdr->p_offset, phdr->p_filesz);
    }
    close(g_elf.woodyfd);
}

int is_elf(const char *file)
{
    Elf64_Ehdr *hdr;
    int fd;
    int iself = 0;

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
        if (!write_header(hdr))
        {
            copy_elf_header();
            copy_program_headers();
        }
    }
#ifdef DEBUG
    printf("binary file g_elf.size: %ld bytes\n", g_elf.size);
    printf("e_ident[EI_CLASS]: %d\n", hdr->e_ident[EI_CLASS]);
#endif
    munmap(g_elf.mem, g_elf.size);
    close(fd);
    free(hdr);
    return (iself);
}