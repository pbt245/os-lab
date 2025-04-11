#!/bin/bash

    echo "Cleaning Previous Build ..."
    make clean

    echo "Building ..."
    make

    echo "Running Program..."
    ./main

    echo "Program finished running!"