## MAxC - A Many Accelerator Coherence Protocol

The current uncore accelerator-host interfaces are not optimized for fine grain data transfer. GPUs utilize the PCIe interface, whereas Xilinx and Intel have shown FPGAs interfaced via Quick Path Interconnect. Most accelerator models (exception is IBM CAPI), task the CPU with the movement of data to and from device memory. Thus for fine grain acceleration the standard has been to use incore acceleration such as the incorporation of cyptographic instructions in Intel processors. This approach however utilizes CPU resources for rote tasks. [4] touches upon the high level issues on selecting a method of attachment. For a coherent memory approach to attachment, conventional protocols are not suitable, we propose a Many Accelerator Coherence (MAxC) Protocol to enable fine grain coherent access to data from an interconnected group of accelerators. 

![inline image](maxc.png)

### Design 
The design consists of many accelerators which will have there own private L1 caches (organised as sector caches) and a shared L2-cache (ACC-L2). 
As shown in the figure above, the ACCs will run an enahnced version of the Temporal Coherence protocol which also forwards data (not similar to Forwarding in MESIF). The host system will run a standard MESI protocol. Due to the self invalidating nature of TC, we can maintain virtual address coherence in the accelerator realm and only performa translations when data interchange takes place between the ACC LLC and the host LLC, this is similar to the approach described in [1]. 

We envision 3 types of workloads which will be accelerated 
1. Separate Kernels (belonging to the same userspace process on the host)
2. Separate iterations of same kernel (loop parallelism)
3. Pipelined kernels - Kernels which are composed of 2 or more `Accelerator Blocks` 

In essence enable a sea of accelerators to cheaply communicate with the core as well as amongst themselves to perform fine grain acceleration while being far removed from core itself.

### Accelerator Blocks
1. Compress / Deflate
2. Matrix / Vector Operations
3. Cryptographic Functions
4. Checksum / Digest / CRC
5. Stencil Patterns 
6. XML
7. Regex

### Contributions
1. The organization of ACC's 
2. Fine grained mem ops in ACC i.e ACC will be capable of issuing memory instructions on its own 
        For example, a program's resource allocation has the following pattern 
        acc1 -> acc2 -> cpu -> acc3
        Curently, the processor is involved in every memory interaction, since the accelerator does not have a LD/ST unit. 
        So the main core has to gather data and put it in the acc scratchpad before acc can start compute.
3. Pipelining - Pipelining the ACC's, so that ACC's running various sections of the code, can forward data without copying back and forth.
4. Granularity (optional) - It is part of (2) having different blocks sizes for ACC (private L1 - eg 32 bytes per block) and ACC-L2 (64 bytes per block).

