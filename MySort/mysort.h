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

int partition(vector<int>& arr, int left, int right);

void q_sort(vector<int>& arr, int left, int right);

int get_max_digit(vector<int> arr);

void exp_sort(vector<int>& arr, int exp);

/* SORT */
void bubble_sort(vector<int>& arr);

void choice_sort(vector<int>& arr);

void insert_sort(vector<int>& arr);

void merge_sort(vector<int>& arr);

void quick_sort(vector<int>& arr);

void radix_sort(vector<int>& arr);

void bucket_sort(vector<int>& arr);

void display(const vector<int>& arr);
