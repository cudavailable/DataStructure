#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
using std::vector;

enum Order{
	ASC, DESC
};

void swap(int& a, int& b);

void merge(vector<int>& arr, int left, int mid, int right);

void m_sort(vector<int>& arr, int left, int right);

vector<int>& bubble_sort(vector<int>& arr);

vector<int>& choice_sort(vector<int>& arr);

vector<int>& insert_sort(vector<int>& arr);

vector<int>& merge_sort(vector<int>& arr);

vector<int> quick_sort(vector<int> arr);

vector<int> radix_sort(vector<int> arr);

vector<int> bucket_sort(vector<int> arr);

void display(const vector<int>& arr);
