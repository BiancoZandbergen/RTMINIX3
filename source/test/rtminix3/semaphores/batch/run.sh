#!/bin/sh

no_tests=19
current_test=1
passed=0
failed=0
badones=
exitcode= 

echo Starting automated test for Synchronisation Server

while [ $current_test -le $no_tests ]
do
#echo $current_test

./test$current_test
exitcode=$?

if [ $exitcode -eq 0 ]; then
	echo passed test $current_test
	passed=`expr $passed + 1` 
else
	echo failed test $current_test
	
	if [ $exitcode -eq 3 ]; then
		echo Fatal failure... exiting test
		exit
	fi
	failed=`expr $failed + 1`
	badones=`echo $badones " " $current_test`
fi

current_test=`expr $current_test + 1`
done

if [ $passed -eq $no_tests ]; then
	echo All $no_tests tests passed without error.
else
	echo Testing completed. Number of tests: $no_tests Passed: $passed Failed: $failed.
	echo Failed tests: $badones.
fi	
