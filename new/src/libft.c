#include "../inc/woody.h"

/*!
 * ft_strlen
 * @param s string to read
 * @returns (unsigned long) length of the string
 */
unsigned long	ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s && s[i])
		++i;
	return (i);
}
