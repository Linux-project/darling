#include <asm/unistd.h>
#include "tls.h"

#define ARCH_SET_GS	0x1001

void __pthread_set_self(void* ptr)
{
#ifdef __x86_64__
	LINUX_SYSCALL(__NR_arch_prctl, ARCH_SET_GS, ptr);
#elif defined(__i386__)
	struct user_desc
	{
		unsigned int  entry_number;
		unsigned long base_addr;
		unsigned int  limit;
		unsigned int  seg_32bit:1;
		unsigned int  contents:2;
		unsigned int  read_exec_only:1;
		unsigned int  limit_in_pages:1;
		unsigned int  seg_not_present:1;
		unsigned int  useable:1;
	};

	struct user_desc desc;

	desc.base_addr = (unsigned long) ptr;
	desc.limit = 4096;
	desc.seg_32bit = 1;
	desc.contents = 0;
	desc.read_exec_only = 0;
	desc.limit_in_pages = 1;
	desc.seg_not_present = 0;
	desc.useable = 1;
	desc.entry_number = -1;

	LINUX_SYSCALL(__NR_set_thread_area, &desc);

	__asm__ ("movl %0, %%fs" :: "r" (desc.entry_number*8 + 3));
#endif
}

