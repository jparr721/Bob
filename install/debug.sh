#!/bin/sh

mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

echo "Devel program files loaded and installed"
