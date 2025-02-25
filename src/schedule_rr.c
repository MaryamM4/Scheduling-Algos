// Round-Robin (RR)
// Each task is run for a time quantum
// (or for the remainder of it's CPU burst)

#include "schedulers.h" // Interface

struct node *g_head = NULL;

int min(int a, int b) { return (a < b) ? a : b; }

void add(char *name, int priority, int burst) {
  Task *newTask = createTask(name, priority, burst);
  insert(&g_head, newTask);
}

// Helper method for schedule
Task *pickNextTask() {
  if (!g_head) {
    return NULL; // If list is empty, nothing to do.
  }
  Task *next = g_head->task;

  // Delete the node from list, Task will get deleted later.
  deleteFromList(&g_head, next);
  return next;
}

void schedule() {
  Task *temp;

  while (g_head != NULL) {
    temp = pickNextTask();
    if (temp) {
      run(temp, min(temp->burst, QUANTUM));

      // If task not done, move back to end.
      temp->burst -= 10;
      if (temp->burst > 0) {
        insertAtEnd(&g_head, temp);

      } else {
        deleteTask(temp); // Done with task.
      }
    }
  }
}