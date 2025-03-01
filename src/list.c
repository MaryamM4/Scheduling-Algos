/**
 * Various list operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "task.h"

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
  // add the new task to the list
  struct node *newNode = malloc(sizeof(struct node));

  newNode->task = newTask;
  newNode->next = *head;
  *head = newNode;
}

void insertAtEnd(struct node **head, Task *newTask) {
  struct node *newNode = malloc(sizeof(struct node));
  newNode->task = newTask;
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
    return;
  }

  struct node *temp = *head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}

void insertLexicographically(struct node **head, Task *task) {
  struct node *newNode = malloc(sizeof(struct node));
  newNode->task = task;
  newNode->next = NULL;

  // Empty list, or new task comes first.
  if (*head == NULL || comesBefore(task->name, (*head)->task->name)) {
    newNode->next = *head;
    *head = newNode;
    return;
  }

  struct node *current = *head;
  while (current->next != NULL &&
         !comesBefore(task->name, current->next->task->name)) {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;
}

// delete the selected task from the list
void deleteFromList(struct node **head, Task *task) {
  struct node *temp;
  struct node *prev;

  temp = *head;
  // special case - beginning of list
  if (strcmp(task->name, temp->task->name) == 0) {
    *head = (*head)->next;
  } else {
    // interior or last element in the list
    prev = *head;
    temp = temp->next;
    while (strcmp(task->name, temp->task->name) != 0) {
      prev = temp;
      temp = temp->next;
    }

    prev->next = temp->next;
  }
}

// traverse the list
void traverse(struct node *head) {
  struct node *temp;
  temp = head;

  while (temp != NULL) {
    printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority,
           temp->task->burst);
    temp = temp->next;
  }
}

void deleteList(struct node **head) {
  struct node *current = *head;
  struct node *next;

  while (current != NULL) {
    next = current->next;

    deleteTask(current->task);
    free(current);

    current = next;
  }

  *head = NULL;
}

// Output a table of information for each task:
// - Turn Around time (TAT): Total time from process init to completion
// - Wait Time (WT): Total time the process has to wait in
//                   ready queue before getting CPU time.
// - Response Time (RT): Duration between task init and getting first
//                       time to be executed by CPU.
void printInfo(struct node *info_head) {
  if (!info_head) {
    return;
  }

  // Program doesn't need to be efficient here.
  // So we're iterating through the list 4 times. :)b

  // Print names
  struct node *it = info_head;
  printf("...|");
  while (it != NULL) {
    printf(" %3s |", it->task->name);
    it = it->next;
  }

  it = info_head;
  printf("\nTAT|");
  int tat;
  while (it != NULL) {
    tat = it->task->completion_time - it->task->init_time;
    printf(" %3d |", tat);
    it = it->next;
  }

  it = info_head;
  printf("\nWT |");
  int wt;
  while (it != NULL) {
    wt = (it->task->completion_time - it->task->init_time) - it->task->burst;
    printf(" %3d |", wt);
    it = it->next;
  }

  it = info_head;
  printf("\nRT |");
  int rt;
  while (it != NULL) {
    rt = it->task->first_response_time - it->task->init_time;
    printf(" %3d |", rt);
    it = it->next;
  }

  printf("\n");
}
