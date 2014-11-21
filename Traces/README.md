### Baselines (SMALL)
1. b1 : A DMA style system with 4K scratchpad where the CPU will copy the data for each window into the scratchpad of the accelerator. Requires:
    1. Run the post process tool to generate the DMA trace. (post-b1)
    2. Profile the running time of accelerator first to obtain the average lease time for each invocation. 
    3. Configs to set in params.in
        a. enable_dma_core 1
        b. cl_lease_accN X (where N is accelerator core from 2 to 7 and X is the lease time in cycles)
        c. acc_lease_update 1
2. b2 : A shared cache like system described in the CODA paper
    1. No DMA trace required. Create a dummy trace_1.raw file.
    2. Configs to set in params.in
        a. enable_dma_core 0
        b. acc_lease_update 1
        c. set all cl_lease_accN to 1
3. b3 : Fusion protocol based system which will have 4K L0 caches and 64K L1 shared cache. 
    1. No DMA trace required. Create a dummy trace_1.raw file.
    2. Profile the running time of each function to obtain the average lease time for each invocation.
    3. Configs to set in params.in
        a. enable_dma_core 0
        b. cl_lease_accN X (where N is accelerator core from 2 to 7 and X is the lease time in cycles)
        c. acc_lease_update 1
4. b4 : Fusion protocol where the current acc will forward the shared data to the next acc. 
    1. DMA trace not required, but post processing tool needs to be run to move loads up. (post-b2)
    2. Use same lease time as previous cases for each accelerated function
    3. Configs to set in params.in
        a. enable_dma_core 0
        b. acc_lease_update 1

LARGE configs will replace the 4K scratchpads/L0 with 8K and the shared L1 will be increased in size from 64K to 256K.

How to profile lease time:
1. Set cl_lease_accN in params.in
2. Observe running time of ACCN
3. Optimize for less runtime
4. Ensure `MI L2_Expire` events don't happen to often (others are waiting on stalled data due to long lease)
