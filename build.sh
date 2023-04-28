# ------------------------------------
# Copyright (C) 2023 Lilanka Pathirage 
# ------------------------------------

# Instead of creating complicated build system, 
# just use simple build script to build the language 

#!/bin/sh
set echo on

project_name="Oevyli Language"
author="Lilanka Pathirage"
project_version="0.0.1"

echo -e "\033[1m$project_name $project_version by $author\033[0m"

mkdir -p bin/

cc_version="-std=c++20"

# Build Compiler 
cc_files=$(find src/ -type f -name "*.cc")
defines="-DEBUG_MODE=1"

echo "Building compiler..."
clang++ $cc_version $cc_files -o bin/oevyli $defines

echo "Build Successfull"

# Run test
echo "Running tests..."
./bin/oevyli ../tests/test1.oli
