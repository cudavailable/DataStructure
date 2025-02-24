#include <iostream>
#include <cstdlib>
#include "mysort.h"
#include "mysort.cpp"
using namespace std;

int main(){
    vector<int> arr = {3, 4, 10, 384, 943, 23, 21, -1, 200, -163};
	//bubble_sort(arr);
	choice_sort(arr);
	display(arr);
    return 0;
}
