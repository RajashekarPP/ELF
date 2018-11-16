#ifndef __PROGRAM_HEADER__
#define __PROGRAM_HEADER__

#include"datatypes.h"

//p_type
#define PT_NULL 	0
#define PT_LOAD 	1
#define PT_DYNAMIC 	2
#define PT_INTERP 	3
#define PT_NOTE 	4
#define PT_SHLIB 	5
#define PT_PHDR 	6
#define PT_LOPROC 	0x70000000
#define PT_HIPROC 	0x7fffffff



typedef struct{

	Elf32_Word	p_type;
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;
	Elf32_Word	p_align;

}Elf32_Phdr;



#endif
