#include "../inc/woody_woodpacker.h"

int ft_rand(void)
{
    int rnd;
    char mem[32];
    int *n;
    static long m;

    rnd = open("/dev/random/", O_RDONLY);
    read(rnd, mem, 32);
    n = (void*)mem;
    m += *n;
    close(rnd);
    return (m ^ 0xDEADBABE);
}

char *generate_key()
{
    char key[PASS_LENGTH];

    for(int i = 0; i < PASS_LENGTH; i++)
    {
        key[i] = ft_rand() % 127;
        while (ft_isprint(key[i]) == 0)
        {
            key[i] = ft_rand() % 127;
        }
    }
    key[PASS_LENGTH - 1] = '\0';
    return (ft_strdup(key));
}