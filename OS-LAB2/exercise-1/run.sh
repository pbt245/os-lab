#!/bin/bash

set -e

echo "Clean Build"
make clean

echo "Build All"
make all

echo "Running..."
./ex1

echo "Results in stored in output.txt!"
