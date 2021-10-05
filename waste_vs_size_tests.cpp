#include "ZipTree.h"
#include "project2.h"
#include "first_fit.cpp"
#include "best_fit.cpp"
#include "next_fit.cpp"

#include <chrono>
#include <functional>
#include <cmath>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <locale.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdio>
#include <unordered_map>
#include <time.h>
#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <vector>
using namespace std;


static std::default_random_engine generator;

double gennum()
{	
	int p[100]={};
  	std::uniform_real_distribution<double> distribution(0.0, 0.6);
	double number;
	for (unsigned i = 0; i < 100; ++i)
	{
  		number = distribution(generator);
  		p[i] = number;
	}
	int index = rand()%100;
	return number;
}

std::vector<double> get_input(int n){
	
	std::vector<double> result;
	for(int i =0; i <n;i++){
		result.push_back(gennum()); 
	}
	return result;
}

double sum(std::vector<double>& arr){
	double s = 0.0;
	for(int i=0;i<arr.size();i++){
		s += arr[i];
	}
	
	return s;
}

double run_algo(int size){
	
	double s;
	std::cout << "INPUT SIZE: " << size << std::endl;
	std::vector<double> items = get_input(size);
	std::vector<int> assignments(items.size(), 0);
	std::vector<double> free_space;
	next_fit(items, assignments, free_space);
	std::cout << "WASTE W(A) = " << free_space.size()- sum(items) << std::endl;
	s = sum(free_space);
	items.clear();
	assignments.clear();
	free_space.clear();
	return s;
}

int power(int x, int y){
    int result = 1;
	for(int m = 0; m<y; m++){
		result = result*x; 
	}
	return result;
}

int main()
{
	
	fstream fout;
    fout.open("NextFit.csv", ios::out | ios::app);
	char input;
	char input2;
	int size;
	double waste;
	int i;
	int j;
	
	for(i = 100; i <= 10000 ; i+=100){
		size = i;
		for(j = 1; j <= 10; j++){
		waste = run_algo(size);
		fout<<size<<", "<<waste;
		}
		fout<<endl;
	}

	
	return 0;
}
