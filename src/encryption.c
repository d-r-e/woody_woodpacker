#include "../inc/woody.h"

extern Elf64_Ehdr g_hdr;

char *generate_key(uint len)
{
    char *ptr = NULL;
    int rd;
    int fd;

    fd = open("/dev/random", O_RDONLY);
    if (fd < 0)
        return (NULL);
    ptr = (char*)malloc(sizeof(char) * (len + 1));
    rd = read(fd, ptr, len);
    close(fd);
    if (rd < (int)len)
        return(NULL);
    return(ptr);

}

int encrypt_text_section(char *mem, int text_sect, uint size)
{
    char *key = NULL;
    unsigned long long bitkey = 0;
    Elf64_Shdr *shdr = NULL;
    char *ptr;

    shdr = (void*)mem + text_sect;
    key = generate_key(KEYLEN);
    bitkey = (long long)key;
    printf(""CYAN"key value: "RED"%*lld"DEFAULT", %lu bit key\n", (int)(sizeof(bitkey)), bitkey, sizeof(bitkey) * 8);
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
    return (0);
}