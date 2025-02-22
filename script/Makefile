# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall

SRC_DIR = ../src

clean:
	rm -rf *.o
	rm -rf fcfs
	rm -rf sjf
	rm -rf rr
	rm -rf priority
	rm -rf priority_rr

rr: driver.o list.o CPU.o schedule_rr.o
	$(CC) $(CFLAGS) -o rr driver.o schedule_rr.o list.o CPU.o

sjf: driver.o list.o CPU.o schedule_sjf.o
	$(CC) $(CFLAGS) -o sjf driver.o schedule_sjf.o list.o CPU.o

fcfs: driver.o list.o CPU.o schedule_fcfs.o
	$(CC) $(CFLAGS) -o fcfs driver.o schedule_fcfs.o list.o CPU.o

priority: driver.o list.o CPU.o schedule_priority.o
	$(CC) $(CFLAGS) -o priority driver.o schedule_priority.o list.o CPU.o

schedule_fcfs.o: $(SRC_DIR)/schedule_fcfs.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/schedule_fcfs.c

priority_rr: driver.o list.o CPU.o schedule_priority_rr.o
	$(CC) $(CFLAGS) -o priority_rr driver.o schedule_priority_rr.o list.o CPU.o

driver.o: $(SRC_DIR)/driver.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/driver.c

schedule_sjf.o: schedule_sjf.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/schedule_sjf.c

schedule_priority.o: $(SRC_DIR)/schedule_priority.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/schedule_priority.c

schedule_rr.o: $(SRC_DIR)/schedule_rr.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/schedule_rr.c

list.o: $(SRC_DIR)/list.c $(SRC_DIR)/list.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/list.c

CPU.o: $(SRC_DIR)/CPU.c $(SRC_DIR)/cpu.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CPU.c
