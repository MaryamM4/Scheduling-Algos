// First-Come First-Served (FCFS)
// Schedules tasks in order in which they request the CPU.

// For simplified grading and testing:
// - Assume all tasks arrive at the same time.
// - Order tasks that arrive at the same time lexicographically.

#include "list.h"
#include "schedulers.h" // Interface
#include <stdbool.h>
#include <stdio.h>

struct node *g_head = NULL;

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

// Helper method for schedule.
// Based on traverse from list.c.
// Finds the task whose name comes first in dictionary.
Task *pickNextTask() {
  if (!g_head) {
    return NULL; // If list is empty, nothing to do.
  }

  struct node *temp;
  temp = g_head;

  Task *best_sofar = temp->task;
  while (temp != NULL) {
    if (comesBefore(temp->task->name, best_sofar->name)) {
      best_sofar = temp->task;
    }
    temp = temp->next;
  }

  // Delete the node from list, Task will get deleted later.
  delete (&g_head, best_sofar);

  return best_sofar;
}

// @TODO
void add(char *name, int priority, int burst);

// @TODO:
// Invokes the scheduler
void schedule();