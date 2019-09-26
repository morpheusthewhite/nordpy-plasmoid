#!/bin/sh

echo "Building and installing plugin"
mkdir -p plugin/build
cd plugin/build
qmake .. && make && sudo make install || { echo "Failed building plugin"; exit 1; }

echo "Building and installing plasmoid"
cd ../..
mkdir -p build
cd build
cmake .. && make && sudo make install || { echo "Failed building plasmoid"; exit 1; }
