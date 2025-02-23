/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

#include <stdlib.h> // EXIT_STATUS

typedef struct task {
  char *name;
  int tid;
  int priority;
  int burst;
} Task;

Task *createTask(char *name, int priority, int burst) {
  Task *newTask = (Task *)malloc(sizeof(Task));
  if (!newTask) {
    fprintf(stderr, "createTask failed to allocate memory for Task.\n");
    exit(EXIT_FAILURE);
  }

  newTask->name = strdup(name); // Duplicate the string to allocate memory
  if (!newTask->name) {
    fprintf(stderr, "createTask failed to allocate memory for Task name.\n");
    free(newTask);
    exit(EXIT_FAILURE);
  }

  newTask->priority = priority;
  newTask->burst = burst;

  return newTask;
}

void deleteTask(Task *task) {
  if (task) {
    free(task->name);
    free(task);
  }
}

#endif // TASK_H
