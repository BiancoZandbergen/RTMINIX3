#!/bin/sh

rt_set_sched_edf

./edf1 100 50&
./edf2 100 60&
