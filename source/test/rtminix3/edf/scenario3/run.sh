#!/bin/sh

rt_set_sched_edf

./edf1 25  6&
./edf2 50  12&
./edf3 100 25&
./edf4 200 50&
