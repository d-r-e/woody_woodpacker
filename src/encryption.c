#include "../inc/woody.h"

extern Elf64_Ehdr g_hdr;

unsigned char *generate_key(uint len)
{
    unsigned char *ptr = NULL;
    int fd;

    fd = open("/dev/random", O_RDONLY);
    if (fd < 0)
        return (NULL);
    ptr = (unsigned char*)ft_calloc(1, (len + 1));
    for (uint i = 0; i < len; i++)
    {
        read(fd, &ptr[i], 1);
        while (ft_isprint(ptr[i]))
            read(fd, &ptr[i], 1);
        printf("%02x ", ptr[i]);
    }
    printf("\n");
    close(fd);
    return(ptr);
}

long long encrypt_text_section(char *mem, int text_sect, uint size)
{
    unsigned char *key = NULL;
    unsigned long long bitkey = 0;
    Elf64_Shdr *shdr = NULL;
    char *ptr;

    shdr = (void*)mem + text_sect;
    key = generate_key(KEYLEN);
    bitkey = *(long long*)key;
    printf(""CYAN"key value: "RED"%llx"DEFAULT", %lu bit key\n", bitkey, sizeof(bitkey) * 8);
    ptr = (char*)&shdr[text_sect];
    for (uint i = 0; i < size; ++i)
    {
        // XOR magic with random key
        ptr[i] ^= key[i % KEYLEN];
        // ptr[i] ^= key[(i + 5) % KEYLEN];
        // ptr[i] ^= key[(i + 42) % KEYLEN];
        // ptr[i] ^= size;
        // if done twice, cypher is reversed.
        ptr[i] ^= key[i % KEYLEN];
        // ptr[i] ^= key[(i + 5) % KEYLEN];
        // ptr[i] ^= key[(i + 42) % KEYLEN];
        // ptr[i] ^= size;
    }
    free(key);
    return (bitkey);
}