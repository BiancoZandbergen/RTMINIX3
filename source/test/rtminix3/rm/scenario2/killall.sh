#!/bin/sh

kill -9 `ps ax | grep rm | awk '{ print $1 }'`
echo "Killed all processes with name containing 'rm'"
