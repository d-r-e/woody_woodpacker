#include "../inc/woody_woodpacker.h"

static void usage()
{
    printf("%s: usage: %s <program_name>\n", BIN, BIN);
    exit (-1);
}

static int read_file(const char *s)
{
    int fd;

    fd = open(s, O_RDONLY, 0);
    if (fd < 0)
        strerr("file could not be read");
    close(fd);
    return (0);
}

int main(int argc, char **argv)
{
    int ret;

    ret = 0;
    if (argc != 2)
        usage();
    ret = read_file(argv[1]);
    exit(ret);
}
