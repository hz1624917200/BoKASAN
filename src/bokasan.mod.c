#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbe3d218e, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x4b472d17, "cdev_del" },
	{ 0x3a44f9b5, "kmalloc_caches" },
	{ 0x17f1e614, "cdev_init" },
	{ 0x1ed8b599, "__x86_indirect_thunk_r8" },
	{ 0xb52929ee, "boot_cpu_data" },
	{ 0x9b7fe4d4, "__dynamic_pr_debug" },
	{ 0x70304faa, "device_destroy" },
	{ 0xc29957c3, "__x86_indirect_thunk_rcx" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x4629334c, "__preempt_count" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0xfb578fc5, "memset" },
	{ 0xd38cd261, "__default_kernel_pte_mask" },
	{ 0x4e06485a, "current_task" },
	{ 0x7c32d0f0, "printk" },
	{ 0x7c1372e8, "panic" },
	{ 0x4c9d28b0, "phys_base" },
	{ 0x1e6d26a8, "strstr" },
	{ 0x5ca6b585, "device_create" },
	{ 0x801de1f9, "unregister_ftrace_function" },
	{ 0x1d19f77b, "physical_mask" },
	{ 0xe007de41, "kallsyms_lookup_name" },
	{ 0x453b73c2, "cdev_add" },
	{ 0xafeda40e, "ftrace_set_filter_ip" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0x71c0e748, "pv_cpu_ops" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x8b9200fd, "lookup_address" },
	{ 0xb96b1096, "pv_mmu_ops" },
	{ 0x91a5c02c, "register_ftrace_function" },
	{ 0xabefed30, "class_destroy" },
	{ 0x28318305, "snprintf" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xbcda763b, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8a35b432, "sme_me_mask" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "257AA286672E9FB70F9998C");
