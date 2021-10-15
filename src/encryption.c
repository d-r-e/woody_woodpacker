#include "../inc/woody.h"

extern Elf64_Ehdr g_hdr;

char *generate_key(int seed)
{
    char *ptr;
    char number[KEYLEN + 1];
    char *sample;

    ptr = ft_calloc(1, seed % 100 + 1);
    sample = ft_calloc(1, 40);
    //sprintf(sample, "%p%p", ptr, ptr);
    for (uint i = 0; i < KEYLEN; ++i)
        number[i] = sample[(i + 2) % 40];
    free(ptr);
    free(sample);
    for (uint i = 0; i < KEYLEN; ++i)
    {
        number[i] += 16 - i - number[i + 1];
        while(!ft_isalnum(number[i]))
        {
            number[i] = (number[i]+ 1) + '0';
        }
    }
    return (strdup(number));
}

int encrypt_text_section(char *mem, int text_sect, uint size)
{
    char *key = NULL;
    unsigned long long bitkey = 0;
    Elf64_Shdr *shdr = NULL;
    char *ptr;

    shdr = (void*)mem + text_sect;
    key = generate_key(text_sect);
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