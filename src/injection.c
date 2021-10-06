#include "../inc/woody.h"

void patch_payload(Elf64_Addr new_entry, Elf64_Addr orig_entry, t_payload *payload)
{
	Elf64_Addr jmp;
	char *addr = NULL;
	long dummy = 0x4242424242424242;

	jmp = (Elf64_Addr)-(new_entry - orig_entry - payload->len);
	(void)new_entry;
	for (uint i = 0; i < payload->len - (sizeof(dummy) - 1) ; ++i) {
		if (ft_strncmp(&payload->data[i], (char*)&dummy, sizeof(dummy)) == 0)
			addr = &payload->data[i];
	}
	if (addr) {
		ft_memcpy(addr, (void *)&jmp, sizeof(jmp));
		printf("e_entry: %p -> new e_entry %p ", (void*)orig_entry, (void*)new_entry);

		printf("jmp: %ld. Offset between original start and new start: %x\n", jmp, abs(new_entry - orig_entry));
	}
	else
		dprintf(2, RED "woody_woodpacker: error: payload not found.\n" DEFAULT);
}