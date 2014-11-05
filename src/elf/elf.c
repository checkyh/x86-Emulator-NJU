/*
typedef struct{
 Elf32_Word st_name;
 Elf32_Addr st_value;
 Elf32_Word st_size;
 Unsigned char st_info;
 Unsigned char st_other;
 Elf32_Half st_shndx;
 }Elf32_Sym;
*/
#include "memory.h"

#include <stdlib.h>
#include <elf.h>
#include <sys/stat.h>

static int main_argc;
static char **main_argv;
static char *exec_file;

static char *strtab = NULL;//字符串表
static Elf32_Sym *symtab = NULL;//符号表
static int nr_symtab_entry;//符号表的表项

void set_main_args(int argc, char *argv[]) {
	main_argc = argc;
	main_argv = argv;
	exec_file = main_argv[0];
}

/* Load symbol table and string table from ELF file for future use.
 * For detail information, please refer to "man elf". */
void load_table() {
	FILE *fp = fopen(exec_file, "rb");
	test(fp, "file not exist!");

	uint8_t buf[4096];
	/* Read the first 4096 bytes from the exec_file.
	 * They should contain the ELF header and program headers. */
	fread(buf, 4096, 1, fp);

	/* The first several bytes contain the ELF header. */
	Elf32_Ehdr *elf = (void *)buf;
	char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

	/* Check ELF header */
	assert(memcmp(elf->e_ident, magic, 4) == 0);		// magic number
	assert(elf->e_ident[EI_CLASS] == ELFCLASS32);		// 32-bit architecture
	assert(elf->e_ident[EI_DATA] == ELFDATA2LSB);		// littel-endian
	assert(elf->e_ident[EI_VERSION] == EV_CURRENT);		// current version
	assert(elf->e_ident[EI_OSABI] == ELFOSABI_SYSV || 	// UNIX System V ABI
			elf->e_ident[EI_OSABI] == ELFOSABI_LINUX); 	// UNIX - GNU
	assert(elf->e_ident[EI_ABIVERSION] == 0);			// should be 0
	assert(elf->e_type == ET_EXEC);						// executable file
	assert(elf->e_machine == EM_386);					// Intel 80386 architecture
	assert(elf->e_version == EV_CURRENT);				// current version


	/* Load section header table */
	uint32_t sh_size = elf->e_shentsize * elf->e_shnum;
	Elf32_Shdr *sh = malloc(sh_size);
	fseek(fp, elf->e_shoff, SEEK_SET);
	fread(sh, sh_size, 1, fp);

	/* Load section header string table */
	char *shstrtab = malloc(sh[elf->e_shstrndx].sh_size);
	fseek(fp, sh[elf->e_shstrndx].sh_offset, SEEK_SET);
	fread(shstrtab, sh[elf->e_shstrndx].sh_size, 1, fp);

	int i;
	for(i = 0; i < elf->e_shnum; i ++) {
		if(sh[i].sh_type == SHT_SYMTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".symtab") == 0) {
			/* Load symbol table from exec_file */
			symtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			fread(symtab, sh[i].sh_size, 1, fp);
			nr_symtab_entry = sh[i].sh_size / sizeof(symtab[0]);
		}
		else if(sh[i].sh_type == SHT_STRTAB && 
				strcmp(shstrtab + sh[i].sh_name, ".strtab") == 0) {
			/* Load string table from exec_file */
			strtab = malloc(sh[i].sh_size);
			fseek(fp, sh[i].sh_offset, SEEK_SET);
			fread(strtab, sh[i].sh_size, 1, fp);
		}
	}

	free(sh);
	free(shstrtab);

	/* Double check */
	assert(strtab != NULL && symtab != NULL);

	fclose(fp);
}

void load_prog() {
	struct stat st;
	stat(exec_file, &st);
	assert(st.st_size < 0xa0000);

	FILE *fp = fopen(exec_file, "rb");
	assert(fp);

	/* We do not have a virtual hard disk now. Before we have a virutal hard disk,
	 * the beginning of physical memory is used as a "disk". The loader in NEMU
	 * will load the program from this "disk" (at the beginning of the physical
	 * memory).
	 */
	fread(hwa_to_va(0), st.st_size, 1, fp);
	fclose(fp);
}

int read_symtab(uint32_t lens)
{
	 printf("st_name:%s\n",strtab+symtab[lens].st_name);
	 printf("st_value:%x\n", symtab[lens].st_value);
	 printf("st_size:%d\n", symtab[lens].st_size);
	 printf("st_info:%x\n", symtab[lens].st_info);
	 printf("st_other:%d\n", symtab[lens].st_other);
	 printf("st_shndx:%x\n", symtab[lens].st_shndx);
	return 1;
}
int symmatch(char *expr)
{
	int i=1;
	for (i=1;i<=nr_symtab_entry;i++)
	{
		printf("%s\n",strtab+symtab[i].st_name );

		if(symtab[i].st_info==12||symtab[i].st_info==13) {printf("%s",strtab+symtab[i].st_name); if (strcmp(expr,strtab+symtab[i].st_name)==0) return i;}
	}
	return -1;
}
uint32_t symvalue(int num)
{
	return symtab[num].st_value;
}
