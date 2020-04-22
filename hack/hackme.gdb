file ./a.out
handle SIGTRAP noprint nostop
break check
run PASS 
printf "----> Program Runs <-----\n"
stepi
step
printf "Return Value At Present From Function ==> %d\n",$eax 
set $eax=4 
printf "Return Value Intercepted and Modified ==> %d\n",$eax
printf "------> Program Behaviour After Modification <------ \n\n"
c

quit
