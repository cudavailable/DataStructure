#include <iostream>
#include <cstdlib>
#include "mysort.h"
#include "mysort.cpp"
using namespace std;

int main(){
//    vector<int> arr = {3, 4, 10, 384, 943, 23, 21, -1, 200, -163};
	vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
	//bubble_sort(arr);
	//choice_sort(arr);
	//insert_sort(arr);
	//merge_sort(arr);
	//quick_sort(arr);
	//radix_sort(arr);
	bucket_sort(arr);
	display(arr);
    return 0;
}
