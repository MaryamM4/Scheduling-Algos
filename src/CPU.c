/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include "cpu.h"

int dispatch_count = 0;
int exec_time = 0;

// "Runs" task for the specified time slice.
void run(Task *task, int slice) {
  printf("Running task = [%s] [%2d] [%2d] for %2d units.\n", task->name,
         task->priority, task->burst, slice);

  // Update CPU's counters
  dispatch_count += 1;
  exec_time += slice;
  int curr_time = getCurrentTime();

  // Update task's counters
  task->dispatch_count += 1;

  if (task->dispatch_count == 1) {
    task->first_response_time = curr_time;
  }

  // Display time after execution
  printf("        Time is now: %d\n", curr_time);
}

int getCurrentTime() { return (exec_time + (dispatch_count * DISPATCH_TIME)); }

// Outputs percentage of time the CPU is idle.
// Assumes dispatcher takes 1 unit of time.
void printCPUUtilization() {
  int time_alive = getCurrentTime();
  double util = (exec_time / (double)time_alive) * 100;

  printf("CPU Utilization: %4f%%\n", util);

  /*
  EX:
  FCFS, if there is dispatcher time: Tasks finish at 170
        (add all of their completion times)
        With dispatcher time, tasks finish at 177.
        (+1 for every time run is called)
        CPU utilization is 170/177 * 100 = 96.04
  */
}
