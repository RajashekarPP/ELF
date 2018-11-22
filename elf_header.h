#ifndef __ELF_HEADER__
#define __ELF_HEADER__

// for e_type
#define ET_NONE		0
#define ET_REL 		1  	//Relocatable file
#define ET_EXEC		2 	//Executable file
#define ET_DYN 		3 	//Shared object file
#define ET_CORE 	4 	//Core file
#define ET_LOPROC  	0xff00  //Processor-specific
#define ET_HIPROC  	0xffff  //Processor-specific

//for e_machine
#define EM_NONE 	0 	// No machine 
#define EM_M32 		1 	// AT&T WE 32100 
#define EM_SPARC 	2 	// SPARC
#define EM_386 		3 	// Intel 80386
#define EM_68K 		4 	// Motorola 68000 
#define EM_88K  	5	// Motorola 88000
#define EM_860 MIPS 	7 	// Intel 80860
#define EM_MIPS 	8 	// RS3000

//e_version
#define EV_NONE 	0 	//Invalid Version
#define EV_CURRENT 	1	//Current Version

//for e_ident[]
#define EI_MAG0 	0	//File identification
#define EI_MAG1 	1	//File identification
#define EI_MAG2 	2	//File identification
#define EI_MAG3 	3	//File identification
#define EI_CLASS	4	//File Class
#define EI_DATA		5	//Data Encoding
#define EI_VERSION	6	//File Version
#define EI_OSABI	7	//type of os platform
#define EI_PAD		9	//start of padding bytes
#define EI_NIDENT 	16	//size of e_ident[]

#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'

#define ELFCLASSNONE 	0	//Invalid class
#define ELFCLASS32	1	//32-bit objects
#define ELFCLASS64	2	//64-bit objects

#define ELFDATANONE 	0	//Invalid data encoding
#define ELFDATA2LSB	1	
#define ELFDATA2MSB	2

#if 0
typedef struct {

	unsigned char	e_ident[EI_NIDENT]; 	// 16
	Elf32_Half	e_type;			// 2
	Elf32_Half	e_machine;		// 2
	Elf32_Word	e_version;		// 4
	Elf32_Addr	e_entry;		// 8
	Elf32_Off	e_phoff;		// 8
	Elf32_Off	e_shoff;		// 8
	Elf32_Sword	e_flags;		// 4	
	Elf32_Half	e_ehsize;		// 2
	Elf32_Half	e_phentsize;		// 2
	Elf32_Half	e_phnum;		// 2 
	Elf32_Half	e_shentsize;		// 2
	Elf32_Half	e_shnum;		// 2
	Elf32_Half	e_shstrndx;		// 2

}Elf32_Ehdr;
#endif

typedef struct {

	unsigned char	e_ident[EI_NIDENT]; 	// 16
	unsigned short	e_type;			// 2
	unsigned short	e_machine;		// 2
	unsigned int	e_version;		// 4
	unsigned long long int  e_entry;	// 8
	unsigned long long int	e_phoff;	// 8
	unsigned long long int 	e_shoff;	// 8
	unsigned int	e_flags;		// 4	
	unsigned short	e_ehsize;		// 2
	unsigned short	e_phentsize;		// 2
	unsigned short	e_phnum;		// 2 
	unsigned short	e_shentsize;		// 2
	unsigned short	e_shnum;		// 2
	unsigned short	e_shstrndx;		// 2

}Elf32_Ehdr;

#endif
