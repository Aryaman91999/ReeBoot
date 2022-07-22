#ifndef ELF_H
#define ELF_H

#include <efi.h>
#include <efilib.h>

typedef struct {
  unsigned char e_ident[16]; /* Magic number and other info */
  UINT16    e_type;         
  UINT16    e_machine;
  UINT32    e_version;      
  UINT64    e_entry;        /* Entry point virtual address */
  UINT64    e_phoff;        /* Program header table file offset */
  UINT64    e_shoff;        /* Section header table file offset */
  UINT32    e_flags;        /* Processor-specific flags */
  UINT16    e_ehsize;       
  UINT16    e_phentsize;    /* Program header table entry size */
  UINT16    e_phnum;        /* Program header table entry count */
  UINT16    e_shentsize;    /* Section header table entry size */
  UINT16    e_shnum;        /* Section header table entry count */
  UINT16    e_shstrndx;     /* Section header string table index */
} Elf64_Ehdr;

#define ELFMAGIC ("\177ELF")

#define ELF32   (1)
#define ELF64   (2)

#define ELFLSB  (1) /* little endian */
#define ELFMSB  (2) /* big endian */

/* architecture values in elf header */
#define X86 (0x3)
#define ARM (0x28)
#define X86_64 (0x3e)
#define AARCH64 (0xb7)

#define ELFSYSV (0) /* System V ABI */

/* ELF types */
#define ELF_RELOC   (1)
#define ELF_EXEC    (2)
#define ELF_SHARED  (3)
#define ELF_CORE    (4)

#endif //ELF_H
