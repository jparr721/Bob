#!/bin/sh

mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
make

echo "Release program files loaded.."
