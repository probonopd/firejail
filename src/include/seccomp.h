/*
 * Copyright (C) 2014-2017 Firejail Authors
 *
 * This file is part of firejail project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/* default seccomp filter
	// seccomp
	struct sock_filter filter[] = {
		VALIDATE_ARCHITECTURE,
		EXAMINE_SYSCALL,
		BLACKLIST(SYS_mount),  // mount/unmount filesystems
		BLACKLIST(SYS_umount2),
		BLACKLIST(SYS_ptrace), // trace processes
		BLACKLIST(SYS_kexec_load), // loading a different kernel
		BLACKLIST(SYS_open_by_handle_at), // open by handle
		BLACKLIST(SYS_init_module), // kernel module handling
		BLACKLIST(SYS_finit_module),
		BLACKLIST(SYS_delete_module),
		BLACKLIST(SYS_iopl), // io permissions
		BLACKLIST(SYS_ioperm),
		BLACKLIST(SYS_iopl), // io permissions
		BLACKLIST(SYS_ni_syscall),
		BLACKLIST(SYS_swapon), // swap on/off
		BLACKLIST(SYS_swapoff),
		BLACKLIST(SYS_syslog), // kernel printk control
		RETURN_ALLOW
	};

	struct sock_fprog prog = {
		.len = (unsigned short)(sizeof(filter) / sizeof(filter[0])),
		.filter = filter,
	};


	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
		perror("prctl(NO_NEW_PRIVS)");
		return 1;
	}
	if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) {
		perror("prctl");
		return 1;
	}
*/

#ifndef SECCOMP_H
#define SECCOMP_H
#include <errno.h>
#include <linux/filter.h>
#include <sys/syscall.h>
#include <linux/capability.h>
#include <linux/audit.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/prctl.h>
#ifndef PR_SET_NO_NEW_PRIVS
# define PR_SET_NO_NEW_PRIVS 38
#endif

#if HAVE_SECCOMP_H
#include <linux/seccomp.h>
#else
#define SECCOMP_MODE_FILTER	2
#define SECCOMP_RET_KILL	0x00000000U
#define SECCOMP_RET_TRAP	0x00030000U
#define SECCOMP_RET_ALLOW	0x7fff0000U
#define SECCOMP_RET_ERRNO	0x00050000U
#define SECCOMP_RET_DATA        0x0000ffffU
struct seccomp_data {
    int nr;
    __u32 arch;
    __u64 instruction_pointer;
    __u64 args[6];
};
#endif

#if defined(__i386__)
# define ARCH_NR	AUDIT_ARCH_I386
#elif defined(__x86_64__)
# define ARCH_NR	AUDIT_ARCH_X86_64
#elif defined(__arm__)
# define ARCH_NR	AUDIT_ARCH_ARM
#else
# warning "Platform does not support seccomp filter yet"
# define ARCH_NR	0
#endif

#define VALIDATE_ARCHITECTURE \
     BPF_STMT(BPF_LD+BPF_W+BPF_ABS, (offsetof(struct seccomp_data, arch))), \
     BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, ARCH_NR, 1, 0), \
     BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#define VALIDATE_ARCHITECTURE_64 \
     BPF_STMT(BPF_LD+BPF_W+BPF_ABS, (offsetof(struct seccomp_data, arch))), \
     BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, AUDIT_ARCH_X86_64, 1, 0), \
     BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#define VALIDATE_ARCHITECTURE_32 \
     BPF_STMT(BPF_LD+BPF_W+BPF_ABS, (offsetof(struct seccomp_data, arch))), \
     BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, AUDIT_ARCH_I386, 1, 0), \
     BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#if defined(__x86_64__)
// handle X32 ABI
#define X32_SYSCALL_BIT 0x40000000
#define HANDLE_X32 \
		BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, X32_SYSCALL_BIT, 1, 0), \
		BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, 0, 1, 0), \
		RETURN_ERRNO(EPERM)
#endif

#define EXAMINE_SYSCALL BPF_STMT(BPF_LD+BPF_W+BPF_ABS,	\
		 (offsetof(struct seccomp_data, nr)))

#define EXAMINE_ARGUMENT(nr) BPF_STMT(BPF_LD+BPF_W+BPF_ABS,	\
		 (offsetof(struct seccomp_data, args[nr])))

#define ONLY(syscall_nr)	\
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, syscall_nr, 1, 0),	\
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#define BLACKLIST(syscall_nr)	\
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, syscall_nr, 0, 1),	\
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL)

#define WHITELIST(syscall_nr) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, syscall_nr, 0, 1), \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#define BLACKLIST_ERRNO(syscall_nr, nr) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, syscall_nr, 0, 1), \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ERRNO | nr)

#define RETURN_ALLOW \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#define RETURN_ERRNO(nr) \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ERRNO | nr)

#define KILL_PROCESS \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL)

#endif
