#include "../inc/woody.h"

extern Elf64_Ehdr g_hdr;
extern size_t g_binsize;
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
        while (!ft_isprint(ptr[i]))
            read(fd, &ptr[i], 1);
        printf("%02x ", ptr[i]);
        if (i == len - 1)
             printf("\n");
    }
    close(fd);
    return(ptr);
}

long long encrypt_text_section(void *mem, int text_offset, uint size)
{
    unsigned char *key = NULL;
    unsigned long long bitkey = 0;
    char *ptr;

    key = generate_key(KEYLEN);
    if (!key || size <= 0 || text_offset <= 0)
        return(-1);
    bitkey = *(long long*)key;
    printf(""CYAN"key value (hexad): "RED"%llx"DEFAULT", %lu bit key\n", bitkey, sizeof(bitkey) * 8);
    ptr = (char*)mem + text_offset;
    printf("key value (ascii): %s\n", key);
    for (uint i = 0; i < size; ++i)
    {
        // XOR magic with random key
        // ptr[i] ^= 0xcafebabe;
        ptr[i] ^= key[i % KEYLEN];
        ptr[i] ^= key[i % KEYLEN];
        // ptr[i] ^= key[i % KEYLEN];
        // ptr[i] ^= key[i % KEYLEN];
        // ptr[i] ^= 0;
        // ptr[i] ^= key[(i + 5) % KEYLEN];
        // ptr[i] ^= key[(i + 42) % KEYLEN];
        // ptr[i] ^= size;
        // if done twice, cypher is reversed.
        // ptr[i] ^= key[i % KEYLEN];
        // ptr[i] ^= key[(i + 5) % KEYLEN];
        // ptr[i] ^= key[(i + 42) % KEYLEN];
        // ptr[i] ^= size;
    }
    free(key);
    return (bitkey);
}