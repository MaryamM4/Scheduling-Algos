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
