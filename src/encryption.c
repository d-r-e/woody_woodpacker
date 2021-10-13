#include "../inc/woody.h"

char *generate_key(int seed)
{
    char *ptr;
    char number[32];
    char *str;

    ptr = ft_calloc(1, seed % 100);
    sprintf(number, "%8p", ptr);
    free(ptr);
    str = ft_calloc(1, 17);
    sprintf(str, "%8s", number);
    for (uint i = 0; i < 16; ++i)
    {
        str[i] += 16 - i - str[i + 1];
        while(str[i] < 32 || str[i] > 126)
            str[i] += 42;
    }
    return (str);
}

int encrypt_text_section(char *mem, int text_sect, uint size)
{
    (void)mem;
    (void)text_sect;
    (void)size;
    char *key = generate_key(-42424242);
    printf("%s\n", key);
    free(key);
    return (0);
}