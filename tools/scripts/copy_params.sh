#!/bin/bash 

APPS=('tracking' 'histogram'  'nw'  'disparity'  'susan'  'filter'  'fft' 'adpcm') 

for(( i=0;i<${#APPS[@]};i++)) 
do
    cp  small/b1/${APPS[$i]}/params.in   small/b3/${APPS[$i]}/.
    cp  small/b1/${APPS[$i]}/params.in   small/b4/${APPS[$i]}/.
    #grep "enable_dma"  small/b3/${APPS[$i]}/params.in | awk '{print $2}'
    sed -i 's/enable_dma_core\ 1/enable_dma_core\ 0/'  small/b3/${APPS[$i]}/params.in
    sed -i 's/enable_dma_core\ 1/enable_dma_core\ 0/'  small/b4/${APPS[$i]}/params.in
done
