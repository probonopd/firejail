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
#include "firejail.h"
#include <sys/time.h>
#include <sys/resource.h>

void set_rlimits(void) {
	// resource limits
	struct rlimit rl;
	if (arg_rlimit_nofile) {
		rl.rlim_cur = (rlim_t) cfg.rlimit_nofile;
		rl.rlim_max = (rlim_t) cfg.rlimit_nofile;
#ifdef HAVE_GCOV	// gcov-instrumented programs might crash at this point
		__gcov_dump();
#endif
		if (setrlimit(RLIMIT_NOFILE, &rl) == -1)
			errExit("setrlimit");
		if (arg_debug)
			printf("Config rlimit: number of open file descriptors %llu\n", cfg.rlimit_nofile);
	}

	if (arg_rlimit_nproc) {
		rl.rlim_cur = (rlim_t) cfg.rlimit_nproc;
		rl.rlim_max = (rlim_t) cfg.rlimit_nproc;
#ifdef HAVE_GCOV
		__gcov_dump();
#endif
		if (setrlimit(RLIMIT_NPROC, &rl) == -1)
			errExit("setrlimit");
		if (arg_debug)
			printf("Config rlimit: number of processes %llu\n", cfg.rlimit_nproc);
	}

	if (arg_rlimit_fsize) {
		rl.rlim_cur = (rlim_t) cfg.rlimit_fsize;
		rl.rlim_max = (rlim_t) cfg.rlimit_fsize;
#ifdef HAVE_GCOV
		__gcov_dump();
#endif
		if (setrlimit(RLIMIT_FSIZE, &rl) == -1)
			errExit("setrlimit");
		if (arg_debug)
			printf("Config rlimit: maximum file size %llu\n", cfg.rlimit_fsize);
	}

	if (arg_rlimit_sigpending) {
		rl.rlim_cur = (rlim_t) cfg.rlimit_sigpending;
		rl.rlim_max = (rlim_t) cfg.rlimit_sigpending;
#ifdef HAVE_GCOV
		__gcov_dump();
#endif
		if (setrlimit(RLIMIT_SIGPENDING, &rl) == -1)
			errExit("setrlimit");
		if (arg_debug)
			printf("Config rlimit: maximum number of signals pending %llu\n", cfg.rlimit_sigpending);
	}
}
