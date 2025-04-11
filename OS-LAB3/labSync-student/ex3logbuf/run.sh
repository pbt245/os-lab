#!/bin/bash
echo "Cleaning Previous Build ..."
make clean
echo "Building ..."
make
echo "Running Program..."
./logbuf
echo "Program finished running!"