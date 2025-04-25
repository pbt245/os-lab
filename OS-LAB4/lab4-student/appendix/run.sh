#!/bin/bash

echo "Running sysheader (A.1: header inspection done during compilation)"
if [ -f "./sysheader" ]; then
    ./sysheader
else
    echo "Error: sysheader not found. Please run 'make' first."
    exit 1
fi

echo -e "\nRunning systime (A.3: time-related system call)"
if [ -f "./systime" ]; then
    ./systime
else
    echo "Error: systime not found. Please run 'make' first."
    exit 1
fi