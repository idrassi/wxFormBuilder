#!/bin/bash

# build files for the plugin
cd ../..
./create_build_files.sh

# build files for the libraries
cd ../build
./create_build_files.sh
