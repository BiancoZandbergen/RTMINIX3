#!/bin/sh

kill -9 `ps ax | grep edf | awk '{ print $1 }'`
echo "Killed all processes with name containing 'edf'"
