/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

#include <stddef.h> // NULL
#include <stdio.h>
#include <stdlib.h> // EXIT_STATUS & free()
#include <string.h> // strdup()

typedef struct task {
  char *name;
  int tid;
  int priority;
  int burst;

  // Starts as burst. Subtracted when
  int time_left; // it gets CPU time.

  int init_time;
  int first_response_time; // First itme it gets run().
  int completion_time;     // Once it's time_left <= 0.
  int dispatch_count;      // Number of times its in run().
} Task;

Task *createTask(char *name, int priority, int burst, int init_time);
void deleteTask(Task *task);

#endif // TASK_H
