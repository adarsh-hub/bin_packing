#include <vector>
#include "ZipTree.h"
#include "project2.h"

//insertion sort
void insertion_sort2(std::vector<double>& nums) {
	int i,j;
	double temp;
	int size = nums.size();
	for(i = 1; i<size; i++){
		j=i;
		temp = nums[i];
		while(j>0 && nums[j-1]>temp){
			nums[j] = nums[j-1];
			j--;
		}
		nums[j] = temp;
	}
}

//reverse
void reverse2(std::vector<double>& arr)
{
	double temp;
	int end = arr.size();
	for (int low = 0, high = end - 1; low < high; low++, high--) {
		temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
    }
}
// implement in best_fit.cpp
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	ZipTree<int, double> tree;
	int bin = 1;
	double max_cap = 1.0;
	tree.insert(bin, max_cap);
	
	ZipNode<int, double>* temp;
	double cur = 1.0;
	int i = 0;
	while(i < items.size()){
		temp = tree.binorder(tree.root, items[i]);
		if(temp->z_key != 999){
			tree.update(temp->z_key, temp->z_value - items[i]);
			assignment[i] = temp->z_key;
		}
		else{
			bin++;
			tree.insert(bin, max_cap- items[i]);
			assignment[i] = bin;
		}
		i++;
	}
	
	for (int i = 1; i <= bin; i++) {
		if(tree.find(i)<0||tree.find(i)<1e-9){
			free_space.push_back(0);
		}
		else{
		free_space.push_back(tree.find(i));
	}
	}
	
	return;
}
void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	std::vector<double> reverseItems(items);
	insertion_sort2(reverseItems);
	reverse2(reverseItems);
	//std::reverse(reverseItems.begin(),reverseItems.end());
	best_fit(reverseItems, assignment, free_space);
	return;
}

