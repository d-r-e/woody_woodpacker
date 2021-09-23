#include "../inc/woody_woodpacker.h"

void	strerr(const char *s)
{
	dprintf(2, "%s: error: %s\n", BIN, s);
	if (g_elf.mem)
		munmap(g_elf.mem, g_elf.size);
	exit (-1);
}
