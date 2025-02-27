// Priority Scheduling
// Schedules tasks in order of priority.

#include "schedulers.h" // Interface

struct node *g_head = NULL;

int min(int a, int b) { return (a < b) ? a : b; }

void add(char *name, int priority, int burst) {
  Task *newTask = createTask(name, priority, burst);

  struct node *newNode = malloc(sizeof(struct node));
  newNode->task = newTask;
  newNode->next = NULL;

  if (g_head == NULL || priority > g_head->task->priority) {
    newNode->next = g_head;
    g_head = newNode;

  } else {

    struct node *prev = g_head;
    struct node *next;
    while (1) {
      next = prev->next;

      if (next == NULL || priority > next->task->priority) {
        prev->next = newNode;
        newNode->next = next;
        break;
      }

      prev = next;
    }
  }
}

void schedule() {
  Task *temp;
  struct node *it = g_head;

  while (g_head != NULL) {
    run(it->task, it->task->burst);

    temp = it->task;
    it = it->next;

    deleteFromList(&g_head, temp);
    deleteTask(temp);
  }
}