rm -f testme
rm -f *.out
gcc $1 -o testme -pg
./testme
gprof testme gmon.out --display-unused-functions --static-call-graph
