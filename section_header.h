#ifndef __SEGMENT_HEADER__
#define __SEGMENT_HEADER__

#include"datatypes.h"

//sh_type
#define SHT_NULL 	0
#define SHT_PROGBITS 	1
#define SHT_SYMTAB 	2
#define SHT_STRTAB 	3
#define SHT_RELA 	4
#define SHT_HASH 	5
#define SHT_DYNAMIC 	6
#define SHT_NOTE 	7 
#define SHT_NOBITS 	8
#define SHT_REL 	9
#define SHT_SHLIB 	10
#define SHT_DYNSYM 	11
#define SHT_LOPROC 	0x70000000
#define SHT_HIPROC 	0x7fffffff
#define SHT_LOUSER 	0x80000000 
#define SHT_HIUSER 	0xffffffff	

//sh_flags
#define SHF_WRITE	0x1
#define SHF_ALLOC	0x2
#define SHF_EXECINSTR	0x4
#define SHF_MASKPROC	0xf0000000


typedef struct{

	Elf32_Word	sh_name;	
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;

}Elf32_Shdr;


#endif
