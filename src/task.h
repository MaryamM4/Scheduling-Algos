/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <stdlib.h> // EXIT_STATUS
#include <string.h> // strdup()

typedef struct task {
  char *name;
  int tid;
  int priority;
  int burst;
} Task;

Task *createTask(char *name, int priority, int burst);
void deleteTask(Task *task);

#endif // TASK_H
