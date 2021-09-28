#include "../inc/woody_woodpacker.h"

static void	usage(void)
{
	printf("%s: usage: %s <program_name>\n", BIN, BIN);
	exit(-1);
}


int	main(int argc, char *argv[])
{
	int	ret;

	ret = 0;
	if (argc != 2)
		usage();
	if (!is_elf(argv[1]))
	{
		printf("File architecture not suported. x86_64 only\n");
		exit(-1);
	}
	g_elf.key = generate_key();
	//printf("GENERATED KEY \"%s\", len: %lu\n", g_elf.key, ft_strlen(g_elf.key));
	free(g_elf.key);
	exit(ret);
}
