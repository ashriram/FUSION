grep "CPU halted after"  std_out | awk '{ sum+=$7} END {print sum}'
DMA=`grep "DMA halted after"  std_out | awk '{ sum+=$7} END {print sum}'`
DMA2=`echo "$DMA+40"|bc -l`
echo "$DMA2"
grep "ACC\s[2-7]\shalted after"  std_out | awk '{ sum+=$8} END {print sum}' 
