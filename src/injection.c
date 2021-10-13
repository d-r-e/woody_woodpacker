#include "../inc/woody.h"

extern Elf64_Addr g_baseaddr;
extern size_t g_binsize;
extern Elf64_Ehdr *g_hdr;

// void find_text_section(char *mem, Elf64_Off *textsection, Elf64_Off *textsize)
// {

// }

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

Elf64_Phdr *get_first_ptload(char *mem)
{
	Elf64_Phdr *phdr = NULL;

	phdr = (Elf64_Phdr *)(mem + g_hdr->e_phoff);
	for (unsigned long i = 0; i < g_hdr->e_phnum; ++i)
	{
		if (phdr[i].p_type == PT_LOAD)
		{
			return (&phdr[i]);
			break;
		}
	}
	return NULL;
}

void patch_payload(Elf64_Off new_entry, Elf64_Off orig_entry, t_payload *payload, void *mem)
{
	Elf64_Ehdr *hdr = mem;
	Elf64_Word jmp;
	Elf64_Addr addr = 0;

	orig_entry += g_baseaddr;
	jmp = hdr->e_entry + g_baseaddr - (new_entry + payload->len) ;
	// print_payload(payload);
	// bzero(&payload->data[payload->len - 4], 4);
	addr = (Elf64_Addr)&payload->data[payload->len - 4];
	if (addr) {
		*(Elf64_Word*)(payload->data + payload->len - 4) = jmp;
	}
	else
		dprintf(2, RED "woody_woodpacker: error: payload not found.\n" DEFAULT);
	g_hdr->e_entry = new_entry;
	ft_memcpy(mem, g_hdr, sizeof(*g_hdr));
}