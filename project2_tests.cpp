#include "ZipTree.h"
#include "project2.h"

#include <iostream>
#include <utility>
#include <string>
#include <cmath>

// Instructions
// Some test cases for the ZipTree and bin packing algorithms can be found in the main function below
//
// 1. Move all source code/header files you will be submitting to a new directory, along with the two files Makefile and project2_tests.cpp
// 2. Edit the main function to create and try different test cases on your algorithms
// 3. Enter the command "make" to compile and run the program
// 4. If you make any changes to any of the files, enter the command "make clean" to remove the generated executable before entering "make" again.
//
// note that passing the test cases here does not necessarily mean your zip tree or algorithms will pass other cases
// so it's a good idea to create and try different test cases for both

/****INSERT ALGOS HERE****/
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
/************************/


typedef struct ProblemInstance {
	std::vector<double> items;
	std::vector<int> assignments;
	std::vector<double> free_space;
} ProblemInstance;

template <typename KeyType, typename ValType>
struct InsertType
{
	KeyType key;
	ValType val;
	unsigned rank;
};

typedef void (*algorithm) (const std::vector<double>&, std::vector<int>&, std::vector<double>&);

template <typename KeyType, typename ValType>
void initializeTreeWithData (ZipTree<KeyType, ValType>& tree, std::vector<InsertType<KeyType, ValType>> data)
{
	for (const auto& item : data) {
		tree.insert(item.key, item.val, item.rank);
	}
}

bool compare(const std::vector<double>& v1, const std::vector<double>& v2)
{
	// floating point comparison
	for (int i = 0; i<v1.size(); i++) {
		if (std::fabs(v1[i] - v2[i]) > 1e-3) {
			return false;
		}
	}
	return true;
}

void testAlgorithm(ProblemInstance test, ProblemInstance expected_result, algorithm algo, std::string name)
{
	algo(test.items, test.assignments, test.free_space);
	if (test.assignments == expected_result.assignments and compare(test.free_space, expected_result.free_space)) {
		std::cout << "Test case passed: " <<  name << std::endl;
	}
	else {
		std::cout << "Test case failed: " <<  name << std::endl;
	}
}

int main()
{
	// ------------------
	// ZipTree tests
	// ------------------
	std::cout << "testing ZipTree" << std::endl;

	// define key/value pairs
	ZipTree<int, char> tree;
	std::vector<InsertType<int, char>> data = {{4, 'a', 0}, {5, 'b', 0}, {2, 'c', 2}, {1, 'd', 1}};
	initializeTreeWithData(tree, data);
	std::cout << "find(4): " << tree.find(4) << ", Expected: a" << std::endl;
	std::cout << "getSize(): " << tree.getSize() << ", Expected: 4" << std::endl;
	std::cout << "getHeight(): " << tree.getHeight() << ", Expected: 2" << std::endl;
	std::cout << "getDepth(2): " << tree.getDepth(2) << ", Expected: 0" << std::endl;
	std::cout << "getDepth(1): " << tree.getDepth(1) << ", Expected: 1" << std::endl;
	tree.insert(0, 'e', 1);
	std::cout << "getSize(): " << tree.getSize() << ", Expected: 5" << std::endl;
	std::cout << "getHeight(): " << tree.getHeight() << ", Expected: 2" << std::endl;
	std::cout << "getDepth(2): " << tree.getDepth(2) << ", Expected: 0" << std::endl;
	std::cout << "getDepth(1): " << tree.getDepth(1) << ", Expected: 2\n" << std::endl;

	ZipTree<int, char> tree2;
	std::vector<InsertType<int, char>> data2 = {{4, 'a', 2}, {5, 'b', 3}, {2, 'c', 1}, {1, 'd', 0}, {0, 'e', 1}};
	initializeTreeWithData(tree2, data2);
	std::cout << "find(4): " << tree2.find(4) << ", Expected: a" << std::endl;
	std::cout << "getSize(): " << tree2.getSize() << ", Expected: 5" << std::endl;
	std::cout << "getHeight(): " << tree2.getHeight() << ", Expected: 4" << std::endl;
	std::cout << "getDepth(2): " << tree2.getDepth(2) << ", Expected: 3" << std::endl;
	std::cout << "getDepth(1): " << tree2.getDepth(1) << ", Expected: 4" << std::endl;

	std::cout << "\ntesting random rank generation" << std::endl;
	unsigned rank_sum = 0u;
	unsigned num_ranks = 10000u;
	for (unsigned i = 0u; i < num_ranks; ++i)
	{
		rank_sum += ZipTree<int, char>::getRandomRank();
	}
	double rank_mean = static_cast<double>(rank_sum) / num_ranks;

	std::cout << "random rank mean: " << rank_mean << ", Expected: ~1" << std::endl;

	// add new tests


	// ------------------
	// bin packing tests
	// ------------------
	std::cout << std::endl;
	std::cout << "testing bin packing" << std::endl;
	std::cout << "test 1" << std::endl;

	// define list of items
	std::vector<double> items {0.1, 0.8, 0.3, 0.5, 0.7, 0.2, 0.6, 0.4};
	std::vector<int> assignments(items.size(), 0);
	std::vector<double> free_space;
	ProblemInstance test1 = {items, assignments, free_space}, expected_result;

	// next_fit
	expected_result = {items, {1, 1, 2, 2, 3, 3, 4, 4}, {0.1, 0.2, 0.1, 0.0}};
	testAlgorithm(test1, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 1, 2, 2, 3, 2, 4, 4}, {0.1, 0.0, 0.3, 0.0}};
	testAlgorithm(test1, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 3, 2, 1, 4}, {0.0, 0.0, 0.0, 0.4}};
	testAlgorithm(test1, expected_result, first_fit_decreasing, "first_fit_decreasing");

	// best_fit
	expected_result = {items, {1, 1, 2, 2, 3, 2, 4, 4}, {0.1, 0.0, 0.3, 0.0}};
	testAlgorithm(test1, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 3, 2, 1, 4}, {0.0, 0.0, 0.0, 0.4}};
	testAlgorithm(test1, expected_result, best_fit_decreasing, "best_fit_decreasing");

	// ----------------------------------test 2 ----------------------------------
	std::cout << std::endl;
	std::cout << "test 2" << std::endl;
	items = {0.79, 0.88, 0.95, 0.12, 0.05, 0.46, 0.53, 0.64, 0.04, 0.38, 0.03, 0.26};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test2 = {items, assignments, free_space};

	// next_fit
	expected_result = {items, {1, 2, 3, 4, 4, 4, 5, 6, 6, 7, 7, 7}, {0.21, 0.12, 0.05, 0.37, 0.47, 0.32, 0.33}};
	testAlgorithm(test2, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 2, 3, 1, 1, 4, 4, 5, 1, 6, 2, 5}, {0, 0.09, 0.05, 0.01, 0.1, 0.62}};
	testAlgorithm(test2, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 5, 6, 4, 2, 1, 3, 3}, {0, 0, 0.14, 0.1, 0.01, 0.62}};
	testAlgorithm(test2, expected_result, first_fit_decreasing, "first_fit_decreasing");

	// best_fit
	expected_result = {items, {1, 2, 3, 2, 3, 4, 4, 5, 1, 6, 1, 5}, {0.14, 0, 0, 0.01, 0.1, 0.62}};
	testAlgorithm(test2, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 5, 6, 4, 2, 1, 4, 4}, {0, 0, 0.21, 0.03, 0.01, 0.62}};
	testAlgorithm(test2, expected_result, best_fit_decreasing, "best_fit_decreasing");

	// ----------------------------------test 3 ----------------------------------
	std::cout << std::endl;
	std::cout << "test 3" << std::endl;
	items = {0.43, 0.75, 0.25, 0.42, 0.54, 0.03, 0.64};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test3 = {items, assignments, free_space};

	// next_fit
	expected_result = {items, {1, 2, 2, 3, 3, 3, 4}, {0.57, 0, 0.01, 0.36}};
	testAlgorithm(test3, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 2, 1, 3, 3, 1, 4}, {0.29, 0.25, 0.04, 0.36}};
	testAlgorithm(test3, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 3, 4, 1, 2}, {0, 0.33, 0.03, 0.58}};
	testAlgorithm(test3, expected_result, first_fit_decreasing, "first_fit_decreasing");

	// best_fit
	expected_result = {items, {1, 2, 2, 1, 3, 1, 4}, {0.12, 0, 0.46, 0.36}};
	testAlgorithm(test3, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 3, 4, 1, 3}, {0, 0.36, 0, 0.58}};
	testAlgorithm(test3, expected_result, best_fit_decreasing, "best_fit_decreasing");

	// ----------------------------------test 4----------------------------------
	std::cout << std::endl;
	std::cout << "test 4" << std::endl;
	items = {0.54, 0.67, 0.46, 0.57, 0.06, 0.23, 0.83, 0.64, 0.47, 0.03, 0.53, 0.74, 0.36, 0.24, 0.07, 0.25, 0.05, 0.63, 0.43, 0.04};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test4 = {items, assignments, free_space};

	// next_fit
	expected_result = {items, {1, 2, 3, 4, 4, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10, 10, 10, 11, 12, 12}, {0.46, 0.33, 0.54, 0.14, 0.17, 0.36, 0.5, 0.47, 0.26, 0.03, 0.37, 0.53}};
	testAlgorithm(test4, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 2, 1, 3, 2, 2, 4, 5, 6, 2, 6, 7, 3, 5, 3, 7, 4, 8, 9, 4}, {0, 0.01, 0, 0.08, 0.12, 0, 0.01, 0.37, 0.57}};
	testAlgorithm(test4, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 4, 2, 3, 5, 1, 1, 3, 1, 3}, {0, 0.01, 0.01, 0, 0.14, 0, 0, 0}};
	testAlgorithm(test4, expected_result, first_fit_decreasing, "first_fit_decreasing");

	// best_fit
	expected_result = {items, {1, 2, 1, 3, 2, 2, 4, 5, 6, 2, 6, 7, 5, 7, 4, 3, 4, 8, 9, 4}, {0, 0.01, 0.18, 0.01, 0, 0, 0.02, 0.37, 0.57}};
	testAlgorithm(test4, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 4, 2, 3, 5, 3, 5, 5, 1, 5}, {0.13, 0.01, 0.02, 0, 0, 0, 0, 0}};
	testAlgorithm(test4, expected_result, best_fit_decreasing, "best_fit_decreasing");
	return 0;
}

