#include "../inc/woody.h"

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
            str[i] -= KEYLEN - (13) * i;
    }
    return (str);
}

int encrypt_text_section(char *mem, int text_sect, uint size)
{
    if (!mem)
        return (-1);
    (void)text_sect;
    (void)size;
    char *key = NULL;
    
    key = generate_key(text_sect);
    printf("KEY: %s\n", key);

    free(key);
    return (0);
}