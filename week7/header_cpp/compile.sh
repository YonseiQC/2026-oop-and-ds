#!/usr/bin/env bash

g++ -c string_sum.cpp
g++ -c main.cpp
g++ -o main main.o string_sum.o
g++ -c odyssey.cpp
g++ -o odyssey odyssey.o string_sum.o
