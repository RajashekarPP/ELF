#ifndef __SYMBOL_TABLE__
#define	__SYMBOL_TABLE__

#define ELF32_ST_BIND(i) 	((i)>>4)
#define ELF32_ST_TYPE(i) 	((i)&0xf)
#define ELF32_ST_INFO(b,t) 	(((b)<<4)+((t)&0xf))



typedef struct{

	unsigned int		st_name;
	unsigned char		st_info;
	unsigned char		st_other;
	unsigned short int	st_shndx;
	unsigned long int	st_value;
	unsigned long int	st_size;
	
}Elf64_Sym;




#endif
