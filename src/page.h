bool is_page_special(unsigned long vaddr);
void set_present_bit(unsigned long vaddr);
void clear_present_bit(unsigned long vaddr);
void pages_clear_present_bit(unsigned long vaddr, size_t size);
int test_present_bit(void);

extern void* g_slub_address;