#include "../inc/woody_woodpacker.h"

static void	usage(void)
{
	printf("%s: usage: %s <program_name>\n", BIN, BIN);
	exit(-1);
}

int	main(int argc, char *argv[])
{
	int	ret;

	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	printf("c: %d\n", ft_rand_bit());
	ret = 0;
	if (argc != 2)
		usage();
	if (!is_elf(argv[1]))
	{
		printf("File architecture not suported. x86_64 only\n");
		exit(-1);
	}
	exit(ret);
}
