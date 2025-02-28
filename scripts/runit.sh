#!/bin/bash

# Prompts user to choose scheduler model.
# Run with: ./runit

# File stores tasks info
#tasks_file="pri-schedule.txt"
tasks_file="schedule.txt"

make clean # prev. build
clear

echo "Type in one of the following scheduler types and enter: "
echo "fcfs, sjf, priority, rr, or priority_rr "
echo
read scheduler
echo


# Build
make $scheduler
echo

# Check if make succeeded before trying to run the binary
if [ $? -eq 0 ]; then
    ./$scheduler "$tasks_file"
else
    echo "Failed to build scheduler for: $scheduler"
fi
echo