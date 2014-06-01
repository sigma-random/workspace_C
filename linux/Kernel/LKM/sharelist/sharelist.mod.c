#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x465fed8b, "module_layout" },
	{ 0xc996d097, "del_timer" },
	{ 0x8949858b, "schedule_work" },
	{ 0xdd1a2871, "down" },
	{ 0xbe2c0274, "add_timer" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x6fe340df, "kmem_cache_alloc_trace" },
	{ 0x62c1ade7, "malloc_sizes" },
	{ 0xc4554217, "up" },
	{ 0xfd1680da, "wake_up_process" },
	{ 0x16bf5257, "kthread_create_on_node" },
	{ 0x37a0cba, "kfree" },
	{ 0x50eedeb8, "printk" },
	{ 0x8834396c, "mod_timer" },
	{ 0x7d11c268, "jiffies" },
	{ 0x67f7403e, "_raw_spin_lock" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

