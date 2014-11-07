.PHONY: all clean bb_gemm fft md pp_scan reduction ss_sort stencil triad

all: bb_gemm fft md pp_scan reduction ss_sort stencil triad

bb_gemm: 
	$(MAKE) -C bb_gemm

fft: 
	$(MAKE) -C fft

md: 
	$(MAKE) -C md

pp_scan: 
	$(MAKE) -C pp_scan

reduction: 
	$(MAKE) -C reduction

ss_sort: 
	$(MAKE) -C ss_sort

stencil: 
	$(MAKE) -C stencil

triad: 
	$(MAKE) -C triad


clean: 
	$(MAKE) -C bb_gemm clean
	$(MAKE) -C fft clean
	$(MAKE) -C md clean
	$(MAKE) -C pp_scan clean
	$(MAKE) -C reduction clean
	$(MAKE) -C ss_sort clean
	$(MAKE) -C stencil clean
	$(MAKE) -C triad clean

