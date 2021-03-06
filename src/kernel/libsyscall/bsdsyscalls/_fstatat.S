#define __SYSCALL_32BIT_ARG_BYTES 16
#include "SYS.h"

#ifndef SYS_fstatat
#error "SYS_fstatat not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__i386__) || defined(__x86_64__) || defined(__ppc__)
__SYSCALL2(_fstatat, fstatat, 4, cerror)
#else
__SYSCALL2(___fstatat, fstatat, 4, cerror)
#endif

