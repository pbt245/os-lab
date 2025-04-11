#!/bin/bash

echo "Cleaning Previous Build ..."
make clean

echo "Building ..."
make

echo "Running Program..."
./shrdmem

echo "Program finished running!"