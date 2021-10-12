#include "../inc/woody.h"

extern Elf64_Addr g_baseaddr;
extern Elf64_Ehdr *g_hdr;
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

void patch_payload(Elf64_Addr new_entry, Elf64_Addr orig_entry, t_payload *payload)
{
	Elf64_Addr jmp;
	Elf64_Addr addr = 0;

	jmp = (Elf64_Addr)-(new_entry - orig_entry - payload->len);
	(void)new_entry;
	// print_payload(payload);
	orig_entry += g_baseaddr;
	// bzero(&payload->data[payload->len - 4], 4);
	ft_memcpy(&payload->data[payload->len - 4], &orig_entry, 4);
	print_payload(payload);
	addr = (Elf64_Addr)&payload->data[payload->len - 4];
	if (addr) {
		ft_memcpy(&addr, (void *)&jmp, sizeof(jmp));
		printf("e_entry: %p -> new e_entry %p ", (void*)orig_entry, (void*)new_entry);

		printf("jmp: %ld. new_entry - orig_entry: %x\n", jmp, (int)ft_abs(new_entry - orig_entry));
	}
	else
		dprintf(2, RED "woody_woodpacker: error: payload not found.\n" DEFAULT);
}