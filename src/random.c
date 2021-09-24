#include "../inc/woody_woodpacker.h"

char ft_rand_bit()
{
    char c[10];
    char *ptr;
    ptr = malloc(sizeof(char));
    sprintf(c, "%p", ptr);
    free(ptr);
    printf("%s\n", c );
    return ((c[0] + c[1] + c[2] +c[3] + c[4]) % 2);
}

// int ft_rand(void)
// {
//     int n;
//     int *p;

//     p = malloc(sizeof(int))
    
// }

