### Baselines (SMALL)
1. b1 : A DMA style system with 4K scratchpad where the CPU will copy the data for each window into the scratchpad of the accelerator. Requires:
    1. Run the post process tool to generate the DMA trace.
    2. Profile the running time of accelerator first to obtain the average lease time for each invocation. 
    3. Configs to set in params.in
        a. enable_dma_core 1
        b. cl_lease_accN X (where N is accelerator core from 2 to 7 and X is the lease time in cycles)
        c. acc_lease_update 1
2. b2 : A shared cache like system described in the CODA paper
    1. No DMA trace required. Create a dummy trace_1.raw file.
    2. CL_LEASE_TIME should be set to 1
    3. Configs to set in params.in
        a. enable_dma_core 0
        b. acc_lease_update 0
3. b3 : Fusion protocol based system which will have 4K L0 caches and 64K L1 shared cache. 
    1. No DMA trace required. Create a dummy trace_1.raw file.
    2. Profile the running time of each function to obtain the average lease time for each invocation.
    3. Configs to set in params.in
        a. enable_dma_core 0
        b. cl_lease_accN X (where N is accelerator core from 2 to 7 and X is the lease time in cycles)
        c. acc_lease_update 1
4. b4 : Fusion protocol where the current acc will forward the shared data to the next acc. (PENDING)

LARGE configs will replace the 4K scratchpads/L0 with 8K and the shared L1 will be increased in size from 64K to 256K.
