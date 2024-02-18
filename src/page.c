#include <linux/kernel.h>
#include <linux/module.h>

#include <asm/tlbflush.h>
#include <asm/pgtable_types.h>
#include <stdbool.h>

#include "page.h"
#include "alloc.h"
#include "config.h"

pte_t* get_addr_pte(unsigned long vaddr){
	unsigned int l;
	pte_t* pte;

	pte = lookup_address(vaddr, &l);
	// printk("BoKASAN: get_addr_pte: vaddr: 0x%lx, pte: 0x%px, l: %d\n", vaddr, pte, l);

	if(l == PG_LEVEL_4K){
		if (unlikely(pte_none(*pte))) {
			printk("BoKASAN warning: pte_none @ %lu, pid %u\n", vaddr, current->pid);
			dump_stack();
		} else {
			return pte;
		}
	} else if(l == PG_LEVEL_2M){
		// printk("BoKASAN warning: [get_addr_pte] page 2M %lx, pte: %px\n", vaddr, pte);
	} else{
		// printk("BoKASAN warning: [get_addr_pte] page 4K nor 2M %lx, l %u\n", vaddr, l);
	}

	return NULL;
}

inline bool is_page_special(pte_t *pte){
	pteval_t val;

	val = native_pte_val(*pte);

	// if ((val & _PAGE_SPECIAL) == _PAGE_SPECIAL) {
	// 	printk("BoKASAN: is_page_special: pte: %px, present: %d, special: %d, refcount: %u\n", pte, (val & _PAGE_PRESENT) == _PAGE_PRESENT, (val & _PAGE_SPECIAL) == _PAGE_SPECIAL, get_page_refcount(pte));
	// }

	if ((val & _PAGE_SPECIAL) == _PAGE_SPECIAL) {
		return true;
	}
	return false;
}

inline bool is_vaddr_special(unsigned long vaddr){
	pte_t *pte;

	pte = get_addr_pte(vaddr);
	if(pte){
		return is_page_special(pte);
	}
	return false;
}

inline unsigned int get_page_refcount(pte_t *pte){
	pteval_t val;

	val = native_pte_val(*pte);

	return (unsigned int)((val & PTE_REFCOUNT_MASK) >> PTE_REFCOUNT_SHIFT);
}

void page_refer(pte_t *pte)
{
	pteval_t val = native_pte_val(*pte);
	unsigned long count = get_page_refcount(pte);

#if DEBUG
	if (count > 0)
		printk("BoKASAN: page_refer: pte: %px, refcount: %lu\n", pte, count);
#endif

	val &= ~PTE_REFCOUNT_MASK;	// clear refcount
	if (count < PTE_REFCOUNT_MAX) {
		if (count == 0) {
			val |= _PAGE_PRESENT;
		}
		val |= (count + 1) << PTE_REFCOUNT_SHIFT;
		set_pte(pte, __pte(val));
		__flush_tlb_all();
	} else {
		// printk("BoKASAN warning: [page_refer] refcount overflow, pte: %px\n", pte);
		// dump_stack();
	}
}

void page_unrefer(pte_t *pte)
{
	pteval_t val = native_pte_val(*pte);
	unsigned long count = get_page_refcount(pte);

#if DEBUG
	if (count > 1)
		printk("BoKASAN: page_unrefer: pte: %px, refcount: %lu\n", pte, count);
#endif

	val &= ~PTE_REFCOUNT_MASK;	// clear refcount
	if (count > 0) {
		if (count == 1) {
			val &= ~_PAGE_PRESENT;
		}
		// decrease refcount and set it
		val |= (count - 1) << PTE_REFCOUNT_SHIFT;
		set_pte(pte, __pte(val));
		__flush_tlb_all();
	} else {
		// printk("BoKASAN warning: [page_unrefer] refcount underflow, pte: %px\n", pte);
		// dump_stack();
	}
}

void page_init_flag(pte_t *pte){
	pteval_t val = native_pte_val(*pte);

	val &= ~PTE_REFCOUNT_MASK;	// clear refcount
	val &= ~_PAGE_PRESENT;
	val |= _PAGE_SPECIAL;
	set_pte(pte, __pte(val));
}

void object_init_flag(unsigned long vaddr, size_t size){
	int i;
	pte_t *pte;

	// printk("BoKASAN: object_init_flag: vaddr: 0x%lx, size: 0x%lx\n", vaddr, size);

	for(i = 0; i <= (size - 1) / PAGE_SIZE; i++){
		pte = get_addr_pte(vaddr + i * PAGE_SIZE);
		if(pte){
			page_init_flag(pte);
		}
	}
}