#include <stdio.h>
extern char _start;
int main()
{
    printf("0x%p\n", (void*)&_start);
}