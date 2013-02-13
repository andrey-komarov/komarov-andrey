#!/bin/bash
cmake .
make main
make testsgen
./testsgen
cp viz/* tests/*
cp main tests
pushd tests
./runall.sh
popd
