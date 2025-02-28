// Priority with Round-Robin
// Schedules tasks in order of priority,
// and uses round-robin shceduling for tasks with equal priority.

#include "schedulers.h" // Interface

struct node *g_head = NULL;
struct node *info_head = NULL;

int min(int a, int b) { return (a < b) ? a : b; }

void add(char *name, int priority, int burst) {
  Task *newTask = createTask(name, priority, burst, 0);

  struct node *newNode = malloc(sizeof(struct node));
  newNode->task = newTask;
  newNode->next = NULL;

  // If list is empty or new task has higher priority than the head
  if (g_head == NULL || priority > g_head->task->priority) {
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
  // traverse(g_head);
  struct node *group_head, *group_end, *curr, *prev, *to_del;

  group_head = g_head;

  while (g_head != NULL) {
    group_head = g_head;

    // Find node that's end of group.
    curr = group_head;
    while (curr->next != NULL &&
           curr->next->task->priority == group_head->task->priority) {
      curr = curr->next;
    }
    group_end = curr;

    // Remove RR group from g_head list.
    g_head = group_end->next;
    group_end->next = group_head; // Make circular.

    // Start Round Robin cycle.
    prev = group_head;
    curr = group_head;
    while (curr && curr->task) {
      run(curr->task, min(curr->task->time_left, QUANTUM));
      curr->task->time_left -= QUANTUM;

      if (curr->task->time_left <= 0) {
        to_del = curr;
        deleteTask(to_del->task);

        if (prev == curr) { // If last node, we're done
          free(to_del);
          // to_del->task->completion_time = getCurrentTime();
          // insertLexicographically(&info_head, to_del->task);
          break;

        } else { // Otherwise remove from RR and iterate.
          prev->next = curr->next;
          curr = curr->next;

          free(to_del);
          // to_del->task->completion_time = getCurrentTime();
          // insertLexicographically(&info_head, to_del->task);
        }

      } else { // Iterate through RR group.
        prev = curr;
        curr = curr->next;
      }
    }
  }

  printf("\n");
  printCPUUtilization();
  printf("\n");
  // printInfo(info_head);
  // deleteList(&info_head);
}
