/**********************************************************************************************
 * File         : imb.h
 * Author       : ska124
 * Date         : 07/05/2013
 * SVN          :
 * Description  : intermediate buffer for acc
 *********************************************************************************************/

#ifndef IMB_H_INCLUDED
#define IMB_H_INCLUDED

#include "global_types.h"
#include "global_defs.h"

class imb_c
{
private:
	int m_capacity;
	Counter m_cycle;
	macsim_c* m_simBase;

	pqueue_c<Acc_Msg_Type> *m_pe_in_queue;     
    pqueue_c<Acc_Msg_Type> *m_pe_out_queue;     
    pqueue_c<Acc_Msg_Type> *m_walker_in_queue;     
    pqueue_c<Acc_Msg_Type> *m_walker_out_queue;     

public:
	imb_c(int cap, 
		pqueue_c<Acc_Msg_Type> *pe_in_queue,     
		pqueue_c<Acc_Msg_Type> *pe_out_queue,     
		pqueue_c<Acc_Msg_Type> *walker_in_queue,     
		pqueue_c<Acc_Msg_Type> *walker_out_queue,
		macsim_c *simBase);

	void run_a_cycle(void);
};


#endif

