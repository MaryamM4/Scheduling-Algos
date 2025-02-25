#!/bin/bash

# Run with: ./runit

make clean # prev. build
clear

echo "Type in scheduler type and enter: "
echo "rr, sjf, fcfs, priority, schedule_fcfs, or priority_rr "
echo
read scheduler
echo


# Build
make $scheduler
echo

# Check if make succeeded before trying to run the binary
if [ $? -eq 0 ]; then
    ./$scheduler schedule.txt
else
    echo "Failed to build scheduler for: $scheduler"
fi
echo