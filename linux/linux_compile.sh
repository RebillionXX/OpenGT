#!/usr/bin/env bash

echo "Configuring OpenGT.Main ..."
cd makemain
cmake .
cmake --build .

# echo "Configuring Lunar.Server ..."
# cd ../makeserver
# cmake .
# cmake --build .