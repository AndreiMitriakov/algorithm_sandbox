#define ELF_NIDENT	16
#include <stdio.h>

// Эта структура описывает формат заголовока ELF файла
struct elf_hdr {
	std::uint8_t e_ident[ELF_NIDENT];
	std::uint16_t e_type;
	std::uint16_t e_machine;
	std::uint32_t e_version;
	std::uint64_t e_entry;
	std::uint64_t e_phoff;
	std::uint64_t e_shoff;
	std::uint32_t e_flags;
	std::uint16_t e_ehsize;
	std::uint16_t e_phentsize;
	std::uint16_t e_phnum;
	std::uint16_t e_shentsize;
	std::uint16_t e_shnum;
	std::uint16_t e_shstrndx;
} __attribute__((packed));


uintptr_t entry_point(const char *name)
{
    FILE *fptr;
    fptr = fopen(name,"r");

    struct elf_hdr * num = (struct elf_hdr*)malloc(sizeof(elf_hdr));
    fread(num, sizeof(elf_hdr), 1, fptr); 
    uintptr_t entry = num->e_entry;
    free(num);
    fclose(fptr);
    return entry;
}


