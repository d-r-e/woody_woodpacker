#include "../inc/woody_woodpacker.h"

void	strerr(const char *s)
{
	dprintf(2, "%s: error: %s\n", BIN, s);
	exit (-1);
}
