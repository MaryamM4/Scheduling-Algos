// Shortest-job-first (SJF)
// Schedules taks in order of the length of tasks' next CPU burst.

#include "schedulers.h"

struct node *g_head = NULL;
struct node *info_head = NULL;

void add(char *name, int priority, int burst) {
  Task *newTask = createTask(name, priority, burst, 0);

  struct node *newNode = malloc(sizeof(struct node));
  newNode->task = newTask;
  newNode->next = NULL;

  // If list is empty or new task has lower duration than the head
  if (g_head == NULL || burst < g_head->task->burst) {
    newNode->next = g_head;
    g_head = newNode;
  } else {
    struct node *prev = g_head;
    struct node *next = g_head->next;

    // Find the correct position based on priority (descending order)
    while (next != NULL && priority <= next->task->priority) {
      prev = next;
      next = next->next;
    }
    prev->next = newNode;
    newNode->next = next;
  }
}

void schedule() {
  Task *to_del;

  while (g_head != NULL) {
    run(g_head->task, g_head->task->burst);

    to_del = g_head->task;
    g_head = g_head->next;

    deleteTask(to_del);
  }
}