#ifndef __DYNAMIC__
#define __DYNAMIC__

//d_tag types
#define DT_NULL		0	
#define DT_NEEDED	1	
#define DT_PLTRELSZ	2	
#define DT_PLTGOT	3	
#define DT_HASH		4		
#define DT_STRTAB	5	
#define DT_SYMTAB	6		
#define DT_RELA		7			
#define DT_RELASZ	8			
#define DT_RELAENT	9			
#define DT_STRSZ	10			
#define DT_SYMENT	11			
#define DT_INIT		12			
#define DT_FINI		13			
#define DT_SONAME	14			
#define DT_RPATH	15			
#define DT_SYMBOLIC	16			
#define DT_REL		17			
#define DT_RELSZ	18			
#define DT_RELENT	19			
#define DT_PLTREL	20			
#define DT_DEBUG	21			
#define DT_TEXTREL	22			
#define DT_JMPREL	23			
#define DT_INIT_ARRAY	0x19
#define DT_INIT_ARRAYSZ	0x1b
#define DT_FINI_ARRAY	0x1a
#define	DT_FINI_ARRAYSZ	0x1c
#define	DT_GNU_HASH	0x6ffffef5
#define DT_VERNEED	0x6ffffffe
#define DT_VERNEEDNUM	0x6fffffff
#define DT_VERSYM	0x6ffffff0

typedef struct{
	signed long long int d_tag;
	union{
		unsigned long int	d_val;
		unsigned long long int 	d_ptr;
	}d_un;
}Elf32_Dyn;

#endif
