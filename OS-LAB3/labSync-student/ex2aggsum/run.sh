#!/bin/bash

echo "Cleaning Previous Build ..."
make clean

echo "Building ..."
make

echo "Running Program..."
./aggsum "$@"

echo "Program finished running!"