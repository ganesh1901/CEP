gcc $1 -o testme  -ftest-coverage -fprofile-arcs
./testme
gcov $1 
gcov -f $1 
gcov -b $1
