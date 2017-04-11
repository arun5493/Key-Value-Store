#!/bin/bash
./threadTest > log.txt
sort -nk2 log.txt > log2.txt 
./validate 1000 < log2.txt 
