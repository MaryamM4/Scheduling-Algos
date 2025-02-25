// Priority with Round-Robin
// Schedules tasks in order of priority,
// and uses round-robin shceduling for tasks with equal priority.

#include "schedulers.h" // Interface

struct node *g_head = NULL;

int min(int a, int b) { return (a < b) ? a : b; }

void add(char *name, int priority, int burst) {
  Task *newTask = createTask(name, priority, burst);

  struct node *newNode = malloc(sizeof(struct node));
  newNode->task = newTask;
  newNode->next = NULL;

  if (g_head == NULL) {
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
  // When we do a RR, we'll have same tasks w/ same priorities linked circularly
  // Tasks with next priority lvl will be temp held on.
  struct node *holder = malloc(sizeof(struct node));
  holder = g_head;

  struct node *temp = malloc(sizeof(struct node));
  temp->next = NULL;

  while (holder != NULL) {
    temp = holder; // Save beginning of RR loop.

    while (holder->next != NULL &&
           holder->task->priority == holder->next->task->priority) {
      holder = holder->next;
    }
    holder->next = temp; // Create circular loop.

    // Round-Robin for everything in temp list.
    while (temp->task != NULL) {
      run(temp, min(temp->task->burst, QUANTUM));

      // If task not done, move back to end.
      temp->task->burst -= 10;
      if (temp->task->burst > 0) {
        insertAtEnd(&g_head, temp->task);

      } else {
        deleteFromList(g_head, temp->task);
        deleteTask(temp->task); // Done with task.
      }
      temp = temp->next;
    }

    holder = holder->next; // Next priority level.
  }
}