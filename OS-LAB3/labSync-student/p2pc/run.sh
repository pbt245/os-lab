#!/bin/bash

echo "Cleaning Previous Build ..."
make clean

echo "Building ..."
make

echo "Running Program..."
./pc

echo "Program finished running!"