/**
 * list data structure containing the tasks in the system
 */

#ifndef LIST_H
#define LIST_H

#include "task.h"
#include <stdbool.h>

struct node {
  Task *task;
  struct node *next;
};

bool comesBefore(char *a, char *b);

// insert and delete operations.
void insert(struct node **head, Task *task);
void insertAtEnd(struct node **head, Task *task);
void insertLexicographically(struct node **head, Task *task);
void deleteFromList(struct node **head, Task *task);
void traverse(struct node *head);
void deleteList(struct node **head);

#endif // LIST_H