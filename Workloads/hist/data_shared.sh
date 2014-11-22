#!/bin/bash
for i in $(eval echo {2..$(($1-1))}); do 
    for j in $(eval echo {$(($i+1))..$1}); do
        #echo $i,$j
        lines=`grep  -F  -f  mem_trace_${i}.out   mem_trace_${j}.out  | wc -l`
        #echo -e "${i}\t${j}\t${lines}"
        echo -e "${lines}"

    done
done
