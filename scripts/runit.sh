#!/bin/bash

# Run with: ./runit

echo "Choose scheduler type: "
echo "rr, sjf, fcfs, priority, schedule_fcfs, or priority_rr "
echo
read scheduler
echo

make clean # prev. build
clear

# Build
make $scheduler

# Check if make succeeded before trying to run the binary
if [ $? -eq 0 ]; then
    ./$scheduler schedule.txt
else
    echo "Failed to build scheduler for: $scheduler"
fi
