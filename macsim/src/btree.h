#ifndef BTREE_H
#define BTREE_H


#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cassert>
#include "global_defs.h"
#include "global_types.h"

using namespace std;


template<class key, class payload> class Element {

// contains a key value, a payload, and a pointer toward the subtree

// containing key values greater than this->m_key but lower than the

// key value of the next element to the right



public:

	key m_key;

	payload m_payload;

	Node* mp_subtree;

public:

	bool operator>   (Element& other) const { return m_key >  other.m_key; }

	bool operator<   (Element& other) const { return m_key <  other.m_key; }

	bool operator>=  (Element& other) const { return m_key >= other.m_key; }

	bool operator<=  (Element& other) const { return m_key <= other.m_key; }

	bool operator==  (Element& other) const { return m_key == other.m_key; }

	bool valid () const { return mp_subtree != reinterpret_cast<Node*> (-1); }

	void invalidate () { mp_subtree = reinterpret_cast<Node*> (-1); }

	Element& operator= (const Element& other) {

		m_key = other.m_key;

		m_payload = other.m_payload;

		mp_subtree = other.mp_subtree;

		return *this;

	}

	Element () { mp_subtree = reinterpret_cast<Node*> (0);; }

	void dump ();

}; //______________________________________________________________________



template<class key, class payload> void Element<key, payload>::dump () {

	cout << "key=" << m_key << "sub=" << mp_subtree << ' ';

} //_______________________________________________________________________



typedef Element<unsigned long long, string> Elem;



class RootTracker;



class Node {

protected:

    // locality of reference, beneficial to effective cache utilization,

    // is provided by a "vector" container rather than a "list"

	vector<Elem> m_vector;

    // number of elements currently in m_vector, including the zeroth element

    // which has only a subtree, no key value or payload.

	int m_count;

	Node* mp_parent;

	bool is_leaf();

	bool vector_insert (Elem& element);

	bool vector_insert_for_split (Elem& element);

	bool split_insert (Elem& element);

	bool vector_delete (Elem& target);

	bool vector_delete (int target_pos);

	void insert_zeroth_subtree (Node* subtree);

	void set_debug();

	int key_count () { return m_count-1; }

	Elem& largest_key () { return m_vector[m_count-1]; }

	Elem& smallest_key () { return m_vector[1]; }

	Elem& smallest_key_in_subtree();

	int index_has_subtree ();

	Node* right_sibling (int& parent_index_this);

	Node* left_sibling (int& parent_index_this);

	Node* rotate_from_left(int parent_index_this);

	Node* rotate_from_right(int parent_index_this);

	Node* merge_right (int parent_index_this);

	Node* merge_left (int parent_index_this);

	bool merge_into_root ();

	int minimum_keys ();

#ifdef _DEBUG

	Elem debug[8];

#endif

public:

	Elem& search (Elem& desired, Node*& last_visited);

	Elem& profile_search (Elem& desired, Node*& last_visited_ptr, FILE* FP, unsigned long long *buffer, int NBuffer);


	bool tree_insert (Elem& element);

	bool delete_element (Elem& target);

	int delete_all_subtrees ();

	Node* find_root();

    // to return a reference when a search fails.

	static Elem m_failure;

    // the root of the tree may change.  this attribute keeps it accessible.

	RootTracker& m_root;

	Elem& operator[] (int i) { return m_vector[i]; }

    // node cannot be instantiated without a root tracker

	Node (RootTracker& root_track);

	void dump ();



}; //______________________________________________________________________



class RootTracker {

// all the node instances that belong to a given tree have a reference to one

// instance of RootTracker.  as the Node instance that is the root may change

// or the original root may be deleted, Node instances must access the root

// of the tree through this tracker, and update the root pointer when they

// perform insertions or deletions.  using a static attribute in the Node

// class to hold the root pointer would limit a program to just one B-tree.

protected:

	Node* mp_root;

public:

	RootTracker() { mp_root = reinterpret_cast<Node*> (0);; }

	void set_root (Node* old_root, Node* new_root) {

        // ensure that the root is only being changed by a node belonging to the

        // same tree as the current root

		if (old_root != mp_root)

			throw "wrong old_root in RootTracker::set_root";

		else

			mp_root = new_root;

	}

	Node* get_root () { return mp_root; }



	~RootTracker () {

        // safety measure

		if (mp_root) {

			mp_root->delete_all_subtrees();

			delete mp_root;

		}

	}

}; //_______________________________________________________________________






// initialize static data at file scope. This is needed 



// int main(int argc, char* argv[])

// {

// // the main function is just some code to test the b-tree.  it inserts 10,000 elements,

// // then searches for each of them, then deletes them in reverse order (also tested in

// // forward order) and searches for all 10,000 elements after each deletion to ensure that

// // all remaining elements remain accessible.





// 	Elem elem;



// 	RootTracker tracker;  // maintains a pointer to the current root of the b-tree

// 	Node* root_ptr = new Node(tracker);

// 	tracker.set_root (reinterpret_cast<Node*> (0);, root_ptr);



// 	vector<long long int> search_vect;

//     // prepare the key strings

// 	search_vect.resize (10E6);

// 	int search_count = 0;

// 	for (int i=0; i<10E5;i++) {

// 		strstream stm;

// 		//stm << random()%10E6;

// 		search_vect[search_count++] = random()%10000;

// 	}

// 	string s;

// 	cout << "finished preparing key strings\n";


// 	for (int i=0; i<10E5; i++) {

// 		elem.m_key = search_vect[i];
// 		//std::cout << elem.m_payload << search_vect[i];

// 		elem.m_payload += " hi you";

// 		tracker.get_root()->tree_insert(elem);

// 	}

// 	cout << "finished inserting elements\n";

// 	Node * last;
// // Your code to measure

// 	for (int i=0; i<1000; i++) {

// 		Elem desired;

// 		desired.m_key = search_vect[i];

// 		Elem& result = tracker.get_root()->search (desired, last);

// 	}

// 	cout << "finished searching for elements\n";

// 	for (int i=9999; i>=0; i--) {

// 		Elem target;

// 		target.m_key = search_vect[i];

// 		tracker.get_root()->delete_element (target);

// 		Node * last;

// 	}


// 	cout << "after deletion" << endl;

// 	tracker.get_root()->dump();


// 	return 0;

// }



#endif //BTREE_H



