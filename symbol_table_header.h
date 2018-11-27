#ifndef __SYMBOL_TABLE__
#define	__SYMBOL_TABLE__

//used for st_info 
#define ELF32_ST_BIND(i) 	((i)>>4)
#define ELF32_ST_TYPE(i) 	((i)&0xf)
#define ELF32_ST_INFO(b,t) 	(((b)<<4)+((t)&0xf))

//st_info
#define STT_NOTYPE		0
#define STT_OBJECT		1
#define STT_FUN 		2
#define STT_SECTION		3
#define STT_FILE		4
#define STT_COMMON		5
#define STT_TLS 		6
#define STT_LOOS		10
#define STT_HIOS		12
#define STT_SPARC_REGISTER	14
#define STT_LOPROC		13
#define STT_HIPROC		15

//Binding of symbol
#define STB_LOCAL		0
#define STB_GLOBAL		1
#define STB_WEAK		2

//Shndx
#define STN_UNDEF		0
#define STN_ABS	 		65521

typedef struct{

	unsigned int		st_name;
	unsigned char		st_info;
	unsigned char		st_other;
	unsigned short int	st_shndx;
	unsigned long int	st_value;
	unsigned long int	st_size;
	
}Elf64_Sym;




#endif
