#!/usr/bin/env bash

echo "Configuring OpenGT.Control ..."
cd makecontrol
cmake .
cmake --build .

# echo "Configuring Lunar.Server ..."
# cd ../makeserver
# cmake .
# cmake --build .