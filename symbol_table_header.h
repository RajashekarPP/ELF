#ifndef __SYMBOL_TABLE__
#define	__SYMBOL_TABLE__

#include"datatypes.h"

#define ELF32_ST_BIND(i) 	((i)>>4)
#define ELF32_ST_TYPE(i) 	((i)&0xf)
#define ELF32_ST_INFO(b,t) 	(((b)<<4)+((t)&0xf))



typedef struct{

	Elf32_Word	st_name;
	Elf32_Addr	st_value;
	Elf32_Word	st_size;
	unsignedchar	st_info;
	unsignedchar	st_other;
	Elf32_Half	st_shndx;

}Elf32_Sym;




#endif
