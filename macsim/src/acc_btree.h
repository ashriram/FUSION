#ifndef ACC_BTREE_H
#define ACC_BTREE_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_set>

// #include "global_defs.h"
// #include "global_types.h"
#include "btree.h"

class DataStruct
{
public:
	/* data */
	FILE* KeyFile;
	int flag; // 
	unsigned long long* buffer;
public:
	DataStruct(char* file,long int BufferSize) 
	{
		KeyFile= fopen(file,"w+b");
	
		// File not found. 
		assert(KeyFile!=NULL); 
	
		flag = 0;

		buffer = new unsigned long long int[BufferSize];

	};
	virtual ~DataStruct() {delete[] buffer; if(KeyFile) fclose(KeyFile);};
	
	/**
	 * Initialize internal data structure. Read keys
	 * from KeyFileand fill in the key-value map. Values are chosen internally
	 * Need to change specifically for each data structure. Look at init definition
	 */
	virtual void init() = 0;
	
	/**
	 * Actual work that is traced and saved into Buffer.
	 */
	virtual void doWork() = 0;


	/**
	 * [Trace description]
	 */
	virtual std::unordered_set<unsigned long long> pop() = 0;

	
};




class BTree : public DataStruct
{
public:
	BTree(char* file, long int BufferSize);
	virtual ~BTree();
	void init();
	void doWork();
	std::unordered_set<unsigned long long> pop();
	int pop_count;
	int64_t pop_max;
	/* data */
	Node* root_ptr;
	RootTracker tracker;  // maintains a pointer to the current root of the b-tree
	long int size;


};

#endif // ACC_BTREE_H