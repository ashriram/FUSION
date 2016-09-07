## MAxC - A Many Accelerator Coherence Protocol

The current uncore accelerator-host interfaces are not optimized for fine grain data transfer. GPUs utilize the PCIe interface, whereas Xilinx and Intel have shown FPGAs interfaced via Quick Path Interconnect. Most accelerator models (exception is IBM CAPI), task the CPU with the movement of data to and from device memory. Thus for fine grain acceleration the standard has been to use incore acceleration such as the incorporation of cyptographic instructions in Intel processors. This approach however utilizes CPU resources for rote tasks. [4] touches upon the high level issues on selecting a method of attachment. For a coherent memory approach to attachment, conventional protocols are not suitable, we propose a Many Accelerator Coherence (MAxC) Protocol to enable fine grain coherent access to data from an interconnected group of accelerators. 

![inline image](maxc.png)

### Design 
The design consists of many accelerators which will have there own private L1 caches (organised as sector caches) and a shared L2-cache (ACC-L2). 
As shown in the figure above, the ACCs will run an enahnced version of the Temporal Coherence protocol which also forwards data (not similar to Forwarding in MESIF). The host system will run a standard MESI protocol. Due to the self invalidating nature of TC, we can maintain virtual address coherence in the accelerator realm and only performa translations when data interchange takes place between the ACC LLC and the host LLC, this is similar to the approach described in [1]. 

We envision 3 types of workloads which will be accelerated 
1. Separate Kernels (belonging to the same userspace process on the host)
2. Separate iterations of same kernel (loop parallelism)
3. Pipelined kernels - Kernels which are composed of 2 or more functions without CPU code execution between them.

In essence enable a sea of accelerators to cheaply communicate with the core as well as amongst themselves to perform fine grain acceleration while being far removed from core itself.

### Contributions
1. The organization of ACC's 
2. Fine grained mem ops in ACC i.e ACC will be capable of issuing memory instructions on its own 
        For example, a program's resource allocation has the following pattern 
        acc1 -> acc2 -> cpu -> acc3
        Curently, the processor is involved in every memory interaction, since the accelerator does not have a LD/ST unit. 
        So the main core has to gather data and put it in the acc scratchpad before acc can start compute.
3. Pipelining - Pipelining the ACC's, so that ACC's running various sections of the code, can forward data without copying back and forth.


### Related Work 

1. [Practically Costless Coherence](http://lpgpu.org/wp/wp-content/uploads/2013/02/04_PEGPUM_PUBLIC.pdf)
    Particulary interesting picture on slide 26. Virtual Address Coherence. 
2. [Computation vs. Memory Systems:Pinning Down Accelerator Bottlenecks](http://arcade.cs.columbia.edu/accels-amasbt10.pdf)
    Data flow between functions.
3. [Cohesion: A Hybrid Memory Model for Accelerators](http://dl.acm.org/citation.cfm?id=1816019)
    Rigel related work.
4. [Attaching Accelerators to Multicore systems](http://www.altera.com/technology/system-design/articles/2014/article-accelerators.html)
    Altera Article
5. [A Reconfigurable Computing System Based on a Cache-Coherent Fabric](http://www.capsl.udel.edu/~egarcia/Papers/Reconfig11.pdf)
    Intel paper on attaching FPGAs using Quick Path Interconnect vs PCIe.
6. [CAPI : Power 8's Coherent Accelerator Processor Interface](http://www.hotchips.org/wp-content/uploads/hc_archives/hc25/HC25.20-Processors1-epub/HC25.26.210-POWER-Studecheli-IBM.pdf)
7. [A Survey on Hardware-aware and Heterogeneous Computing on Multicore Processors and Accelerators]  (http://emcl.iwr.uni-heidelberg.de/fileadmin/images/Publications/Preprints/emcl-preprint-2009-02.pdf)
8. [Accelerator-Rich CMPs: From Concept to Real Hardware](http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6657039&url=http%3A%2F%2Fieeexplore.ieee.org%2Fiel7%2F6644329%2F6657009%2F06657039.pdf%3Farnumber%3D6657039)


