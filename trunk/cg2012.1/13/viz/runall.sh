#!/bin/bash
for i in ???
do
    ./main < $i > $i.a
    echo $i
done
for i in ???
do
    python plot.py $i{,.a}
done
