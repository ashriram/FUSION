
/**

This assumes that the max number of simultaneous vectors is 8. If
more are required this needs to changed and both the Pintool and the
Simulator need to be recompiled. The libroi interface will also need
to change. Check KNOB when running simulator.

**/

bool     ds_flag;
ds_ops   ds_op_type;
uint32_t ds_load_base_addrs[8];
uint32_t ds_node_size[8];
uint32_t ds_load_index_offsets[8];
uint32_t ds_static_ins_count;
uint32_t ds_compute_slice_latency;
uint32_t ds_compute_int_count;
uint32_t ds_compute_fp_count;
uint32_t ds_compute_k;
uint32_t ds_stack_accesses;
uint32_t ds_store_base_addrs[8];
uint32_t ds_store_index_offsets[8];
uint32_t ds_num_iter;
uint32_t ds_vec_len[8];

