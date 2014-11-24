L2_ACCESS_PJ=100
L2T_TO_L2_LINK_PJ_BYTE=2
L2T_64K_ACCESS_PJ=40
#----To be added later
L2T_256K_ACCESS_PJ=40

L1T_TO_L2T_LINK_PJ_BYTE=0.4
L1T_8K_CACHE_ACCESS_PJ=8
L1T_8K_SP_ACCESS_PJ=6.8
L1T_4K_CACHE_ACCESS_PJ=5
L1T_4K_SP_ACCESS_PJ=3.8
INT_ADD_PJ=0.2
INT_MUL_PJ=3
FP_ADD_PJ=1
FP_MUL_PJ=4

##--- to be added later
NUM_INT_ADD=1000
NUM_INT_MUL=1000
NUM_FP_ADD=1000
NUM_FP_MUL=1000
    
#-------------- BASELINE 1 --------------------------
run_baseline_1 () {    
    
    echo "Running Baseline 1"    
    if [ "$1" == "small" ]; then
        L1T_SP_ACCESS_PJ=${L1T_4K_SP_ACCESS_PJ}
    elif [ "$1" == "large" ];then
        L1T_SP_ACCESS_PJ=${L1T_8K_SP_ACCESS_PJ}
    else
        echo "ERROR XXXX -- KHATRA"
        exit

    fi
    NUM_DMA=`grep Sequencer_1 ruby.stat.out | awk '{print $7}'`
    FINAL_DMA_PJ=`echo "$NUM_DMA*(${L2_ACCESS_PJ}+${L1T_SP_ACCESS_PJ} +${L2T_TO_L2_LINK_PJ_BYTE}*40 )"|bc -l`  #40byte is 5flits*8bytes
    FINAL_CORE_PJ=`echo "${NUM_INT_ADD}*${INT_ADD_PJ} + ${NUM_INT_MUL}*${INT_MUL_PJ} + ${NUM_FP_ADD}*${FP_ADD_PJ} + ${NUM_FP_MUL}*${FP_MUL_PJ}"|bc -l`

    L1T_TOT_STORES=`grep "^L1_WThru" ruby.stat.out | awk '{print $2}'`  #Since we are faking L1T and L2T behaves as the actual Scratchpad 
    L1T_HIT=`grep -A19 "\-\-\- L1TCache \-\-\-" ruby.stat.out | grep "^S\ \ Load" | awk '{print $3}'`
    FINAL_SP_PJ=`echo "${L1T_SP_ACCESS_PJ}*(${L1T_HIT} + ${L1T_TOT_STORES})"|bc -l`

    echo "$FINAL_CORE_PJ"
    echo "$FINAL_SP_PJ"
    echo "$FINAL_DMA_PJ"
}
#-------------- BASELINE 2 --------------------------

run_baseline_2 () {    
    echo "Running Baseline 2"    
    if [ "$1" == "small" ]; then
        L2T_ACCESS_PJ=${L2T_64K_ACCESS_PJ}
    elif [ "$1" == "large" ]; then
        L2T_ACCESS_PJ=${L2T_256K_ACCESS_PJ}
    else
        echo "ERROR XXXX -- KHATRA"
        exit
    fi

    FINAL_CORE_PJ=`echo "${NUM_INT_ADD}*${INT_ADD_PJ} + ${NUM_INT_MUL}*${INT_MUL_PJ} + ${NUM_FP_ADD}*${FP_ADD_PJ} + ${NUM_FP_MUL}*${FP_MUL_PJ}"|bc -l`

    L2T_MISS=`grep "L2T_cache_total_misses:" ruby.stat.out | awk '{print $2}'`    
    L2T_TOTAL_REQ=`grep "L2T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
    L2_TO_L2T_DATA=`grep "L2_TO_L2T_DATA" ruby.stat.out |  awk '{print $3}'`
    L2T_TO_L1T_DATA=`grep "L2T_TO_L1T_DATA" ruby.stat.out | awk '{print $3}'`
    L1T_TO_L2T_MSG=`grep "L1T_TO_L2T_MSG" ruby.stat.out | awk '{print $3}'`

    FINAL_L2T_PJ=`echo "$L2T_TOTAL_REQ * $L2T_ACCESS_PJ +  8*$L1T_TO_L2T_LINK_PJ_BYTE*( $L2T_TO_L1T_DATA + $L1T_TO_L2T_MSG )" | bc -l`
    FINAL_L2_PJ=`echo "($L2T_MISS +$L2_TO_L2T_DATA) *8* $L2T_TO_L2_LINK_PJ_BYTE + $L2T_MISS * $L2_ACCESS_PJ"|bc -l`

    echo "$FINAL_CORE_PJ"
    echo "$FINAL_L2T_PJ"
    echo "$FINAL_L2_PJ"

}


#-------------- BASELINE 3 --------------------------



run_baseline_3 () {    
    if [ "$2" == "b3" ]; then 
        echo "Running Baseline 3" 
    elif [ "$2" == "b4" ]; then 
        echo "Running Baseline 4" 
    else
        echo "ERROR not b3 or b4"
        echo "$2"
        exit
    fi


    if [ "$1" == "small" ]; then
        L2T_ACCESS_PJ=${L2T_64K_ACCESS_PJ}
        L1T_ACCESS_PJ=${L1T_4K_CACHE_ACCESS_PJ}
    elif [ "$1" == "large" ]; then
        L2T_ACCESS_PJ=${L2T_256K_ACCESS_PJ}
        L1T_ACCESS_PJ=${L1T_8K_CACHE_ACCESS_PJ}
    else
        echo "ERROR XXXX -- KHATRA"
        exit
    fi
    L2T_MISS=`grep "L2T_cache_total_misses:" ruby.stat.out | awk '{print $2}'`    
    L2_TO_L2T_DATA=`grep "L2_TO_L2T_DATA" ruby.stat.out |  awk '{print $3}'` 
    LINK_PJ=`echo "($L2T_MISS + $L2_TO_L2T_DATA)*8*$L2T_TO_L2_LINK_PJ_BYTE" |bc -l` 
    L2_ACCESS_PJ=`echo " $L2T_MISS*$L2_ACCESS_PJ" | bc -l`
    FINAL_L2_PJ=`echo " $L2_ACCESS_PJ + $LINK_PJ" | bc -l`

    L2T_TOTAL_REQ=`grep "L2T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
    L2T_TO_L1T_DATA=`grep "L2T_TO_L1T_DATA" ruby.stat.out | awk '{print $3}'`
    L1T_TO_L2T_MSG=`grep "L1T_TO_L2T_MSG" ruby.stat.out | awk '{print $3}'`
    FINAL_L2T_PJ=`echo "$L2T_TOTAL_REQ * $L2T_ACCESS_PJ +  8*$L1T_TO_L2T_LINK_PJ_BYTE*( $L2T_TO_L1T_DATA + $L1T_TO_L2T_MSG )" | bc -l`
 
    L1T_TOTAL_REQ=`grep "L1T_cache_total_requests:"  ruby.stat.out | awk '{print $2}'`
    FINAL_L1T_PJ=`echo  "$L1T_TOTAL_REQ * $L1T_ACCESS_PJ" | bc -l`

    FINAL_CORE_PJ=`echo "${NUM_INT_ADD} * ${INT_ADD_PJ} + ${NUM_INT_MUL}*${INT_MUL_PJ} + ${NUM_FP_ADD}*${FP_ADD_PJ} + ${NUM_FP_MUL}*${FP_MUL_PJ}"|bc -l`


    echo "$FINAL_CORE_PJ"
    echo "$FINAL_L1T_PJ"
    echo "$FINAL_L2T_PJ"
    echo "$FINAL_L2_PJ"
}


#------------- MAIN-----------------------
if [ "$2" == "b1" ]; then
    run_baseline_1 $1
elif [ "$2" == "b2" ]; then
    run_baseline_2 $1

elif [ "$2" == "b3"  ]; then
    run_baseline_3 $1 $2

elif [ "$2" == "b4" ]; then   ## baseline 3 and 4 are same 
    run_baseline_3 $1  $2
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
