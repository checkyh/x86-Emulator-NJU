/*
#define EI_NIDENT       16
 typedef struct {
      unsigned char       e_ident[EI_NIDENT];
      Elf32_Half          e_type;
      Elf32_Half          e_machine;
      Elf32_Word          e_version;
      Elf32_Addr          e_entry;//程序入口的虚拟地址
      Elf32_Off           e_phoff;//程序头部表格和节区表格的偏移量， 以字节计算
      Elf32_Off           e_shoff;//程序头部表现在在ELF头部表结束后第一个字节开始
      Elf32_Word          e_flags;
      Elf32_Half          e_ehsize;/ELF头部的大小(字节)
      Elf32_Half          e_phentsize;//表明程序头部大小----Size of program headers
      Elf32_Half          e_phnum;//项目数----Number of program headers
      Elf32_Half          e_shentsize;//节头大小
      Elf32_Half          e_shnum;//节区数目
      Elf32_Half          e_shstrndx;
  } Elf32_Ehdr;

typedef struct elf32_phdr{
    Elf32_Word    p_type;
    Elf32_Off     p_offset;//Offset
    Elf32_Addr    p_vaddr;//VirtAddr
    Elf32_Addr    p_paddr;//PhysAddr
    Elf32_Word    p_filesz;//FileSiz
    Elf32_Word    p_memsz;//MemSiz
    Elf32_Word    p_flags;
    Elf32_Word    p_align;
} Elf32_Phdr;
程序头：
  Type           	Offset 	    VirtAddr  	PhysAddr      FileSiz     MemSiz  Flg    Align
  LOAD           	0x001000 0x00100000 0x00100000 0x003c0 0x003c0 RWE 0x1000
  GNU_STACK    0x000000 0x00000000 0x00000000 0x00000 0x00000 RW   0x10

你需要找出每一个program header的Offset, VirtAddr, FileSiz和MemSiz这些参数. 
其中相对文件偏移Offset指出相应segment的内容从ELF文件的第Offset字节开始, 
在文件中的大小为FileSiz, 它需要被分配到以VirtAddr为首地址的虚拟内存位置, 
在内存中它占用大小为MemSiz. 但现在NEMU还没有虚拟地址的概念, 
因此你只需要把VirtAddr当做物理地址来使用就可以了, 也就是说, 
这个segment使用的内存就是[VirtAddr, VirtAddr + MemSiz)这一连续区间, 
然后将segment的内容从ELF文件中读入到这一内存区间, 
并将[VirtAddr + FileSiz, VirtAddr + MemSiz)对应的物理区间清零. 
*/
#include <elf.h>
#include <string.h>
#include<stdio.h>
#include "trap.h"
 #define PT_LOAD 1

void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *ph =(void *)elf+elf->e_ehsize;
	int ph_num=elf->e_phnum;
 	int i=1;
 	printf("%x\n",ph );
 	for (i=1;i<=ph_num;i++)
 	{
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) {
		memcpy(((void(*)(void)) ph->p_vaddr),((void(*)(void)) ph->p_offset),ph->p_memsz);
		
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
 	
 		memset(((void(*)(void)) (ph->p_vaddr+ph->p_filesz)),0,ph->p_memsz-ph->p_filesz);
 			

			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
 		}
 
		
	}
	/* Here we go! */
	((void(*)(void)) elf->e_entry) ();
	/* When returning from the program, it is executed successfully */
	HIT_GOOD_TRAP;
}