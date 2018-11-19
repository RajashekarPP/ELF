#include"elf_header.h"
#include"section_header.h"
#include"symbol_table_header.h"
#include"program_header.h"
#include"datatypes.h"

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
	int fd;
	if(argc < 1)
	{
		puts("execution format : ./a.out binary/elf_file");
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

	lseek(fd,0,SEEK_SET);

	printf("%s :\n",__FILE__);	
	printf("Magic :			%x %x %x %x\n",Elf_header.e_ident[EI_MAG0],Elf_header.e_ident[EI_MAG1],
							Elf_header.e_ident[EI_MAG2],Elf_header.e_ident[EI_MAG3]);
	printf("Class :			%d\n",Elf_header.e_ident[EI_CLASS]);
	switch(Elf_header.e_ident[EI_DATA])
	{
		case ELFDATANONE : puts("Invalid data Encodeing"); break;
		case ELFDATA2LSB  : puts("Little Endian"); break;
		case ELFDATA2MSB  : puts("Big Endian"); break;
	}

	printf("Version :		%d\n",Elf_header.e_ident[EI_VERSION]);
	switch(Elf_header.e_ident[EI_OSABI])
	{
		case 0 :printf("ABI : 			Unix System-V\n");break;
		case 1 :printf("ABI : 			HP-UX\n");break;
		case 2 :printf("ABI : 			NetBSD\n");break;
		case 3 :printf("ABI : 			LINUX\n");break;
		case 4 :printf("ABI : 			GNU Hurd\n");break;
		case 6 :printf("ABI : 			Solaris\n");break;
		case 12:printf("ABI : 			Open-BSD\n");break;
		case 9 :printf("ABI : 			Free BSD\n");break;
		default :puts("printing the default case WARNING");break;
	}
	printf("Type :			");
	switch(Elf_header.e_type)
	{
		case ET_NONE : puts("No file type"); break;
		case ET_REL  : puts("Relocatable file");break;
		case ET_EXEC : puts("Executable file");break;
		case ET_DYN  : puts("Shared Object File");break;
		case ET_CORE : puts("Core File");break;
		default : puts("unknown value"); break;
	}

	printf("Machine :		");	
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

#if 0
	unsigned long long int addr;
	lseek(fd,24,SEEK_SET);
	read(fd,&addr,sizeof(addr));
	printf("Entry point Address	0x%llx\n",addr);
#endif

	printf("Entry point Address 	0x%llx\n",Elf_header.e_entry); // this givs the offset address of the value present
	printf("program headers table offset address 		:  %llu\n",Elf_header.e_phoff);
	printf("section header table offset address  		:  %llu\n",Elf_header.e_shoff);
	printf("ELF Header size in bytes /this header size	:  %u\n",Elf_header.e_ehsize);
	printf("size of  program headers			:  %u\n",Elf_header.e_phentsize);
	printf("Number of program headers			:  %u\n",Elf_header.e_phnum);
	printf("Size of section headers 			:  %u\n",Elf_header.e_shentsize);
	printf("Total No of section headers			:  %u\n",Elf_header.e_shnum);
	printf("Section Header string table index		:  %u\n",Elf_header.e_shstrndx);

// shifting fd to section header offset address

	printf("offset : %ld\n",lseek(fd,64,SEEK_SET) );
	if(lseek(fd,Elf_header.e_shoff,SEEK_SET) != Elf_header.e_shoff)
	{
		perror("lseek ");
		return -1;
	}

	Shdr = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr));
	if(Shdr == NULL)
	{
		perror("malloc ");
		return -1;
	}
	if(read(fd,Shdr,sizeof(Elf32_Shdr)) != sizeof(Elf32_Shdr) )
	{
		perror("read ");
		return -1;
	}

	printf("index loc in string table 	:%lu\n",Shdr->sh_name);
	printf("first section offset address	:%llu\n",Shdr->sh_offset);
	printf("section  size			:%llu\n",Shdr->sh_size);

puts("**********************************");
printf("printing the program header details\n");

Elf32_Phdr Phdr;

printf("lseek of Phdr : %ld \n",lseek(fd,Elf_header.e_phoff,SEEK_SET) );

read(fd,&Phdr,sizeof(Phdr));

printf("p_type = 			%u \n",Phdr.p_type);
printf("p_offset of one segment = 	%lu \n",Phdr.p_offset);
printf("p_vaddr of segment	=	%lu \n",Phdr.p_vaddr);
printf("segment size =			%lu \n",Phdr.p_filesz);



	return 0;
}
