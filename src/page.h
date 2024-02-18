#ifndef _PAGE_H
#define _PAGE_H

// get the page table entry, return NULL if not valid
pte_t* get_addr_pte(unsigned long vaddr);
// get the refcount of the page
unsigned int get_page_refcount(pte_t *pte);
bool is_page_special(pte_t *pte);
bool is_vaddr_special(unsigned long vaddr);

void page_refer(pte_t *pte);
void page_unrefer(pte_t *pte);
void page_init_flag(pte_t *pte);
void object_init_flag(unsigned long vaddr, size_t size);

#define PTE_REFCOUNT_SHIFT 52
#define PTE_REFCOUNT_MASK 0x00F0000000000000
#define PTE_REFCOUNT_MAX 0xF

#endif