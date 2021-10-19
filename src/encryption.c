#include "../inc/woody.h"

extern Elf64_Ehdr g_hdr;
extern size_t g_binsize;
char *generate_key(uint len)
{
    char *ptr = NULL;
    int fd;

    fd = open("/dev/random", O_RDONLY);
    if (fd < 0)
        return (NULL);
    ptr = (char*)ft_calloc(1, (len + 1));
    for (uint i = 0; i < len; i++)
    {
        read(fd, &ptr[i], 1);
        while (!ft_isprint(ptr[i]))
            read(fd, &ptr[i], 1);
        printf("%02x ", ptr[i]);
        if (i == len - 1)
             printf("\n");
    }
    close(fd);
    return(ptr);
}

char *encrypt_text_section(void *mem, int text_offset, uint size)
{
    char *key = NULL;
    char *ptr;

    key = generate_key(KEYLEN);
    if (!key || size <= 0 || text_offset <= 0 || ft_strlen((char*)key) != KEYLEN)
        return(NULL);
    printf("Injected random %lu bit key\n", ft_strlen(key) * 8);
    ptr = (char*)mem + text_offset;
    printf("key value (ascii): %s\n", key);
    for (uint i = 0; i < size; ++i)
        ptr[i] ^= key[i % KEYLEN];
    return (key);
}