echo -e "Metrics">>summary.txt
echo -e "    ">>summary.txt
echo -e "Misses">>summary.txt
echo -e "----------------">>summary.txt

M_PE_INT=`grep PE_INT acc.stat.out | awk '{print $2}'` 
