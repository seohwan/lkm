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
    pe.config = PERF_COUNT_HW_CACHE_MISSES;
    inst_fd = perf_event_open(&pe, mypid, 0, -1, 0);
    if (inst_fd < 0)
    {
        perror("perf_event_open for cycles failed");
        exit(EXIT_FAILURE);
    }
    ioctl(inst_fd, PERF_EVENT_IOC_RESET, 0);
    ioctl(inst_fd, PERF_EVENT_IOC_DISABLE,0);
    read(inst_fd, &instr_count, sizeof(long long));

    printf("Time is up : icount %lld\n", instr_count);

}