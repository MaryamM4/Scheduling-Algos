#ifndef SCHEDULERRS_H
#define SCHEDULERS_H

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

#include "cpu.h"  // For run() and tasks
#include "list.h" // For Task list.

// Global Head for tasks list.
extern struct node *g_head;

// Add a task to the list
void add(char *name, int priority, int burst);

// Invoke the scheduler
void schedule();

#endif // SCHEDULERS_H
