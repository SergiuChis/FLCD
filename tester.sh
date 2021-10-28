#!/bin/bash

for test_file in `ls Inputs/Testing/`
do
    echo "Input file: "$test_file
    echo "Contents:"
    cat Inputs/Testing/$test_file
    echo ""
    echo "Tokens:"
    ./lexer Inputs/Testing/$test_file Inputs/token.in
    echo ""
    echo ""
done