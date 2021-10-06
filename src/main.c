#include "../inc/woody.h"
char payload[] = {
'\x50','\x57','\x56','\x52','\xb8','\x01','\x00','\x00','\x00','\xbf','\x01','\x00','\x00','\x00','\x48','\x8d','\x35','\x1b','\x00','\x00','\x00','\xba','\x19','\x00','\x00','\x00','\x0f','\x05','\x5a','\x5e','\x5f','\x58','\x49','\xbd','\x42','\x42','\x42','\x42','\x42','\x42','\x42','\x42','\x41','\xff','\xe5','\x90','\x90','\x90','\x1b','\x5b','\x39','\x34','\x6d','\x2e','\x2e','\x2e','\x2e','\x57','\x4f','\x4f','\x44','\x59','\x2e','\x2e','\x2e','\x2e','\x2e','\x1b','\x5b','\x30','\x6d','\x0a','\x00'
};

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
	if (!ft_strncmp(ELFMAG, (const char*)hdr->e_ident, ft_strlen(ELFMAG)) &&
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

	woodyfd = open("woody", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
	if (woodyfd < 0)
		return (-1);
	if ((written = write(woodyfd, mem, size)) < size)
		return (-2);
	return (woodyfd);
}

void patch_payload(Elf64_Addr new_entry)
{
	Elf64_Addr jmp;
	char *addr = NULL;
	char dummy[] = "\x42\x42\x42\x42\x42\x42\x42\x42";

	jmp = (Elf64_Addr)(new_entry - g_hdr->e_entry);
	jmp = -abs(jmp) + sizeof(payload);
	(void)new_entry;
	for (uint i = 0; i < sizeof(payload) - 7; ++i) {
		if (strncmp(&payload[i], dummy, 8) == 0)
			addr = &payload[i];
	}
	if (addr) {
		ft_memcpy(addr, (void *)&jmp, sizeof(jmp));
		printf("addr: %p -> ", (void*)jmp);

		printf("rewritten original entrypoint into 0x%lx. Offset between original start and new start: %x\n", jmp, abs(new_entry - g_hdr->e_entry));
	}
	else
		dprintf(2, RED "woody_woodpacker: error: payload not found.\n" DEFAULT);
}

Elf64_Addr find_cave(void *mem)
{
	Elf64_Phdr *phdr = NULL;
	Elf64_Addr start = 0, end = 0;
	unsigned long i = 0, j = 0;

	phdr = (Elf64_Phdr *)(mem + g_hdr->e_phoff);
	for (i = 0; i < g_hdr->e_phnum; ++i)
	{
		if (phdr[i].p_type == PT_LOAD)
		{
			g_baseaddr = phdr[i].p_vaddr;
			break;
		}
	}
	for (i = 0; i < g_hdr->e_phnum; ++i) {
		if (phdr[i].p_filesz > 0 && phdr[i].p_filesz == phdr[i].p_memsz && (phdr[i].p_flags & PF_X))
		{
			start = phdr[i].p_offset + phdr[i].p_filesz;
			end = start + sizeof(payload);
			for (j = 0; j < g_hdr->e_phnum; ++j) /* corruption check */ {
				if (phdr[j].p_offset >= start && phdr[j].p_offset < end && phdr[j].p_filesz > 0)
					break;
			}
			if (j == g_hdr->e_phnum)
			{
				patch_payload(start + i);
				ft_memcpy(mem + start + i, payload, sizeof(payload));
				g_hdr->e_entry = start + i + g_baseaddr;
				memcpy(mem, g_hdr, sizeof(*g_hdr));
				printf(CYAN "Found cave at offset -> " DEFAULT "0x%lx" CYAN ".\n" DEFAULT, start + i);
				return (start + i);
			}
		}
	}
	return (0);
}



int main(int ac, char **av)
{
	int woodyfd = 0;
	Elf64_Off cave = 0;
	g_hdr = NULL;

	if (ac != 2)
		ft_error("usage: woody_woodpacker binary");
	if (!ft_strcmp("woody", av[1]))
		ft_error("error: this binary has already been infected!");
	int fd;
	size_t g_binsize;

	fd = open(av[1], O_RDONLY);
	if (fd < 3)
		ft_error("error: binary could not be read.");
	g_binsize = lseek(fd, 0, SEEK_END);
	char *mem = mmap(NULL, g_binsize, PROT_READ, MAP_SHARED, fd, 0);
	if (mem == MAP_FAILED)
		printf("first map failed\n");
	g_hdr = is_64_elf(mem, g_binsize);
	if (!g_hdr)
	{
		munmap(mem, g_binsize);
		ft_error("error: binary not compatible");
	}
	else
		woodyfd = duplicate_binary(mem, g_binsize);
	munmap(mem, g_binsize);
	mem = NULL;
	if (woodyfd > 0)
	{
		mem = mmap(NULL, g_binsize,PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, woodyfd, 0);
		if (mem != MAP_FAILED)
		{
			cave = find_cave(mem);
			if (cave > 0)
			{
				;
			}
			else
				printf("this binary cannot be injected: no executable region\n");
			munmap(mem, g_binsize);
		}
		else
			printf("mmap failed\n");
	}
	else if (woodyfd == -1)
		printf("error: " RED "file could not be duplicated\n" DEFAULT);
	else if (woodyfd == -2)
		printf("error: " RED "file could not be duplicated\n" DEFAULT);
	free(g_hdr);
	close(fd);
	if (woodyfd > 0)
		close(woodyfd);
	if (!cave)
		exit(-1);
	else
		exit(0);
}
