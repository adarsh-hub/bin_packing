#include <vector>
#include "ZipTree.h"
#include "project2.h"
#include <algorithm>
//insertion sort
void insertion_sort(std::vector<double>& nums) {
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
void reverse(std::vector<double>& arr)
{
	double temp;
	int end = arr.size();
	for (int low = 0, high = end - 1; low < high; low++, high--) {
		temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
    }
}

//implement in first_fit.cpp
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	ZipTree<int, double> tree;
	int bin = 1;
	double max_cap = 1.0;
	tree.insert(bin, max_cap);
	
	ZipNode<int, double>* temp;
	double cur = 1.0;
	int i = 0;
	while(i < items.size()){
		temp = tree.inorder(tree.root, items[i]);
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
		if(tree.find(i)<0 || tree.find(i)<1e-9){
			free_space.push_back(0);
		}
		else{
		free_space.push_back(tree.find(i));
	}
	}
	
	return;
}
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space){
	std::vector<double> reverseItems(items);
	insertion_sort(reverseItems);
	reverse(reverseItems);
	//std::reverse(reverseItems.begin(),reverseItems.end());
	first_fit(reverseItems, assignment, free_space);
	return;
}

//int main(){
//	std::vector<double> items {0.54, 0.67, 0.46, 0.57, 0.06, 0.23, 0.83, 0.64, 0.47, 0.03, 0.53, 0.74, 0.36, 0.24, 0.07, 0.25, 0.05, 0.63, 0.43, 0.04};
//	std::vector<int> assignments(items.size(), 0);
//	std::vector<double> free_space;
//	
//	first_fit(items, assignments, free_space);
//	
//	std::cout << "Assignments" << std::endl;
//	std::cout << "{";
//	for(int i = 0; i<assignments.size();i++){
//		std::cout << assignments[i] << ", ";
//	}
//	std::cout << "}"<<std::endl;
//	
//	std::cout << "Free Space" << std::endl;
//	std::cout << "{" ;
//	for(int j = 0; j<free_space.size();j++){
//		std::cout << free_space[j] << ", ";
//	}
//	std::cout << "}";
//	//expected_result = {{1, 2, 1, 3, 2, 2, 4, 5, 6, 2, 6, 7, 3, 5, 3, 7, 4, 8, 9, 4}, {0, 0.01,   0,    0.08, 0.12, 0, 0.01, 0.37, 0.57}};
//	//                   {1, 2, 1, 3, 2, 2, 4, 5, 6, 2, 6, 7, 3, 5, 3, 7, 4, 8, 9, 4}, {0, 0.01, 5e-017, 0.08, 0.12, 0, 0.01, 0.37, 0.57, }
//	
//	return 0;
//}
