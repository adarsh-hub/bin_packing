#include <vector>
#include "ZipTree.h"
#include "project2.h"
// each file should #include this header file
// implement in next_fit.cpp
void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	ZipTree<int, double> tree;
	int bin = 1;
	double max_cap = 1.0;
	tree.insert(bin, max_cap);
	
	double cur = 1.0;
	for(int i = 0; i<items.size();i++){
		double cur_b = items[i];
		//if space in current bucket, insert the item
		if(cur - cur_b >= -.0001){
			tree.update(bin, cur - cur_b);
			cur = cur - cur_b;
			assignment[i] = bin;
		} 
		else{
			//Create new bucket
			bin++;
			tree.insert(bin, 1.0-cur_b);
			cur = 1.0 - cur_b;
			assignment[i] = bin;
		}
	}
	
	for (int i = 1; i <= bin; i++) {
		free_space.push_back(tree.find(i));
	}
	
}

