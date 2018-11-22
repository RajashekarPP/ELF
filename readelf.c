#include"elf_header.h"
#include"section_header.h"
#include"program_header.h"
#include"dynamic_structure_header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main(int argc , char **argv)
{
	Elf32_Ehdr Elf_header;
	Elf32_Shdr *Shdr = NULL;
	int fd;			// file descriptor to read the binary/executable/linkable file
	unsigned short int index_str_t=0;

	if(argc < 1)
	{
		puts("execution format : ./a.out --format binary/elf_file");
		return -1;
	}

	fd = open(argv[1] ,O_RDONLY);
	if(fd == -1)
	{
		perror("open ");
		return -1;
	}

	printf("size of ELF structure is : %lu \n",sizeof(Elf32_Ehdr));
	
	//reding the binary file
	if(read(fd,&Elf_header,sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr) )
	{
		perror("read ");
		return -1;
	}

//	lseek(fd,0,SEEK_SET);

	printf("%s :\n",__FILE__);	
	printf("ELF Header:\n");
	printf("Magic :\t\t\t\t\t\t%x %x %x %x\n",Elf_header.e_ident[EI_MAG0],Elf_header.e_ident[EI_MAG1],
							Elf_header.e_ident[EI_MAG2],Elf_header.e_ident[EI_MAG3]);
	printf("Class :\t\t\t\t\t\t%d\n",Elf_header.e_ident[EI_CLASS]);
	printf("Data :\t\t\t\t\t\t");
	switch(Elf_header.e_ident[EI_DATA])
	{
		case ELFDATANONE : puts("Invalid data Encodeing"); break;
		case ELFDATA2LSB  : puts("Little Endian"); break;
		case ELFDATA2MSB  : puts("Big Endian"); break;
	}

	printf("Version :\t\t\t\t\t%d\n",Elf_header.e_ident[EI_VERSION]);
	switch(Elf_header.e_ident[EI_OSABI])
	{
		case 0 :printf("ABI : 	\t\t\t\t\tUnix System-V\n");break;
		case 1 :printf("ABI : 	\t\t\t\t\tHP-UX\n");break;
		case 2 :printf("ABI : 	\t\t\t\t\tNetBSD\n");break;
		case 3 :printf("ABI : 	\t\t\t\t\tLINUX\n");break;
		case 4 :printf("ABI : 	\t\t\t\t\tGNU Hurd\n");break;
		case 6 :printf("ABI : 	\t\t\t\t\tSolaris\n");break;
		case 12:printf("ABI : 	\t\t\t\t\tOpen-BSD\n");break;
		case 9 :printf("ABI : 	\t\t\t\t\tFree BSD\n");break;
		default :puts("printing the default case WARNING");break;
	}

	printf("Type :			\t\t\t");
	switch(Elf_header.e_type)
	{
		case ET_NONE : puts("No file type"); break;
		case ET_REL  : puts("Relocatable file");break;
		case ET_EXEC : puts("Executable file");break;
		case ET_DYN  : puts("Shared Object File");break;
		case ET_CORE : puts("Core File");break;
		default : puts("unknown value"); break;
	}

	printf("Machine :		\t\t\t");	
	switch(Elf_header.e_machine)
	{
		case EM_NONE : puts("No machine specific"); break;
		case EM_M32  : puts("AT&T WE 32100"); break;
		case EM_SPARC: puts("SPARC");break;
		case EM_386  : puts("Intel 80386"); break;
		case EM_68K  : puts("Motorola 68000");break;
		case EM_88K  : puts("Motorola 88000");break;
		case EM_MIPS : puts("MIPS RS3000");break;
		case 40 : puts("ARM");break;
		case 50 : puts("IA-64");break;
		case 62 : puts("x86-64");break;
		default : puts("Invalid input is given:-");break;
	}
	printf("Entry point Address 	\t\t\t0x%llx\n",Elf_header.e_entry); 	// this givs the offset address of the value present
	printf("program headers table offset address 		:  %llu\n",Elf_header.e_phoff);
	printf("section header table offset address  		:  %llu\n",Elf_header.e_shoff);
	printf("ELF Header size in bytes /this header size	:  %u\n",Elf_header.e_ehsize);
	printf("size of  program headers			:  %u\n",Elf_header.e_phentsize);
	printf("Number of program headers			:  %u\n",Elf_header.e_phnum);
	printf("Size of section headers 			:  %u\n",Elf_header.e_shentsize);
	printf("Total No of section headers			:  %u\n",Elf_header.e_shnum);
	printf("Section Header string table index		:  %u\n",Elf_header.e_shstrndx);
	
	index_str_t = Elf_header.e_shstrndx;

	Elf32_Phdr *Phdr = NULL;
	Phdr = (Elf32_Phdr *)malloc(sizeof(Elf32_Phdr)*Elf_header.e_phnum);
	lseek(fd,Elf_header.e_phoff,SEEK_SET);
	if(read(fd,Phdr,sizeof(*Phdr)*Elf_header.e_phnum) != sizeof(*Phdr)*Elf_header.e_phnum )
	{ 
		perror("read ");
		return -1;
	}

	printf("\nProgram Headers:\n");
	int i,index_dynamic_section=0;
	printf("  Type\t\tOffset\t\tVirtAddr\tFlags\n");
	for(i=0 ; i< Elf_header.e_phnum ;i++)
	{
		switch(Phdr[i].p_type)
		{	
			case PT_NULL 	:printf("  NULL\t");break;
			case PT_LOAD 	:printf("  LOAD\t");break;
			case PT_DYNAMIC :printf("  DYNAMIC");break;
			case PT_INTERP 	:printf("  INTERP");break;
			case PT_NOTE	:printf("  NOTE\t");break;	
			case PT_SHLIB	:printf("  SHLIB\t");break;
			case PT_PHDR	:printf("  PHDR\t");break;
			case 1685382480 :printf(" GNU_EH_FRAME");break;
			case 1685382481 :printf(" GNU_STACK");break;
			case 1685382482 :printf(" GNU_RELRO");break;
			default : printf("  INV\t");break;
		}

		printf("\t0x%lx\t",Phdr[i].p_offset);
		printf("\t0x%lx\t",Phdr[i].p_vaddr);
		if(!Phdr[i].p_vaddr)
		{
			printf("\t");
		}
		switch(Phdr[i].p_flags)
		{
			case 1:printf("E");break;
			case 2:printf("W");break;
			case 3:printf("W E");break;
			case 4:printf("R");break;
			case 5:printf("R E");break;
			case 6:printf("R W");break;
			case 7:printf("R W E");break;
		}
		puts("");
	}

	puts("");
	printf("Section Headers:\n");
	if(lseek(fd,Elf_header.e_shoff,SEEK_SET) != Elf_header.e_shoff)
	{
		perror("lseek ");
		return -1;
	}

	Shdr = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr)*Elf_header.e_shnum);

	if(Shdr == NULL)
	{
		perror("malloc ");
		return -1;
	}

	if(read(fd,Shdr,sizeof(Elf32_Shdr)*Elf_header.e_shnum) != sizeof(Elf32_Shdr)*Elf_header.e_shnum )
	{
		perror("read ");
		return -1;
	}

	printf("  Name\t\t    Type\t\tAddress\t\tOffset\t");
	printf("Size\tEntSize\tFlags\tLink\n");

	for(i=0;i<Elf_header.e_shnum ;i++)
	{
		char p[100];
		if((lseek(fd,Shdr[index_str_t].sh_offset,SEEK_SET)) != Shdr[index_str_t].sh_offset)
		{
			perror("lseek ");return -1;
		}
		lseek(fd,Shdr[i].sh_name,SEEK_CUR);
		read(fd,p,100);
		printf("%-20s",p);
		switch(Shdr[i].sh_type)
		{	
			case SHT_NULL 		: printf("NULL\t\t");break;
			case SHT_PROGBITS	: printf("PROGBITS\t\t");break;
			case SHT_SYMTAB 	: printf("SYMTAB\t\t");break;
			case SHT_STRTAB		: printf("STRTAB\t\t");break;
			case SHT_RELA 		: printf("RELA\t\t");break;
			case SHT_HASH		: printf("GNU_HASH\t");break;
			case SHT_DYNAMIC	: printf("DYNAMIC\t\t");index_dynamic_section=i;break;
			case SHT_NOTE		: printf("NOTE\t\t");break;
			case SHT_NOBITS		: printf("NOBITS\t\t");break;
			case SHT_REL		: printf("REL\t\t");break;
			case SHT_SHLIB		: printf("SHLIB\t\t");break;
			case SHT_DYNSYM		: printf("DYNSYM\t\t");break;
			case SHT_INIT_ARRAY	: printf("INIT_ARRAY\t\t");break;
			case SHT_FINI_ARRAY	: printf("FINI_ARRAY\t\t");break;
			case SHT_PREINIT_ARRAY	: printf("PREINIT_ARRAY\t");break;
			case SHT_GROUP		: printf("GROUP\t\t");break;
			case SHT_SYMTAB_SHNDX	: printf("SYMTAB_SHNDX\t");break;
			case SHT_NUM		: printf("NUM\t\t");break;
			case SHT_LOOS		: printf("LOOS\t\t");break;
			default 		: printf( "INV \t\t");break;
		}

		printf("0x%lx\t",Shdr[i].sh_addr);
		if(!Shdr[i].sh_addr)
		{
			printf("\t");
		}
		printf("0x%lx\t",Shdr[i].sh_offset);
		printf("0x%lx\t",Shdr[i].sh_size);
		printf("  %-3lu\t",Shdr[i].sh_entsize);	
		printf("  ");
		switch(Shdr[i].sh_flags)
		{
			case 1:printf("W");break;
			case 2:printf("A");break;
			case 3:printf("WA");break;
			case 4:printf("X");break;
			case 6:printf("AX");break;
			case 0x10:printf("M");break;
			case 0x20:printf("S");break;
			case 0x30:printf("MS");break;
			case 0x40:printf("I");break;
			case 0x42:printf("AI");break;
		//default : printf("%lu",Shdr[i].sh_flags);break;
		}
		printf("\t");
		printf("  %u\n",Shdr[i].sh_link);
	}

	puts("\nPrinting the Dynamic Section details");	

	if(lseek(fd,Shdr[index_dynamic_section].sh_offset,SEEK_SET) != Shdr[index_dynamic_section].sh_offset )
	{
		perror("lseek ");return -1;
	}

	//Variable to read the dynamic section structures	
	Elf32_Dyn *D = NULL;

	// this array of structures end with d_val == DT_NULL
	printf(" Tag\t\t\tType\t\t\tName/Value\n");
	while(1)
	{		
		D = (Elf32_Dyn *)malloc(sizeof(*D));
		if(D == NULL)
		{
			perror("malloc ");return -1;
		}
		if(read(fd,D,sizeof(*D)) != sizeof(*D) )		
		{
			perror("read ");return -1;	
		}
	//	printf("#### %ld ###\n",lseek(fd,0,SEEK_CUR));	
		printf("0x%-10lx\t\t",D->d_tag);
		switch(D->d_tag)
		{
			case DT_NULL	:printf("NULL\t");puts("");return 0;
			case DT_NEEDED	:printf("NEEDED\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_PLTRELSZ:printf("PLTRELSZ");printf("\t\t%u",D->d_un.d_val);break;
			case DT_PLTGOT	:printf("PLTGOT\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_HASH	:printf("HASH\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_STRTAB	:printf("STRTAB\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_SYMTAB	:printf("SYMTAB\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_RELA	:printf("RELA\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_RELASZ	:printf("RELASZ\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_RELAENT	:printf("RELAENT\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_STRSZ	:printf("STRSZ\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_SYMENT	:printf("SYMENT\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_INIT	:printf("INIT\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_FINI	:printf("FINI\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_SONAME	:printf("SONAME\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_RPATH	:printf("RPATH\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_SYMBOLIC:printf("SYMBOLIC\t");break;
			case DT_REL	:printf("REL\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_RELSZ	:printf("RELSZ\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_RELENT	:printf("RELENT\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_PLTREL	:printf("PLTREL\t");printf("\t\t%u",D->d_un.d_val);break;
			case DT_DEBUG	:printf("DEBUG\t");printf("\t\t0x%llx",D->d_un.d_ptr);break;
			case DT_TEXTREL	:printf("TEXTREL\t");break;
			case DT_JMPREL	:printf("JMPREL\t");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_INIT_ARRAY:printf("INIT_ARRAY");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_INIT_ARRAYSZ:printf("INIIT_ARRAYSZ");printf("\t\t%u",D->d_un.d_val);break;
			case DT_FINI_ARRAY:printf("FINI_ARRAY");printf("\t\t%llx",D->d_un.d_ptr);break;
			case DT_FINI_ARRAYSZ:printf("FINI_ARRAYSZ");printf("\t\t%u",D->d_un.d_val);break;
			case 0x6ffffef5:printf("GNU_HASH");printf("\t\t%llx",D->d_un.d_ptr);break;
			case 0x6ffffffe	:printf("VERNEED");printf("\t\t\t%llx",D->d_un.d_ptr);break;
			case 0x6fffffff:printf("VERNEEDUM");printf("\t\t%u",D->d_un.d_val);break;
			case 0x6ffffff0	:printf("VERSYM");printf("\t\t\t%llx",D->d_un.d_ptr);break;
		//	default :printf("0x%x",D->d_tag);break;

		}
	//	printf("\t\t%x",D->d_un.d_val);
	//	printf("\t\t%llx",D->d_un.d_ptr);
	//	printf("*** %ld ***",lseek(fd,2,SEEK_CUR));
		puts("");
		free(D);
	}
	return 0;
}
