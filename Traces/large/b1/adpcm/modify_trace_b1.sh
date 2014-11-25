for x in {1..7}; do
    if [ ! -f "trace_${x}.raw" ]; then
        touch trace_${x}.raw
        gzip trace_${x}.raw
        mv trace_${x}.raw.gz trace_${x}.raw
    fi
done

cp ../trace.txt .
ln -s ../../../../tools/post-b1/process 
./process 8192
rm process


