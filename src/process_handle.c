#include <asm/traps.h>

#include "process_handle.h"

static bool pid_arr[PID_MAX] = {0, };

void add_pid(int pid){
	if (pid == -1) return;
	if(pid != 1)
		pid_arr[pid] = 1;
}

void remove_pid(int pid){
	if (pid == -1) return;
	pid_arr[pid] = 0;
}

bool is_pid_present(int pid){
	return pid_arr[pid];
}

bool is_current_pid_present(void){
	if (pid_arr[task_pid_nr(current)]) {
		printk("PID %d is present\n", task_pid_nr(current));
	}
	return pid_arr[task_pid_nr(current)];
}