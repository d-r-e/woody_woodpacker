#include "../inc/woody.h"

Elf64_Ehdr *g_hdr = 0;
size_t g_binsize = 0;
Elf64_Addr g_baseaddr = 0;

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
	ft_memcpy(hdr, mem, sizeof(*hdr));
	if (!ft_strncmp(ELFMAG, (const char *)hdr->e_ident, ft_strlen(ELFMAG)) &&
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

	if (size <= 0)
		return (-1);
	woodyfd = open("woody", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
	if (woodyfd < 0)
		return (-1);
	if ( (written = write(woodyfd, mem, size)) < size)
		return (-2);
	g_binsize = written;
	return (woodyfd);
}

/**
 * @param mem : pointer to mmapped memory of binary file
 * @returns virtual address in memory of the first PT_LOAD segment
 */
Elf64_Addr get_vaddr(void *mem)
{
	Elf64_Phdr *phdr = NULL;

	phdr = (Elf64_Phdr *)(mem + g_hdr->e_phoff);
	for (unsigned long i = 0; i < g_hdr->e_phnum; ++i)
	{
		if (phdr[i].p_type == PT_LOAD)
		{
			return phdr[i].p_vaddr;
			break;
		}
	}
	return 0;
}

static Elf64_Addr find_cave(void *mem, t_payload *payload)
{
	Elf64_Phdr *phdr = NULL;
	Elf64_Addr start = 0, end = 0;
	Elf64_Off new_entry = 0;
	unsigned long i = 0, j = 0;

	phdr = (Elf64_Phdr *)(mem + g_hdr->e_phoff);
	g_baseaddr = get_vaddr(mem);
	for (i = 0; i < (g_hdr->e_phnum); ++i)
	{
		if (phdr[i].p_filesz > 0 &&
			phdr[i].p_filesz == phdr[i].p_memsz && (phdr[i].p_flags & (PF_X)))
		{
			start = phdr[i].p_offset + phdr[i].p_filesz;
			end = start + payload->len;
			for (j = 0; j < g_hdr->e_phnum; ++j) /* corruption check */
			{
				if (phdr[j].p_offset >= start && phdr[j].p_offset < end && phdr[j].p_filesz > 0)
					break;
			}
			if (j == g_hdr->e_phnum)
			{
				new_entry = phdr[i].p_vaddr + phdr[i].p_filesz;
				if ((void*)mem + new_entry + payload->len > (void*)mem + g_binsize) {
					continue;
				}
				patch_payload(new_entry, g_hdr->e_entry, payload, mem);
				phdr[i].p_filesz += payload->len;
				phdr[i].p_memsz += payload->len;
				ft_memcpy(mem + new_entry, payload->data, payload->len);
				printf(CYAN "Found cave at offset -> " DEFAULT "0x%lx" CYAN ".\n" DEFAULT, start + i);
				return (i);
			}
		}
	}
	return (0);
}

/**
 * @fn get_payload
 * @param path file to get the payload from (binary opcode)
 * @returns a struct with the memory and the length of it
 * or NULL in case of error
 * */
t_payload *get_payload(const char *path)
{
	int fd;
	size_t size;
	t_payload *pld;

	fd = open(path, O_RDWR);
	if (fd < 0)
		return (NULL);
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (size == 0)
		return (NULL);
	// printf("Reading payload from %s, %lu bytes\n", path, size);
	pld = malloc(sizeof(*pld));
	pld->data = calloc(1, size);
	read(fd, pld->data, size);
	pld->len = size;
	close(fd);
	return (pld);
}

static int closefds(uint n, ...)
{
	va_list args;
	int fd;
	va_start(args, n);
	for (uint i = 0; i < n; ++i)
	{
		fd = va_arg(args, int);
		close(fd);
	}
	return(0);
}


int main(int ac, char **av)
{
	int woodyfd = 0;
	Elf64_Off cave = 0;
	int fd;
	g_hdr = NULL;
	t_payload *payload;
	int ret = 0;

	if (ac != 2)
		ft_error("usage: woody_woodpacker <binary>");
	print_woody(ac, av);
	size_t g_binsize;

	fd = open(av[1], O_RDONLY);
	if (fd < 3)
		ft_error("error: binary could not be read.");
	g_binsize = lseek(fd, 0, SEEK_END);
	if (g_binsize <= 0)
		printf("woody_woodpacker: error: file error: this binary is probably stripped\n");
	char *mem = mmap(NULL, g_binsize, PROT_READ, MAP_SHARED, fd, 0);
	if (mem == MAP_FAILED) {
		printf("error: mmap failed: this file cannot be read.\n");
		close(fd);
		exit(-1);
	}
	if (!(g_hdr = is_64_elf(mem, g_binsize))) {
		close(fd);
		munmap(mem, g_binsize);
		ft_error("error: binary not compatible");
	}
	else {
		woodyfd = duplicate_binary(mem, g_binsize);
		if (woodyfd <= 0)
			printf("woody_woodpacker: error: binary could not be copied");
	}
	if (ft_strcmp("woody", av[1])) {
		munmap(mem, g_binsize);
		mem = NULL;
	}
	if (woodyfd > 0) {
		payload = get_payload("asm/opcode");
		if (!payload || payload->len == 0)
			printf("woody_woodpacker: error: no payload");
		mem = mmap(NULL, g_binsize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, woodyfd, 0);
		if (mem != MAP_FAILED) {
			cave = find_cave(mem, payload);
			if (cave <= 0)
				printf("this binary cannot be injected: no executable region\n");
			munmap(mem, g_binsize);
		}
		else
			printf("mmap failed\n");
		free(payload->data);
		free(payload);
	}
	else if (woodyfd == -1)
		printf("error: " RED "error opening file.\n" DEFAULT);
	else if (woodyfd == -2)
		printf("error: " RED "file could not be duplicated.\n" DEFAULT);
	free(g_hdr);
	closefds(2, fd, woodyfd);
	if (!cave)
		ret = -1;
	exit(ret);
}
