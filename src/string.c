#include "../inc/woody_woodpacker.h"

void	strerr(const char *s)
{
	(void)payload;
	dprintf(2, "%s: error: %s\n", BIN, s);
	if (g_elf.mem)
		munmap(g_elf.mem, g_elf.size);
	exit (-1);
}


void debug(const char *s)
{
	#ifdef DEBUG
		printf("%s\n", s);
	#endif
}