### MAxC - A Many Accelerator Coherence Protocol
Motivation :- In systems with accelerators, The  acceleratable kernel has to be first brought in from memory to cache of the Accelerators.
Moreover, for an accelerator to realize any performance gain and hide this memory latency, the size of the acceleratable code should be large.
But there exists parts of the code which is acceleratble and not large enough for existing accelerators ( like GPU's) to exploit.
The idea is to have multiple light wight acclerators which can work on various small acceleratable kernels, which are not accleratable on traditional accelerators like GPU's.

We propose to have a coherence protocol for the accelerators (ACC) which can be used to accelerate small parts of the code.
The design consists of many accelerators which will have there own private caches(sector caches) and a shared L2-cache (ACC-L2). 
The shared ACC-L2 will be  integrated with the Main Cores- L2. 

When  a section of the code is detected as acceleratable, the main core will isuue an instruction to copy the related data from Main core's L2 to ACC-L2, and will switch to another process.
Then an ACC will be assigned by the main core to accelerate the kernel. The assigned ACC will then inform the time it will take to do the compute and invalidate the data after that time.

ACC-L2 that




Contributions:-
CPU - side L2 - MESI
1. Request from ACC - how are they organized
3. fine grained mem ops in accelerator
1-3 is same
trace consists of -- memops nad noops with some latency 
ld -- nop -- ld

2. How ld/st is organized  -- Ld hoisting
 Latency -- copying from L2 to acc L2

4. pipelining
5. Granularity