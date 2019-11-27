#!/bin/bash

g++ -std=c++11 -o run.o main.cpp HashLL.cpp HashBST.cpp Hashing.cpp Kits.cpp

./run.o dataSetA.csv dataSetC.csv
