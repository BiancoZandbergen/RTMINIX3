#!/bin/sh

CYCLES=200

rt_set_sched_rm_pu

./rm1 1 $CYCLES&
./rm2 2 $CYCLES&
./rm3 3 $CYCLES&

