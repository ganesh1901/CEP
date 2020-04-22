rm -f testme
rm -f *.out
gcc $1 -o testme -pg
./testme
gprof testme gmon.out > gprof1.out 
gprof --sum testme gmon.out 
gprof -b --no-graph testme gmon.out 

