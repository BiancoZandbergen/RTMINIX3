#!/bin/sh

rt_set_sched_edf

./edf1 50 10&
./edf2 100 20&
./edf3 50 5&
./edf4 100 10&
