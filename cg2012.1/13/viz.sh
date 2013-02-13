#!/bin/bash
cmake .
make main
make testgen
./testgen
cp viz/* tests
cp main tests
pushd tests
./runall.sh
popd
