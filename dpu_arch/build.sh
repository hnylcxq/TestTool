#!/bin/bash

rm *.o
g++ -g -c dpu_ckp.cpp  dpu_cmodel.cpp  dpu_csc.cpp cmodel_wrapper.cpp   -I code_piece 

ar -crv libcmodel.a *.o

g++ -g main.c -L . -l cmodel 

