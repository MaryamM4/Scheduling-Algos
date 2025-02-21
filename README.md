# Scheduling Algorithms
C implementation of process scheduling algorithms described in Chapter 5 of the Operating System Concepts textbook.
Tasks are predefined and assigned priority and CPU burst time.

## Algorithms
* First-Come, First-Served (FCFS): Schedules tasks in the order of arrival.
* Shortest-Job-First (SJF): Schedules tasks by the shortest CPU burst time.
* Priority Scheduling: Schedules tasks based on priority (1–10, higher number = higher priority).
* Round-Robin (RR): Runs tasks for a fixed time quantum (10ms) in a cyclic order.
* Priority RR: Schedules by priority and uses round-robin for tasks with equal priority.

## Other Features
* Calculates and outputs CPU utilization considering 1 unit of dispatcher time.
* Displays turnaround time (TAT), wait time (WT), and response time (RT) for each task.
