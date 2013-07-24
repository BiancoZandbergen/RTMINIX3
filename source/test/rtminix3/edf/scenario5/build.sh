#!/bin/sh

cc -o edf1 edf_klog.c -lrt -lklog
cc -o edf2 edf.c -lrt
