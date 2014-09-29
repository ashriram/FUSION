### MAxC - A Many Accelerator Coherence Protocol
Motivation :- In systems with accelerators, The  acceleratable kernel has to be first brought in from memory to cache of the Accelerators.
Moreover, for an accelerator to realize any performance gain and hide this memory latency, the size of the acceleratable code should be large.
But there exists acceleratble part of the code which is not large enough for existing accelerators ( like GPU's) which can be exploited.
The idea is to have multiple light wight acclerators which can work on various small acceleratable kernels, which cannot be given to traditional accelerators like GPU's.
