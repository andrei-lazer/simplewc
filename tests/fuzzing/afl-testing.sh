#!/bin/bash

# using AFL to compile simplewc.c
./AFL/afl-gcc ../../simplewc.c -o ./simplewc-afl

# running fuzzer
./AFL/afl-fuzz -i afl-testcases -o afl-findings ./simplewc-afl @@
