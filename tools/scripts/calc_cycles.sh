grep "CPU halted after"  std_out | awk '{ sum+=$7} END {print sum}'
grep "DMA halted after"  std_out | awk '{ sum+=$7} END {print sum}'
grep "ACC\s[2-7]\shalted after"  std_out | awk '{ sum+=$8} END {print sum}' 
