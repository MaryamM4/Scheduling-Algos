/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "schedulers.h"
#include "task.h"

#define SIZE 100

int main(int argc, char *argv[]) {
  FILE *in;
  char *temp;
  char task[SIZE];

  char *name;
  int priority;
  int burst;

  in = fopen(argv[1], "r");
  while (fgets(task, SIZE, in) != NULL) {
    temp = strdup(task);
    name = strsep(&temp, ",");
    priority = atoi(strsep(&temp, ","));
    burst = atoi(strsep(&temp, ","));

    add(name, priority, burst); // Add task to scheduler's list.

    free(temp);
  }
  fclose(in);

  schedule(); // Invoke the scheduler
  return 0;
}
