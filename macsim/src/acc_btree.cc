
#include <iostream>
#include "acc_btree.h"
#include "btree.h"
#include <stdio.h>
#include <stdlib.h>


#define NITERS 64 // # of iterations required for ~500 million instructions

BTree::BTree(char* Filename, long int NBuffer) : DataStruct(Filename,NBuffer)
{

    Node::m_failure.invalidate();

    Node::m_failure.m_key = 0;

    root_ptr = new Node(tracker);

    tracker.set_root (reinterpret_cast<Node*> (0), root_ptr);

    size = NBuffer;

    pop_max = 0;
}

BTree::~BTree()
{
//delete root_ptr;
}

void BTree::init()
{

    FILE* datafile = fopen("data.bin", "rb");
    assert(datafile!=NULL);

    unsigned long long entries = 0;
    unsigned long long* DataBuffer;

    fread (&entries,1,sizeof(unsigned long long),datafile);

    DataBuffer = new unsigned long long[entries];

    fread(DataBuffer, 1, entries*sizeof(unsigned long long),datafile);





    Elem elem;


    for (long int i = 0; i < entries; i++)
        {

        elem.m_key = DataBuffer[i];
        //std::cout << "Index i "<< i << "Key: " << elem.m_key << "\n" ;

        elem.m_payload += "";

        tracker.get_root()->tree_insert(elem);

    }

    delete[] DataBuffer;
    std::cout<<"Finished initializing keys" << std::endl;

}


void BTree::doWork()
{
    Node *last;


    FILE* searchfile = fopen("search.bin", "rb");
    assert(searchfile!=NULL);

    unsigned long long entries;
    unsigned long long* searchbuffer;

    fread(&entries, 1, sizeof(unsigned long long), searchfile);
    std:cout<<"Entries" << entries << std::endl;
    searchbuffer = new unsigned long long[entries];
    fread(searchbuffer, 1, entries*sizeof(unsigned long long), searchfile);

    pop_max = entries * NITERS;

   for (int j = 0; j < NITERS; j++ )
   {
        for (long int i = 0; i < (entries-1); i++)
        {
            Elem desired;
            last = NULL;
            desired.m_key = searchbuffer[i];
            // Elem& result = tracker.get_root()->search(desired, last);

            // Dumps to file : dump.bin
            tracker.get_root()->profile_search(desired, last,DataStruct::KeyFile,DataStruct::buffer, size);
        }
    }



    fclose(searchfile);
    delete[] searchbuffer;
    rewind(DataStruct::KeyFile);
    pop_count = 0;
    std::cout << "doWork Complete" << endl;
    return;
}


std::unordered_set<unsigned long long> BTree::pop()
{
    std::unordered_set<unsigned long long> addresses;

    unsigned long long address = 0;
    fread(&address, 1, sizeof(unsigned long long), DataStruct::KeyFile);
    while(address) {
        addresses.insert(address);
        fread(&address, 1, sizeof(unsigned long long), DataStruct::KeyFile);
    }

    // std::cout << "Popping" << endl;
    // for(auto I = addresses.begin(); I != addresses.end(); ++I)
    //     std::cout << hex << *I << " ";
    // std::cout << endl;


    return addresses;
}





// int main()
// {

//     BTree B(const_cast<char *>("dump.bin"),4*1000*1000);

//     std::cout << "Did you delete dump.bin??" << endl;

//     //std::cout << "init" << endl;
//     B.init();

//     //std::cout << "doWork" << endl;
//     B.doWork();

//     // std::cout<< "trace" << endl;

//     // std::unordered_set<unsigned long long> address_set;
//     // do
//     // {
//     //  cout << endl;
//     //  address_set = B.pop();
//     //  for(auto address = address_set.begin(); address != address_set.end(); address++) {
//     //      cout << *address << endl;
//     //  }
//     // } while (address_set.size());


// }
