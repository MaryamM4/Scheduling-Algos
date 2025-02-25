#!/bin/bash

echo "Choose scheduler type: "
echo "rr, sjf, fcfs, priority, schedule_fcfs, or priority_rr"
echo
read scheduler
echo

make clean  # Remove previous builds
clear

make $scheduler

# Check if make succeeded before trying to debug the binary
if [ $? -eq 0 ]; then
    gdb -ex run -ex backtrace -ex quit ./$scheduler
else
    echo "Failed to build scheduler for: $scheduler"
fi
