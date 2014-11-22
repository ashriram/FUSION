for x in {6..7}; do
    if [ ! -f "trace_${x}.raw" ]; then
        touch trace_${x}.raw
        gzip trace_${x}.raw
        mv trace_${x}.raw.gz trace_${x}.raw
        cp ../trace.txt .
        #ln -s ../../../../tools/post-b4/process 
        #./process 4096
        #rm process
    fi
done

