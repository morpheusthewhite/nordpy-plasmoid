#!/bin/sh

echo "Building and installing plugin"
cd plugin/build
qmake .. && make && sudo make install || (echo "Failed building plugin" && exit 1)

echo "Building and installing plasmoid"
cd ../../build
pwd
cmake .. && make && sudo make install || (echo "Failed building plasmoid" && exit 1)
