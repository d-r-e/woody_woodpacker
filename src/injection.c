#include "../inc/woody.h"

extern Elf64_Addr g_baseaddr;
extern size_t g_binsize;
extern Elf64_Ehdr *g_hdr;

static Elf64_Off get_strtab(Elf64_Ehdr *hdr, char *mem)
{
	Elf64_Shdr *shdr = (void*)mem + hdr->e_shoff;

	return shdr[hdr->e_shstrndx].sh_offset;
}

static int find_text_section(char *mem, Elf64_Off *textoffset, Elf64_Off *textsize)
{
	Elf64_Shdr	*shdr = (void*)mem + g_hdr->e_shoff;
	const char	*name;
	Elf64_Off	strtab;

	strtab = get_strtab(g_hdr, mem);
	for (uint i = 0; i < g_hdr->e_shnum; ++i)
	{
		name = (void*)mem + strtab + shdr[i].sh_name;
		// printf("%s\n", name);	
		if (!ft_strcmp(".text", name))
		{
			*textoffset = shdr[i].sh_offset;
			*textsize = shdr[i].sh_size;
			return (i);
		}
	}
	*textoffset = 0;
	*textsize = 0;
	return (-1);
}

 void print_payload(t_payload *payload)
{
	uint WIDTH = 32; 
	for (uint i = 0; i < payload->len; ++i)
	{
		printf("%.2x ", (unsigned char)payload->data[i]);
		if (i % WIDTH == WIDTH - 1)
			printf("\n");
	}
	printf("\n");
}

// static Elf64_Phdr *get_first_ptload(char *mem)
// {
// 	Elf64_Phdr *phdr = NULL;

// 	phdr = (Elf64_Phdr *)(mem + g_hdr->e_phoff);
// 	for (unsigned long i = 0; i < g_hdr->e_phnum; ++i)
// 	{
// 		if (phdr[i].p_type == PT_LOAD)
// 		{
// 			return (&phdr[i]);
// 			break;
// 		}
// 	}
// 	return NULL;
// }

void inject_address(t_payload *payload, long long value)
{
	char	*key = "\xca\xca\xca\xca";

	for (uint i = 0; i < payload->len - ft_strlen(key); i++)
	{
		if (ft_strncmp(&payload->data[i], key, ft_strlen(key)) == 0)
		{
			ft_memcpy(&payload->data[i], (char*)&value, ft_strlen(key));
			break;
		}
	}
}

void patch_payload(Elf64_Off new_entry, t_payload *payload, void *mem)
{
	Elf64_Word	jmp;
	Elf64_Off	text_offset;
	Elf64_Off	size;
	long long	bitkey;

	find_text_section(mem, &text_offset, &size);
	bitkey = encrypt_text_section(mem, text_offset, size);
	// print_payload(payload);
	inject_address(payload, new_entry);
	inject_address(payload, text_offset);
	inject_address(payload, size);
	inject_address(payload, bitkey);
	print_payload(payload);
	//printf("text_offset offset %lu text_offset size %u\n", text_offset, size);
	jmp = ((Elf64_Ehdr*)(mem))->e_entry + g_baseaddr - (new_entry + payload->len);

	*(Elf64_Word*)(payload->data + payload->len - 4) = jmp;


	g_hdr->e_entry = new_entry;
	ft_memcpy(mem, g_hdr, sizeof(*g_hdr));
}