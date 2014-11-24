#!/bin/bash 

APPS=('tracking' 'histogram'  'nw'  'disparity'  'susan'  'filter'  'fft' 'adpcm') 
#APPS=('fft')
#bench=('b1'  'b2'  'b3'  'b4')
bench=('b1')

path='large/'

cd ${path}
for x in ${bench[@]}
do
    cd ${x}
    pwd
    tail */std_out | grep "finalize" |wc -l
    cd ..
done
cd ..
