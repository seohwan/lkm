#define _GNU_SOURCE 1

#include <asm/unistd.h>
#include <linux/perf_event.h>
#include <linux/hw_breakpoint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

static long perf_event_open(struct perf_event_attr* event_attr, pid_t pid, int cpu,
		     int group_fd, unsigned long flags)
{
    int ret;
    return syscall(__NR_perf_event_open, event_attr, pid, cpu, group_fd, flags);

    return ret;
}

int main(void)
{
    struct perf_event_attr pe;
    struct perf_event *event= NULL;
    pid_t mypid = getpid();
    int inst_fd;
    long long instr_count;

    memset(&pe, 0, sizeof(struct perf_event_attr));

    pe.disabled = 0;
    pe.type = PERF_TYPE_HARDWARE;
    pe.exclude_hv = 1;
    pe.size = sizeof(struct perf_event_attr);
    pe.enable_on_exec = 1;
    pe.inherit = 1;
    pe.exclude_kernel = 0;
    pe.config = 0x17;
    event = perf_event_create_kerenl_counter(&pe, 1, )
}