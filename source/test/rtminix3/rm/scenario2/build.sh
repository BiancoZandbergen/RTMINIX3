#!/bin/sh

cc -o rm1 rm_klogstart.c -lrt -lklog 
cc -o rm2 rm.c -lrt
cp rm2 rm3

