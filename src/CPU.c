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

// @NOTE: printInfo() should be in scheudlers, not cpu.

// Output a table of information for each task:
// - Turn Around time (TAT): Total time from process init to completion
// - Wait Time (WT): Total time the process has to wait in
//                   ready queue before getting CPU time.
// - Response Time (RT): Duration between task init and getting first
//                       time to be executed by CPU.
void printInfo(struct node *info_head) {
  /*
  Each tasks needs:
  - init_time
  - first_response_time
  - burst
  - completion_time
  - dispatch_count

  TAT = completion_time - init_time

  RT = first_response_time - init_time

  WT = (completion_time - init_time) - burst
     =       task's alive time       - time in CPu

  */
  if (!info_head) {
    return;
  }

  // Program doesn't need to be efficient here.
  // So we're iterating through the list 4 times. :)b

  // Print names
  struct node *it = info_head;
  printf("...|");
  while (it != NULL) {
    printf(" %3s |", it->task->name);
    it = it->next;
  }

  it = info_head;
  printf("\nTAT|");
  int tat;
  while (it != NULL) {
    tat = it->task->completion_time - it->task->init_time;
    printf(" %3d |", tat);
    it = it->next;
  }

  it = info_head;
  printf("\nWT |");
  int wt;
  while (it != NULL) {
    wt = (it->task->completion_time - it->task->init_time) - it->task->burst;
    printf(" %3d |", wt);
    it = it->next;
  }

  it = info_head;
  printf("\nRT |");
  int rt;
  while (it != NULL) {
    rt = it->task->first_response_time - it->task->init_time;
    printf(" %3d |", rt);
    it = it->next;
  }

  printf("\n");

  /*
  EXAMPLE:
  ...| T1 | T2 | T3 | T4 | T5 | T6 | T7 | T8 |
  TAT| 2  | 1  | 2  | 1  | 2  | 1  | 2  |  1 |
  WT | 2  | 1  | 2  | 1  | 2  | 1  | 2  |  1 |
  RT | 2  | 1  | 2  | 1  | 2  | 1  | 2  |  1 |
  */
}