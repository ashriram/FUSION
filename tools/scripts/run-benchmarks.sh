#!/bin/bash 

#APPS=('tracking' 'histogram'  'nw'  'disparity'  'susan'  'filter'  'fft' 'adpcm') 
APPS=('fft')
#bench=('b1'  'b2'  'b3'  'b4')
bench=('b1')

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
        echo "$cwd"
        ./ooo-sim>std_out  2>std_err &        
        cd ..
    done
    cd ..
done
cd ..
