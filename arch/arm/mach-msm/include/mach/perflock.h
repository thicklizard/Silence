/* arch/arm/mach-msm/perflock.h
 *
 * MSM performance lock driver header
 *
 * Copyright (C) 2008 HTC Corporation
 * Author: Eiven Peng <eiven_peng@htc.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __ARCH_ARM_MACH_PERF_LOCK_H
#define __ARCH_ARM_MACH_PERF_LOCK_H

#include <linux/list.h>
#include <linux/cpufreq.h>


enum {
	TYPE_PERF_LOCK = 0,	
	TYPE_CPUFREQ_CEILING,	
};

enum {
	PERF_LOCK_LOWEST,	
	PERF_LOCK_LOW,	
	PERF_LOCK_MEDIUM,	
	PERF_LOCK_HIGH,	
	PERF_LOCK_HIGHEST,	
	PERF_LOCK_INVALID,
};

struct perf_lock {
	struct list_head link;
	unsigned int flags;
	unsigned int level;
	const char *name;
	unsigned int type;
};

struct perflock_data {
	unsigned int *perf_acpu_table;
	unsigned int table_size;
};

struct perflock_pdata {
	struct perflock_data *perf_floor;
	struct perflock_data *perf_ceiling;
};



extern void perf_lock_init(struct perf_lock *lock, unsigned int type,
	unsigned int level, const char *name);
extern void perf_lock(struct perf_lock *lock);
extern void perf_unlock(struct perf_lock *lock);
extern int is_perf_lock_active(struct perf_lock *lock);
extern int is_perf_locked(void);
extern void perflock_scaling_max_freq(unsigned int freq, unsigned int cpu);
extern void perflock_scaling_min_freq(unsigned int freq, unsigned int cpu);
extern int perflock_override(const struct cpufreq_policy *policy, const unsigned int new_freq);
extern void htc_print_active_perf_locks(void);
extern struct perf_lock *perflock_acquire(const char *name);
extern int perflock_release(const char *name);
#ifdef CONFIG_PERFLOCK_BOOT_LOCK
extern void release_boot_lock(void);
#endif



#endif

