rm -f testme
gcc $1 -o testme -pg -O2
./testme
gprof testme gmon.out > gprof2.out 
gprof --sum testme gmon.out 
gprof -b --no-graph testme gmon.out 

