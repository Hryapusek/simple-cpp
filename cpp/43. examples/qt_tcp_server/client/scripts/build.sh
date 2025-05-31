#!/bin/bash
mkdir build
cd build
cmake -S .. -B .
cmake --build . --parallel 16
mkdir libs
cp ./*.so* libs/