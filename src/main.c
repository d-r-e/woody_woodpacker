#include "../inc/woody_woodpacker.h"

int main(int argc, char **argv)
{
    while (argc > 1 && *++argv)
        printf("%s\n", *argv);
    exit(0);
}