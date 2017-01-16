#!/usr/bin/env bash

cd "$(dirname "$0")"

rmdir -r build
mkdir build
cd build

cmake ..
make -j4
