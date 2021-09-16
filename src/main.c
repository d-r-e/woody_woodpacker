#include "../inc/woody_woodpacker.h"

static void	usage(void)
{
	printf("%s: usage: %s <program_name>\n", BIN, BIN);
	exit(-1);
}

static	int	read_file(const char *s)
{
	int	fd;
	int woodyfd;

	fd = open(s, O_RDONLY, 0);
	if (fd < 0)
		strerr("file could not be read");
	woodyfd = open("woody", O_CREAT | O_APPEND | O_TRUNC, 0755);
	close(woodyfd);
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc != 2)
		usage();
	printf("iself? %d\n", is_elf(argv[1]));
	ret = read_file(argv[1]);
	exit(ret);
}
