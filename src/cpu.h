#ifndef CPU_H
#define CPU_H

#include "task.h"
#include <stdio.h> // bool

// length of a time quantum
#define QUANTUM 10
#define DISPATCH_TIME 1

extern int dispatch_count;
extern int exec_time;

// run the specified task for the following time slice
void run(Task *task, int slice);

// Outputs percentage of time the CPU is idle.
void printCPUUtilization();

int getCurrentTime();

#endif // CPU_H