L2_ACCESS_PJ=300
L2T_512K_ACCESS_PJ=12

L2T_TO_L2_LINK_PJ_BYTE=6
L1T_TO_L2T_LINK_PJ_BYTE=0.4
L1T_TO_L1T_LINK_PJ_BYTE=0.1

L1T_8K_CACHE_ACCESS_PJ=7.2
L1T_8K_SP_ACCESS_PJ=6.8

INT_ADD_PJ=0.2
INT_MUL_PJ=3
FP_ADD_PJ=1
FP_MUL_PJ=4

##--- to be added later
NUM_INT_ADD=1000
NUM_INT_MUL=1000
NUM_FP_ADD=1000
NUM_FP_MUL=1000

## HACK: Benchname
BENCH_NAME=$3

FWDX=100
    
run_baseline_3 () {    

    L2T_ACCESS_PJ=${L2T_512K_ACCESS_PJ}
    L1T_ACCESS_PJ=${L1T_8K_CACHE_ACCESS_PJ}
    
    L2T_MISS=`grep "L2T_cache_total_misses:" ruby.stat.out | awk '{print $2}'`    
    L2_TO_L2T_DATA=`grep "L2_TO_L2T_DATA" ruby.stat.out |  awk '{print $3}'` 
    LINK_PJ=`echo "($L2T_MISS + $L2_TO_L2T_DATA)*8*$L2T_TO_L2_LINK_PJ_BYTE" |bc -l` 
    
    
    L2T_TOTAL_REQ=`grep "L2T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
    L2T_TO_L1T_DATA=`grep "L2T_TO_L1T_DATA" ruby.stat.out | awk '{print $3}'`
    L1T_TO_L2T_MSG=`grep "L1T_TO_L2T_MSG" ruby.stat.out | awk '{print $3}'`
    
	# Cache Energy. Accelerator side
	#    L2T (GETS)*ACCESS ENERGY + DMA STORES * ACCESS ENERGY
	#   L1T + L2T

	# L1T energy   
	L1T_TOTAL_REQ=`grep "L1T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
	
    FINAL_L1T_PJ=`echo  "$L1T_TOTAL_REQ * $L1T_ACCESS_PJ" | bc -l`

	# L2T energy. Reads + WBacks
	L2T_READS=`grep -A2 "\-\-\- L2TCache \-\-\-" ruby.stat.out | grep "^L1_GETS" | awk '{print $2}'`
	NUM_DMA=`grep Sequencer_1 ../../b1/$BENCH_NAME/ruby.stat.out | awk '{print $7}'`
	NUM_DMA_READS=`grep "^DMA" ../../b1/$BENCH_NAME/ruby.stat.out | awk '{print $3}' | xargs -i echo "{} / 5" | bc -l`
	NUM_DMA_WRITES=`echo "$NUM_DMA-$NUM_DMA_READS" | bc -l`
    #echo $NUM_DMA_READS
    #echo $NUM_DMA_WRITES
	L2T_WRITES=$NUM_DMA_WRITES
	FINAL_L2T_PJ=`echo "($L2T_READS+$L2T_WRITES)* $L2T_ACCESS_PJ" | bc -l`

	# MESI side cache energy
	#L2 energy
	FINAL_L2_PJ=`echo "$L2T_MISS * $L2_ACCESS_PJ" | bc -l`


	#LINK Energy (Accelerator + ACC->CPU)
	
	L2_TO_L2T_DATA=`grep "L2_TO_L2T_DATA" ruby.stat.out |  awk '{print $3}'`
	L2T_TO_L1T_DATA=`grep "L2T_TO_L1T_DATA" ruby.stat.out| awk '{print $3}' `
	L1T_TO_L2T_MSG=`grep "L1T_TO_L2T_MSG" ruby.stat.out |  awk '{print $3}' `
	L2T_TO_L2_MSG=$L2T_MISS

	FINAL_TILE_LINK_PJ=`echo "($L2_TO_L2T_DATA + $L2T_TO_L2_MSG)*8*$L2T_TO_L2_LINK_PJ_BYTE" | bc -l`
    FINAL_ACC_LINK_PJ=`echo "($L2T_TO_L1T_DATA + $L1T_TO_L2T_MSG)*8*$L1T_TO_L2T_LINK_PJ_BYTE" | bc -l`

    FINAL_CORE_PJ=`echo "${NUM_INT_ADD} * ${INT_ADD_PJ} + ${NUM_INT_MUL}*${INT_MUL_PJ} + ${NUM_FP_ADD}*${FP_ADD_PJ} + ${NUM_FP_MUL}*${FP_MUL_PJ}"|bc -l`


    #echo "$FINAL_CORE_PJ"
   # 
   # echo "$FINAL_L1T_PJ"
   # echo "$FINAL_L2T_PJ"
    FINAL_T_PJ=`echo "$FINAL_L1T_PJ +$FINAL_L2T_PJ" | bc -l`
    echo $FINAL_T_PJ
    echo "$FINAL_L2_PJ"
    #echo "$FINAL_TILE_LINK_PJ"
    #echo "$FINAL_ACC_LINK_PJ"
    FINAL_LINK=`echo "$FINAL_ACC_LINK_PJ + $FINAL_TILE_LINK_PJ "|bc -l`
    echo "$FINAL_LINK"
}

run_baseline_4 () {    

    L2T_ACCESS_PJ=${L2T_512K_ACCESS_PJ}
    L1T_ACCESS_PJ=${L1T_8K_CACHE_ACCESS_PJ}
    
    L2T_MISS=`grep "L2T_cache_total_misses:" ruby.stat.out | awk '{print $2}'`    
    L2_TO_L2T_DATA=`grep "L2_TO_L2T_DATA" ruby.stat.out |  awk '{print $3}'` 
    LINK_PJ=`echo "($L2T_MISS + $L2_TO_L2T_DATA)*8*$L2T_TO_L2_LINK_PJ_BYTE" |bc -l` 
    
    
    L2T_TOTAL_REQ=`grep "L2T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
    L2T_TO_L1T_DATA=`grep "L2T_TO_L1T_DATA" ruby.stat.out | awk '{print $3}'`
    L1T_TO_L2T_MSG=`grep "L1T_TO_L2T_MSG" ruby.stat.out | awk '{print $3}'`
    
	# Cache Energy. Accelerator side
	#    L2T (GETS)*ACCESS ENERGY + DMA STORES * ACCESS ENERGY
	#   L1T + L2T

	# L1T energy   
	L1T_TOTAL_REQ=`grep "L1T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
	
    FINAL_L1T_PJ=`echo  "$L1T_TOTAL_REQ * $L1T_ACCESS_PJ" | bc -l`

	# L2T energy. Reads + WBacks
	L2T_READS=`grep -A2 "\-\-\- L2TCache \-\-\-" ruby.stat.out | grep "^L1_GETS" | awk '{print $2}'`
	NUM_DMA=`grep Sequencer_1 ../../b1/$BENCH_NAME/ruby.stat.out | awk '{print $7}'`
	NUM_DMA_READS=`grep "^DMA" ../../b1/$BENCH_NAME/ruby.stat.out | awk '{print $3}' | xargs -i echo "{} / 5" | bc -l`
	NUM_DMA_WRITES=`echo "$NUM_DMA-$NUM_DMA_READS" | bc -l`
    #echo $NUM_DMA_READS
    #echo $NUM_DMA_WRITES
	L2T_WRITES=$NUM_DMA_WRITES
    FINAL_L2T_PJ=`echo "($L2T_READS+$L2T_WRITES -2*${FWDX})* $L2T_ACCESS_PJ" | bc -l`  ### B4 : Subtract 2X the number of accesses to L2T

	# MESI side cache energy
	#L2 energy
	FINAL_L2_PJ=`echo "$L2T_MISS * $L2_ACCESS_PJ" | bc -l`


	#LINK Energy (Accelerator + ACC->CPU)
	
	L2_TO_L2T_DATA=`grep "L2_TO_L2T_DATA" ruby.stat.out |  awk '{print $3}'`
	L2T_TO_L1T_DATA=`grep "L2T_TO_L1T_DATA" ruby.stat.out| awk '{print $3}' `
	L1T_TO_L2T_MSG=`grep "L1T_TO_L2T_MSG" ruby.stat.out |  awk '{print $3}' `
	L2T_TO_L2_MSG=$L2T_MISS

	FINAL_TILE_LINK_PJ=`echo "($L2_TO_L2T_DATA + $L2T_TO_L2_MSG)*8*$L2T_TO_L2_LINK_PJ_BYTE" | bc -l`
    FINAL_ACC_LINK_PJ=`echo "($L2T_TO_L1T_DATA + $L1T_TO_L2T_MSG - 5*${FWDX})*8*$L1T_TO_L2T_LINK_PJ_BYTE + 32*${FWDX}*$L1T_TO_L1T_LINK_PJ_BYTE" | bc -l` ### Energy for Writebacks not accounted for, should be very small

    FINAL_CORE_PJ=`echo "${NUM_INT_ADD} * ${INT_ADD_PJ} + ${NUM_INT_MUL}*${INT_MUL_PJ} + ${NUM_FP_ADD}*${FP_ADD_PJ} + ${NUM_FP_MUL}*${FP_MUL_PJ}"|bc -l`


    #echo "$FINAL_CORE_PJ"
   # 
   # echo "$FINAL_L1T_PJ"
   # echo "$FINAL_L2T_PJ"
    FINAL_T_PJ=`echo "$FINAL_L1T_PJ +$FINAL_L2T_PJ" | bc -l`
    echo $FINAL_T_PJ
    echo "$FINAL_L2_PJ"
    #echo "$FINAL_TILE_LINK_PJ"
    #echo "$FINAL_ACC_LINK_PJ"
    FINAL_LINK=`echo "$FINAL_ACC_LINK_PJ + $FINAL_TILE_LINK_PJ "|bc -l`
    echo "$FINAL_LINK"
}

#------------- MAIN-----------------------
if [ "$2" == "b3"  ]; then
    run_baseline_3 $1 $2
elif [ "$2" == "b4" ]; then 
    run_baseline_4 $1  $2
else
    echo "WRONG ARGUMENT ENTER b1 or b2 or b3 or b4 for \$2"
    exit
fi    
    

# For b4  Assume total data forwarded between AXC1 and Axc2 is X  then 
# TOTAL ENERGY IS equal to :- 
# L2T_ENERGY = L2T_B3 - 2X * 32 * 0.4
# L1T_ENERGY = L1T_B3 + X * 0.1 * 32  - X* 8 * 0.4
#-----------------------------------------------
#
