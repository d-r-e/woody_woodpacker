#include "../inc/woody_woodpacker.h"

int is_elf(const char *file)
{
    Elf64_Ehdr *hdr;
    int fd;
    uint size;
    int iself;
    char *mem;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    size = lseek(fd, 0, SEEK_END);
    mem = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED)
    {
        close(fd);
        return (0);
    }
    if (size < sizeof(*hdr))
        iself = 0;
    hdr = (Elf64_Ehdr*)mem;
    if (ft_memcmp(ELFMAG, hdr->e_ident, ft_strlen(ELFMAG)) == 0)
        iself = 1;
    munmap(mem, size);
    close(fd);
    return (iself);
}