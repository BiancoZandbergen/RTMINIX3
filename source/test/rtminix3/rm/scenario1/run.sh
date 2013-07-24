#!/bin/sh

CYCLES=1024

rt_set_sched_rm_pu

./rm3 3 $CYCLES&
./rm7 7 $CYCLES&
./rm1 1 $CYCLES&
./rm4 4 $CYCLES&
./rm8 8 $CYCLES&
./rm2 2 $CYCLES&
./rm6 6 $CYCLES&
./rm5 5 $CYCLES&
