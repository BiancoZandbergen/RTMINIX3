#!/bin/sh

rt_set_sched_edf

./edf1 100 25&
./edf2 100 25 200&
