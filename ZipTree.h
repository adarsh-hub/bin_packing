#ifndef ZIPTREE_H
#define ZIPTREE_H

// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file
#include "project2.h"
#include <random>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

template <typename KeyType, typename ValType>
class ZipNode
{
public:
    //create constructor
    ZipNode();
    ~ZipNode();
    
    KeyType z_key;
    ValType z_value;
    unsigned z_rank;
    ZipNode *z_left;
    ZipNode *z_right;
    
};

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>::ZipNode(){
	this->z_left = 0;
	this->z_right = 0;
}

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>::~ZipNode(){
	delete z_left;
	delete z_right;
}

template <typename KeyType, typename ValType>
class ZipTree
{
public:
	// DO NOT MODIFY METHOD SIGNATURES BELOW THIS LINE
	ZipTree();
	~ZipTree();
	static unsigned getRandomRank();
	void insert(const KeyType &key, const ValType &val, unsigned rank = getRandomRank());
	void remove(const KeyType& key);
	ValType find(const KeyType& key);
	unsigned getSize();
	int getHeight();
	unsigned getDepth(const KeyType& key);
	std::vector<ZipNode<KeyType, ValType>*> nodelist;
	// DO NOT MODIFY METHOD SIGNATURES ABOVE THIS LINE

	// define new public methods
	int nodecount = 0;
	ZipNode<KeyType, ValType> *root;
	const double p_value = 0.5;
	int max(int a, int b);
	unsigned getDepth_rec(ZipNode<KeyType, ValType> *node, const KeyType& key, unsigned depth);
	int tree_height(ZipNode<KeyType, ValType> *rt);
	ZipNode<KeyType, ValType>* insert_rec(ZipNode<KeyType, ValType> *x,ZipNode<KeyType, ValType> *rt);
	ZipNode<KeyType, ValType>* find_node(const KeyType& key);
	void destroyZip(ZipNode<KeyType, ValType> *node);
	void update(KeyType key, ValType val);
	ZipNode<KeyType, ValType>* inorder(ZipNode<KeyType, ValType>* root, double item);
	ZipNode<KeyType, ValType>* binorder(ZipNode<KeyType, ValType>* root, double item);
	ZipNode<KeyType, ValType>* delete_rec(ZipNode<KeyType, ValType>* x, ZipNode<KeyType, ValType>* root);
	ZipNode<KeyType, ValType>* zip(ZipNode<KeyType, ValType>* x, ZipNode<KeyType, ValType>* y);
	
private:
	// define private methods
};

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>* ZipTree<KeyType, ValType>::binorder(ZipNode<KeyType, ValType>* root, double item){
	
	ZipNode<KeyType, ValType> *notfound = new ZipNode<KeyType, ValType>();
	ZipNode<KeyType, ValType> *temp;
	notfound->z_key = 999;
	KeyType key;
	double min = 999.00;
	
	for(int i=0; i<this->nodelist.size(); i++){
		temp = this->nodelist[i];
		if( temp->z_value - item > -1e-6){
			if(temp->z_value - item<min){
				min = temp->z_value - item;
				key = temp->z_key;
			}
		}
	}
	
	return find_node(key);
}

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>* ZipTree<KeyType, ValType>::inorder(ZipNode<KeyType, ValType>* root, double item){
	
	ZipNode<KeyType, ValType> *notfound = new ZipNode<KeyType, ValType>();
	notfound->z_key = 999; 
	ZipNode<KeyType, ValType> *temp;
	
	for(int i=0; i<this->nodelist.size(); i++){
		temp = this->nodelist[i];
		if( temp->z_value - item > -1e-6){
			return temp;
		}
	}
	
	return notfound;
}


// fill in the definitions for each required member function and for any additional member functions you define
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::update(KeyType key, ValType val){
	ZipNode<KeyType, ValType>* node = find_node(key);
	node->z_value = val;
}

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>* ZipTree<KeyType, ValType>::insert_rec(ZipNode<KeyType, ValType> *x,ZipNode<KeyType, ValType> *rt)
{
	//std::cout << "INSERT REC" << std::endl;
	//std::cout << "log 1" << std::endl;
	if(this->root == nullptr){
		//std::cout << "inserting in root" << std::endl;
		this->root = x;
	}
	else if( rt == nullptr ){
		//std::cout << "second param is null" << std::endl;
		x->z_left = 0;
		x->z_right = 0;
		return x;
	}
	
	//std::cout << "log 2" << std::endl;
	if(x->z_key < rt->z_key){
		
	//std::cout << "log 3" << std::endl;
		if(insert_rec(x, rt->z_left)==x){
			
	//std::cout << "log 4" << std::endl;
	//std::cout << "Rank a: " <<x->z_rank<< std::endl;
	//std::cout << "Rank b: " <<rt->z_rank<< std::endl;
			if(x->z_rank<rt->z_rank){
				
	//std::cout << "inserting in left child" << std::endl;
				rt->z_left = x;
			}
			else{
				
	//std::cout << "log 5" << std::endl;
				rt->z_left = x->z_right;
				x->z_right = rt;
				return x;
			}
		}
	}
	else{
		
	//std::cout << "log 6" << std::endl;
		if(insert_rec(x, rt->z_right)==x){
			
	//std::cout << "log 7" << std::endl;
			if(x->z_rank<=rt->z_rank){
				
	//std::cout << "log inserting in right child" << std::endl;
				rt->z_right = x;
			}
			else{
				
	//std::cout << "log 8" << std::endl;
				rt->z_right = x->z_left;
				x->z_left = rt;
				return x;
			}
		}
	}
	
	//std::cout << "log 10" << std::endl;
	return rt;
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::destroyZip(ZipNode<KeyType, ValType> *node){
	if (node)
    {
        destroyZip(node->z_left);
        destroyZip(node->z_right);
        delete node;
    }
}

template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::ZipTree()
{
	srand(time(0));
	this->root = new ZipNode<KeyType, ValType>;
}

template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::~ZipTree()
{
	//destroyZip(this->root);
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getRandomRank()
{	
  	int p[100]={};
  	std::geometric_distribution<int> distribution(0.5);
  	static std::default_random_engine generator;
	int number;
	for (unsigned i = 0; i < 100; ++i)
	{
  		number = distribution(generator);
  		p[i] = number;
	}
	int index = rand()%100;
	return p[index];
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::insert(const KeyType& key, const ValType& val, unsigned rank)
{
	this->nodecount++;
	ZipNode<KeyType, ValType> *x = new ZipNode<KeyType, ValType>;
	ZipNode<KeyType, ValType> *prev;
	ZipNode<KeyType, ValType> *fix = this->root;
	x->z_key = key;
	x->z_value = val;
	x->z_rank = rank;
	nodelist.push_back(x);
	
	this->root = insert_rec(x, this->root);
}

// TODO: REMOVE/DELETE
template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>* ZipTree<KeyType, ValType>::zip(ZipNode<KeyType, ValType>* x, ZipNode<KeyType, ValType>* y){
	if(x==nullptr){
		return y;
	}
	if(y==nullptr){
		return x;
	}
	
	if(x->z_rank < y->z_rank){
		y->z_left = zip(x, y->z_left);
		return y;
	}
	else{
		x->z_right = zip(x->z_right, y);
		return x;
	}
}

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>* ZipTree<KeyType, ValType>::delete_rec(ZipNode<KeyType, ValType>* x, ZipNode<KeyType, ValType>* rt){
	if(x->z_key == rt->z_key){
		return zip(rt->z_left, rt->z_right);
	}
	if(x->z_key < rt->z_key){
		if(x->z_key == rt->z_left->z_key){
			rt->z_left = zip( rt->z_left->z_left, rt->z_left->z_right );
		}
		else{
			delete_rec(x, rt->z_left);
		}
	}
	else{
		if(x->z_key == rt->z_right->z_key){
			rt->z_right = zip( rt->z_right->z_left, rt->z_right->z_right );
		}
		else{
			delete_rec(x, rt->z_right);
		}
	}
	return rt;
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::remove(const KeyType& key)
{
	ZipNode<KeyType, ValType> *temp = find_node(key);
	this->root = delete_rec(temp, this->root);
}

// DONE: FIND
template <typename KeyType, typename ValType>
ValType ZipTree<KeyType, ValType>::find(const KeyType& key)
{
	ZipNode<KeyType, ValType> *rt = this->root;
	while(rt){
		if(key<rt->z_key){
			rt = rt->z_left;
		} else if (rt->z_key < key){
			rt = rt->z_right;
		}
		else{
			return rt->z_value;
		}
	}
	//return 0; // remove this line when you implement this function
}

template <typename KeyType, typename ValType>
ZipNode<KeyType, ValType>* ZipTree<KeyType, ValType>::find_node(const KeyType& key)
{
	ZipNode<KeyType, ValType> *notfound = new ZipNode<KeyType, ValType>();
	notfound->z_key = 999;
	
	int i = this->nodelist.size();
	ZipNode<KeyType, ValType>* temp;
	for(int j = 0; j<i; j++){
		temp = this->nodelist[j];
		if(temp->z_key == key){
			return temp;
		}
	}
	
	return notfound;
}

// DONE: SIZE 
template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getSize()
{
	return this->nodecount; 
}

// DONE: HEIGHT
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::getHeight()
{
	
	return tree_height(this->root)-1;
}

template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::tree_height(ZipNode<KeyType, ValType> *rt){
	
	if (!rt)
        return 0;
    else {
        int left_height = tree_height(rt->z_left);
        int right_height = tree_height(rt->z_right);
        if (left_height >= right_height){
				return left_height + 1;
		}
        else{
			return right_height + 1;
		}
    }
}

template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::max(int a, int b){
	if(a>b){
		return a;
	}
	return b;
	
}
// DONE: DEPTH
template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getDepth(const KeyType& key)
{	
	return getDepth_rec(this->root, key, 0); // remove this line when you implement this function
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getDepth_rec(ZipNode<KeyType, ValType> *node, const KeyType& key, unsigned depth)
{
	unsigned downdepth = 0;
	if (node == NULL) 
        return 0; 
  
    if (node->z_key == key)
        return depth; 
  
    downdepth = getDepth_rec(node->z_left,key, depth + 1); 
    
    if (downdepth != 0) 
        return downdepth; 
  
    downdepth = getDepth_rec(node->z_right, key, depth + 1);
    return downdepth; 
}

#endif
