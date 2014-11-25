#!/bin/bash 

APPS=( 'fft' 'disparity' 'tracking' 'histogram'  'susan'  'filter' 'adpcm') 
#APPS=('fft')
bench=('b1'  'b2'  'b3')
#bench=('b4' 'b3')

path=$1
#path='small'
#path='small'

cd ${path}

for(( i=0;i<${#APPS[@]};i++)) 
do
#    echo "" > ../../energy/${path}/energy-${APPS[$i]}.csv
 
    for x in ${bench[@]}
    do

        #cd ${x}    
        echo "${APPS[$i]}"
        cd  "${x}/${APPS[$i]}" 
        cwd=$(pwd)
        echo -e "$cwd"
        #--- To Run BENCH MARK--------------------------
        cp ../../../energy.sh  .
        ./energy.sh ${path}  ${x} ${APPS[$i]} >>../../../energy/${path}/energy-all.csv
        
        #rm CONFIG_SCRATCHPAD_4K
        #rm CONFIG       
        #ln -s ../../../../gems-lib/ruby_clean/config/LARGE/CONFIG_XLARGE_B4 CONFIG

        #if [ "${x}" == "b1"  ] 
        #then    
        #    ln -s ../../../../gems-lib/ruby_clean/config/LARGE/CONFIG_SCRATCHPAD_8K  CONFIG
        #else
        #    ln -s ../../../../gems-lib/ruby_clean/config/LARGE/CONFIG_b2-b3-b4  CONFIG
        #fi
        #rm trace_file_list
        #echo "1">trace_file_list
        #echo "../../../../Traces/large/${x}/"${APPS[$i]}"/trace.txt">>trace_file_list
        #./ooo-sim>std_out  2>std_err &        
        #------ to Calculate CPU -- DMA --- ACC Cycles ----
       
        #---- CPU DMA AND ACC  CYCLES------
        #grep "CPU halted after"  std_out | awk '{ sum+=$7} END {print sum}'
        #
        #if [ "${x}" == "b1"  ] 
        #then
        #    DMA=`grep "DMA halted after"  std_out | awk '{ sum+=$7} END {print sum}'`
        #    DMA2=`echo "$DMA+40"|bc -l`
        #    echo -e "$DMA2"
        #else
        #    echo -e "0"
        #fi
        #
        #grep "ACC\s[2-7]\shalted after"  std_out | awk '{ sum+=$8} END {print sum}' 
        
        #-----------------------------------------------------
        cd ../../
    done
    #cd ..
done
cd ..
