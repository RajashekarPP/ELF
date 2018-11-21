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
#define SHT_SHLIB 	0x0A	
#define SHT_DYNSYM 	0x0B
#define SHT_INIT_ARRAY	0x0E
#define SHT_FINI_ARRAY	0x0F
#define SHT_PREINIT_ARRAY	0x10
#define SHT_GROUP	0x11
#define SHT_SYMTAB_SHNDX	0x12
#define SHT_NUM		0x13	
#define SHT_LOOS	0x60000000
#define SHT_LOPROC 	0x70000000
#define SHT_HIPROC 	0x7fffffff
#define SHT_LOUSER 	0x80000000 
#define SHT_HIUSER 	0xffffffff	

//sh_flags
#define SHF_WRITE	0x1
#define SHF_ALLOC	0x2
#define SHF_EXECINSTR	0x4
#define SHF_MERGE	0x10
#define SHF_STRINGS	0x20
#define SHF_INFO_LINK	0x40
#define SHF_MASKPROC	0xf0000000


typedef struct{
	unsigned int	sh_name;	//4
	unsigned int	sh_type;	//4
	unsigned long	sh_flags;	//8
	unsigned long	sh_addr;	//8
	unsigned long	sh_offset;	//8
	unsigned long	sh_size;	//8
	unsigned int	sh_link;	//4
	unsigned int	sh_info;	//4
	unsigned long	sh_addralign;	//8
	unsigned long	sh_entsize;	//8
}Elf32_Shdr;


#endif
