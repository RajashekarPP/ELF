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

	unsigned int	p_type;     	// 4
	signed int	p_flags;	// 4
	unsigned long	p_offset;	// 8
	unsigned long	p_vaddr;	// 8
	unsigned long	p_paddr;	// 8
	unsigned long	p_filesz;	// 8
	unsigned long	p_memsz;	// 8
	unsigned long	p_align;	// 8

}Elf32_Phdr;



#endif
