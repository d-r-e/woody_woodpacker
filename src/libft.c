#include "../inc/woody.h"

/*! ft_strlen
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

/*! ft_strcmp
 * @param s1 string to compare
 * @param s2 string to compare
 * @returns (int) lexicographical difference of both strings, or 0 if equal
 */
int ft_strcmp(const char *s1, const char *s2)
{
	int diff = 0;

	if (!s1 || !s2)
		return(diff);
	while (s1[diff] && s2[diff] && s1[diff] == s2[diff])
		diff++;
	return s2[diff] - s1[diff];
}

/*!
 * @fn ft_strncmp
 * @param	s1	string to compare
 * @param	s2	string to compare
 * @param	n		compare up to this amount of bytes
 * @returns (int) lexicographical difference of both strings, or 0 if equal
 */
int ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	int diff = 0;

	if (!s1 || !s2)
		return(diff);
	while (--n > 0 && s1[diff] && s2[diff] && s1[diff] == s2[diff])
		diff++;
	return s2[diff] - s1[diff];
}
/*!
 * @fn ft_memcpy
 * @param	dest	destination of the copy
 * @param	src		source or origin, bytes to read
 * @param	n		size of the bytes to read
 * @returns a pointer to the destination or null if error
 */
void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src && n > 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return ((unsigned char*)dest);
}

void ft_puts(const char *s)
{
	if (!s)
		return;
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

long long ft_abs(long long val)
{
	return (val > 0 ? val : -val);
}