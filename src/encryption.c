#include "../inc/woody.h"

extern Elf64_Ehdr g_hdr;

char *generate_key(int seed)
{
    char *ptr;
    char number[KEYLEN + 1];
    char *str;


    ptr = ft_calloc(1, seed % 100 + 1);
    sprintf(number, "%8p%8p", ptr, ptr);
    free(ptr);
    str = ft_calloc(1, KEYLEN + 1);
    sprintf(str, "%s", number);
    for (uint i = 0; i < KEYLEN; ++i)
    {
        str[i] += 16 - i - str[i + 1];
        while(!ft_isalnum(str[i]))
        {
            str[i] = (str[i]+ 1) + '0';
        }
    }
    str[0] = number[42 % KEYLEN];
    return (str);
}

int encrypt_text_section(char *mem, int text_sect, uint size)
{
    char *key = NULL;
    Elf64_Shdr *shdr = NULL;
    char *ptr;

    shdr = (void*)mem + g_hdr.e_shoff;
    key = generate_key(text_sect);
    printf("KEY: %s\n", key);

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