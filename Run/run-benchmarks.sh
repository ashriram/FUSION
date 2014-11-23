#!/bin/bash 

APPS=('tracking' 'histogram'  'nw'  'disparity'  'susan'  'filter'  'fft' 'adpcm') 
#APPS=('fft')
bench=('b1'  'b2'  'b3'  'b4')
#bench=('b1')

path='small/'

cd ${path}
for x in ${bench[@]}
do
    cd ${x}    
        
    for(( i=0;i<${#APPS[@]};i++)) 
    do
        #echo "$(pwd)"
        cd ${APPS[$i]} 
        cwd=$(pwd)
        echo -e "$cwd">>../../../cycles.csv
        #--- To Run BENCH MARK--------------------------
        #./ooo-sim>std_out  2>std_err &        
        #------ to Calculate CPU -- DMA --- ACC Cycles ----
        
        echo -e grep "CPU halted after"  std_out | awk '{ sum+=$7} END {print sum}'>>../../../cycles.csv
        if [ "${x}" == "b1"  ] 
        then
            DMA=`grep "DMA halted after"  std_out | awk '{ sum+=$7} END {print sum}'`
            DMA2=`echo "$DMA+40"|bc -l`
            echo -e "$DMA2">>../../../cycles.csv
        else
            echo -e "0">>../../../cycles.csv
        fi
        
        grep "ACC\s[2-7]\shalted after"  std_out | awk '{ sum+=$8} END {print sum}'>>../../../cycles.csv 
        
        #-----------------------------------------------------
        cd ..
    done
    cd ..
done
cd ..
