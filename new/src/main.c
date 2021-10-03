#include "../inc/woody.h"
char payload[] = {
	'\x9c', '\x50', '\x57', '\x56', '\x54', '\x52', '\x51', '\x41', '\x50', '\x41', '\x51', '\x41', '\x52', '\xbf', '\x01', '\x00', '\x00', '\x00', '\xeb', '\x0d', '\x5e', '\xba', '\x0f', '\x00', '\x00', '\x00', '\x48', '\x89', '\xf8', '\x0f', '\x05', '\xeb', '\x15', '\xe8', '\xee', '\xff', '\xff', '\xff', '\x2e', '\x2e', '\x2e', '\x2e', '\x57', '\x4f', '\x4f', '\x44', '\x59', '\x2e', '\x2e', '\x2e', '\x2e', '\x2e', '\x0a', '\x41', '\x5a', '\x41', '\x59', '\x41', '\x58', '\x59', '\x5a', '\x5c', '\x5e', '\x5f', '\x58', '\x9d', '\xb8', '\x43', '\x42', '\x42', '\x42', '\xff', '\xe0'};

Elf64_Ehdr *g_hdr = 0;
Elf64_Addr *g_strtab = 0;
size_t g_binsize = 0;

static int ft_error(const char *s)
{
	dprintf(2, "%s: %s\n", "woody_woodpacker", s);
	exit(-1);
}

static Elf64_Ehdr *is_64_elf(char *mem, size_t size)
{
	Elf64_Ehdr *hdr = NULL;

	if (size < sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(Elf64_Shdr))
		return (NULL);
	hdr = malloc(sizeof(*hdr));
	memcpy(hdr, mem, sizeof(*hdr));
	if (!memcmp(ELFMAG, hdr->e_ident, ft_strlen(ELFMAG)) &&
		hdr->e_ident[EI_CLASS] == ELFCLASS64)
		return (hdr);
	else
		free(hdr);
	return (NULL);
}

static int duplicate_binary(char *mem, size_t size)
{
	int woodyfd;
	size_t written;

	woodyfd = open("woody", O_CREAT | O_TRUNC | O_RDWR);
	if (woodyfd < 3)
		return (-1);
	if ((written = write(woodyfd, mem, size)) < size)
		return (-2);
	return (woodyfd);
}

// static void find_strtab(void *mem)
// {
//     Elf64_Shdr *shdr;

//     for (int i = 0; i < g_hdr->e_shnum; ++i)
//     {
//         shdr = (Elf64_Shdr *)(mem + g_hdr->e_shoff + (i * sizeof(*shdr)));
//         if (shdr->sh_type == SHT_STRTAB)
//             g_strtab = mem + shdr->sh_offset;
//     }
// }

// static const char *get_section_name(void *mem, int index)
// {
//     char *ptr;

//     if (g_strtab == 0)
//         find_strtab(mem);
//     if (index < 0 || g_hdr == NULL ||g_strtab == 0)
//         return ("");
//     if ((void*)(g_strtab + index) > (void*)(mem + g_binsize))
//         return ("");
//     ptr = (void*)(g_strtab + index);
//     return (ptr);
// }

Elf64_Addr find_cave(void *mem, size_t size)
{
	Elf64_Phdr *phdr = NULL;
	Elf64_Addr start = 0, end = 0, i = 0, j = 0;

	phdr = mem + g_hdr->e_phoff;
	for (i = 0; i < g_hdr->e_phnum; ++i)
	{
		if (i * sizeof(g_hdr->e_shnum) > size - g_hdr->e_phoff)
			return (0);
		// printf("%c%c%c\n",
		//     phdr[i].p_flags & PF_X ? 'x' : ' ',
		//     phdr[i].p_flags & PF_W ? 'w' : ' ',
		//     phdr[i].p_flags & PF_R ? 'r' : ' '
		// );
		if (phdr[i].p_filesz > 0 && phdr[i].p_filesz == phdr[i].p_memsz && (phdr[i].p_flags & PF_X))
		{
			start = phdr[i].p_offset + phdr[i].p_filesz;
			end = start + sizeof(payload);
			for (j = 0; j < g_hdr->e_phnum; ++j)
			{
				if (phdr[j].p_offset >= start && phdr[j].p_offset < end && phdr[j].p_filesz > 0)
					break;
			}
			if (j == g_hdr->e_phnum)
				return (i);
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	int woodyfd;

	g_hdr = NULL;
	if (ac != 2)
	{
		dprintf(2, "woody_woodpacker: usage: program binary_to_infect");
		exit(-1);
	}
	int fd;
	size_t g_binsize;

	fd = open(av[1], O_RDONLY);
	if (fd < 3)
		ft_error("error: binary could not be read.");
	g_binsize = lseek(fd, 0, SEEK_END);
	char *mem = mmap(NULL, g_binsize, PROT_READ, MAP_PRIVATE, fd, 0);
	g_hdr = is_64_elf(mem, g_binsize);
	if (!g_hdr)
	{
		munmap(mem, g_binsize);
		ft_error("error: binary not compatible");
	}
	woodyfd = duplicate_binary(mem, g_binsize);
	munmap(mem, g_binsize);
	if (woodyfd > 0)
	{
		mem = mmap(NULL, g_binsize, PROT_WRITE, MAP_PRIVATE, woodyfd, 0);
		Elf64_Off cave = find_cave(mem, g_binsize);
		if (cave)
		{
			;
		}
		else
			printf("this binary cannot be injected: no executable region\n");
		munmap(mem, g_binsize);
		close(woodyfd);
	}
	else
	{
		printf("error: file could not be duplicated\n");
	}
	free(g_hdr);
	close(fd);
}