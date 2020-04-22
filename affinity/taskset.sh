#!/bin/sh
ID=`ps ax | grep sched | awk '{ print $1 }' | head -1`
for i in 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
do
sleep 10
if [ $i -eq 1 ] 
then
taskset -pc 1 $ID 
else
taskset -pc 0 $ID
fi
done
