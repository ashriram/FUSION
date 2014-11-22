#x=$(cat accfunc.txt | wc -l)
#x=$(wc -l < "accfunc.txt")
#let "x+= 1"
#echo $x
#while  [ x -lt 8 ];
#do
    #touch trace_${x}.raw
    #gzip trace_${x}.raw
    #mv trace_${x}.raw.gz trace_${x}.raw
    #x=x+1
#done

for x in {2..7}; do
    if [ ! -f "trace_${x}.raw" ]; then
        touch trace_${x}.raw
        gzip trace_${x}.raw
        mv trace_${x}.raw.gz trace_${x}.raw
    fi
done

ln -s ../../../../tools/post-b1/process 
./process 4096
rm process
