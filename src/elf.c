#include "../inc/woody_woodpacker.h"

t_elf g_elf;

int write_to_woody(void *mem, size_t size)
{
    (void)payload;
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
        written += write(g_elf.woodyfd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", len);
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
    ft_memcpy(&g_elf.hdr, header, sizeof(g_elf.hdr));
    print_elf_header(g_elf.hdr);
    write_to_woody(&g_elf.hdr, sizeof(g_elf.hdr));
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

void print_elf_header(Elf64_Ehdr hdr)
{
    printf("------------------------------------------\n");
    printf("e_phoff: %-5lu\n", hdr.e_phoff);
    printf("e_entry: 0x%-8lx\n", hdr.e_entry);
    printf("e_shnum: %-5u\n", hdr.e_shnum);
    printf("e_shoff: 0x%-5lx\n", hdr.e_shoff);
    printf("e_phoff: 0x%-5lx\n", hdr.e_phoff);
    printf("e_phentsize: %-5u\n", hdr.e_phentsize);
    printf("e_ehsize: %-5u\n", hdr.e_ehsize);
    printf("e_phnum: %-u\n", hdr.e_phnum);
    printf("e_entry: 0x%-8lx\n", hdr.e_entry);
    printf("e_shstrndx: 0x%-8x\n", hdr.e_shstrndx);
    printf("------------------------------------------\n");
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
    Elf64_Shdr *shdr = NULL;
    Elf64_Shdr *prev = NULL;
    int pad = 0;
    int written = 0;

    for (int i = 0; i < g_elf.hdr.e_shnum; ++i)
    {
        shdr = malloc(sizeof(*shdr));
        ft_memcpy(shdr, g_elf.mem + g_elf.hdr.e_shoff + i * sizeof(*shdr), sizeof(*shdr));
        if ((void *)shdr + sizeof(*shdr) > (void *)(g_elf.mem + g_elf.size))
            strerr("wrong file format");
        pad = 0;
        if (g_elf.woodysz < shdr->sh_offset)
            pad = (shdr->sh_offset - g_elf.woodysz);
        if (!ft_strcmp(SECTION, get_section_name(shdr->sh_name)))
        {
#ifdef DEBUG
            printf("%s section found. Size: %lu\n", SECTION, shdr->sh_size);
#endif
            ;
        }
#ifdef DEBUG
        if (shdr->sh_type)
        {
            // find_caves(*shdr, '\0', CAVE_SIZE);
            // if (g_elf.cave_offset)
            //     shdr->sh_flags = 6;
            printf("%3d| %-20s %04lx-%04lx sz: %7lu  type:%d flags:%lx algn: %3lu pad: %4d\n",
                   i,
                   get_section_name(shdr->sh_name),
                   shdr->sh_offset, shdr->sh_offset + shdr->sh_size,
                   shdr->sh_size, shdr->sh_type < 10 ? shdr->sh_type : 0, shdr->sh_flags, shdr->sh_addralign,
                   pad);
        }
#endif
        if (written == 0 && prev && !ft_strcmp(SECTION, get_section_name(shdr->sh_name))) //!ft_strcmp(get_section_name(prev->sh_name), ".bss") && written == 0)
        {
            printf("%s has passed\n", SECTION);
            write_woody_section(shdr);
            written = 1;
        }
        (void)prev;
        // if (i == g_elf.hdr.e_shnum - 1 && written == 0)
        // {
        //     printf("last section appended\n");
        //     write_woody_section(shdr);
        //     written = 1;
        // }
        pad_to_woody(pad);
        if (shdr->sh_type != SHT_NOBITS)
            write_to_woody(g_elf.mem + shdr->sh_offset, shdr->sh_size);
        else if (shdr->sh_type == SHT_NOBITS)
        {
            pad_to_woody(shdr->sh_size);
            //write_woody_section(shdr);
        }
        if (i == g_elf.hdr.e_shnum - 1 && written == 0)
        {
            pad = g_elf.hdr.e_shoff - g_elf.woodysz + sizeof(payload);
            printf("header: 0x%lx pad: %d\n", shdr->sh_offset, pad);
            if (pad > 0)
                pad_to_woody(pad);
        }
        prev = (Elf64_Shdr *)(g_elf.mem + g_elf.hdr.e_shoff + i * sizeof(*shdr));
        free(shdr);
        // printf("align: %ld, ret %d \n", phdr->p_align, ret);
    }
    if (written == 0)
        printf("Mal asunto!\n");
}

static void update_size(Elf64_Ehdr *hdr)
{
    (void)hdr;

    //ft_memset(&hdr->e_entry, 42, sizeof(hdr->e_entry));
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
    if (is_infected())
    {
        printf("%s: error: this binary has already been infected.\n", BIN);
        iself = 1;
    }
    else if (g_elf.size >= sizeof(*hdr) &&
             !ft_memcmp(ELFMAG, hdr->e_ident, ft_strlen(ELFMAG)) &&
             hdr->e_ident[EI_CLASS] == ELFCLASS64)
    {
        iself = 1;
        g_elf.woodyfd = open("woody", O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0755);
        if (g_elf.woodyfd < 0)
        {
            printf("%s: error: packed file could not be created or another program is using it.\n", BIN);
        }
        else
        {
            update_size(hdr);
            if (!write_header(hdr))
            {
                copy_program_headers();
                find_strtab();
                copy_program_sections();
#ifdef COPY_HEADERS
                copy_section_headers();
                // write_to_woody(g_elf.mem + g_elf.woodysz, g_elf.size - g_elf.woodysz);
#endif
            }
        }
        close(g_elf.woodyfd);
#ifdef MODIFY
        write_payload();
#endif
        // if (g_elf.cave_offset)
        //     write_payload();
        // else
        //     printf("Cave of size %u was not found.\n", CAVE_SIZE);
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