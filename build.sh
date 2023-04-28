# ------------------------------------
# Copyright (C) 2023 Lilanka Pathirage 
# ------------------------------------

# Instead of creating complicated build system just use simple 
# build script to compile the language 

#!/bin/sh
set echo on

project_name="Oevyli Lang"
project_version="0.0.1"

echo -e "\033[1m$project_name $project_version\033[0m"

mkdir -p bin/

cc_version="-std=c++20"

# Build Compiler 
cc_files=$(find src/ -type f -name "*.cc")
compiler_flags="-g -shared -fdeclspec -fPIC"
defines="-D_DEBUG -DKIMPORT"

echo "Building engine..."
clang++ $cc_version $cc_files $compiler_flags -o bin/lib_oevyli.so $defines \

# Build Tests
#test_files=$(find tests/ -type f -name "*.cc")
test_files=$(find tests/ -type f -name test1.cc) # for unit tests
test_compiler_flags="-g -fdeclspec -fPIC"
test_include_flags="-Isrc/"
test_linker_flags="-Lbin/ -Lsrc/"
defines="-D_DEBUG -DKIMPORT"

echo "Building tests..."
clang++ $cc_version $test_files $test_compiler_flags -o bin/libtests $testdefines $test_include_flags $test_linker_flags

echo "Build Successfull"
