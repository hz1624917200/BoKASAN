#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/stacktrace.h>
#include <linux/kallsyms.h>

#include <stdbool.h>

#include "report.h"
#include "alloc.h"

void (*_arch_stack_walk)(stack_trace_consume_fn consume_entry, void *cookie,
		     struct task_struct *task, struct pt_regs *regs);

typedef struct {
	unsigned long ip;
	bool need_next;
} stack_trace_cookie;

static bool stack_trace_callback(void *cookie_ptr, unsigned long addr, bool reliable){
	stack_trace_cookie *cookie = (stack_trace_cookie *)cookie_ptr;
	if (cookie->need_next) {
		cookie->ip = addr;
		return false;
	}
	if (addr == cookie->ip) {
		cookie->need_next = true;
	}
	return true;
	
}

void report_poison_1(unsigned long vaddr, unsigned long ip){

	char fname[100];
	s8 shadow_value;
	stack_trace_cookie cookie = {
		.ip = ip,
		.need_next = false
	};
	snprintf(fname, 100, "%pS", (void *)ip);
	
	if (strstr(fname, "memcpy") != NULL || strstr(fname, "memset") != NULL || strstr(fname, "memmove") != NULL){
		_arch_stack_walk(stack_trace_callback, &cookie, current, NULL);
	}

	ip = cookie.ip;

	shadow_value = *(s8 *)kasan_mem_to_shadow((void *)vaddr);

	pr_crit("==================================================================\n");

	if((unsigned long)(shadow_value & 0xff) == BOKASAN_FREE){
		pr_err("BUG: KASAN: use-after-free in %pS vaddr: %px\n", (void *)ip, (void *)vaddr);
	}
	else if((unsigned long)(shadow_value & 0xff) == BOKASAN_REDZONE){
		pr_crit("BUG: KASAN: out-of-bounds access in %pS vaddr: %px\n", (void *)ip, (void *)vaddr);
	}
	else if((unsigned long)(shadow_value & 0xff) == BOKASAN_FREE_PAGE){
		pr_err("BUG: KASAN: use-after-free (page) in %pS vaddr: %px\n", (void *)ip, (void *)vaddr);
	}
	else {
		pr_crit("BUG: KASAN: out-of-bounds access in %pS vaddr: %px\n", (void *)ip, (void *)vaddr);
	}

	dump_stack();

	panic("bokasan panic...\n");
}

void init_report(void){
	_arch_stack_walk = (void*)kallsyms_lookup_name("arch_stack_walk");
}