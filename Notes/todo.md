1. Protocol - TC
    a. Testing and verification
2. Protocol - MESI
    a. Verification using old traces
3. System 
    a. Separate SequencerT type
    b. Mapping functions for callbacks
    c. Testing new sequencer types
    d. Configuration parameters need to be set -- Scale ACC L1 and L2 by constant factor of CPU L1 and LLC.
4. Frontend
    a. Trace reader (in icache stage) needs to be modified for multiple trace files
    b. Add support for accelerator cores
    c. ACC cores memory interface 
    d. Filter out stack accesses for accelerator
    e. Accelerator core config
5. Benchmarks
    a. Modify existing pintool to add acc marker along with accelerator identifier
    b. Offline trace processing which will partition the accelerator trace into load -- compute -- store 
    c. Characterize function level data movement. 
    d. Machsuite 
