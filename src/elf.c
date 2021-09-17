#include "../inc/woody_woodpacker.h"

int is_elf(const char *file)
{
    Elf64_Ehdr *hdr;
    int fd;
    uint size;
    int iself = 0;
    char *mem;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    size = lseek(fd, 0, SEEK_END);
    
    mem = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED)
    {
        printf("%s, error: \"%s\" not a regular file\n", BIN, file);
        close(fd);
        return (0);
    }
    hdr = (Elf64_Ehdr*)mem;
    if (size >= sizeof(*hdr) &&
            !ft_memcmp(ELFMAG, hdr->e_ident, ft_strlen(ELFMAG)) &&
            hdr->e_ident[EI_CLASS] == ELFCLASS64)
        iself = 1;
    #ifdef DEBUG
     printf("binary file size: %d bytes\n", size);
     printf("e_type: %d\n", hdr->e_type);
     printf("e_ident[EI_CLASS]: %d\n", hdr->e_ident[EI_CLASS]);
    #endif
    munmap(mem, size);
    close(fd);
    return (iself);
}