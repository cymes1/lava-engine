#!/bin/bash

# creating directory build if not exist
if [ -d ".build" ]; then
	mkdir build
fi
cd build

# running cmake
cmake ..

# running make
make

# copying compile_commands.json
if [ -d "../compile_commands.json" ]; then
	rm ../compile_commands.json
fi
cp ./compile_commands.json ../compile_commands.json

# running program
cd build/bin
./lava

# returning to root directory
cd ../../../
