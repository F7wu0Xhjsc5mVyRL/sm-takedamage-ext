#!/bin/bash

rm -rf build

mkdir build
cd build
python3 ../configure.py --enable-optimize 1
ambuild

exit
