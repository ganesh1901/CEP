#!/bin/bash

for i in `seq 1 100`; do 
ps -Leo pid,tid,class,sched,rtprio,s,comm | grep Task
sleep 1;
echo "Showing Next Sample...! ";
done 
