#include "mysort.h"

using namespace std;

void swap(int& a, int& b){
	int t = a;
	a = b;
	b = t;
}

/* Default: ASC */
vector<int>& bubble_sort(vector<int>& arr){
	for(int i=arr.size()-1; i > 0; i--){
		for(int j=0; j < i; j++){
			// compare arr[j], arr[j+1]
			if(arr[j] > arr[j+1]){
				swap(arr[j], arr[j+1]);
			}
		}	
	}
	
	return arr;
}

vector<int>& choice_sort(vector<int>& arr){
	for(int i=0; i < arr.size()-1; i++){
		for(int j=i+1; j < arr.size(); j++){
			// compare arr[j], arr[i]
			if(arr[j] < arr[i]){
				swap(arr[j], arr[i]);
			}
		}
	}
	
	return arr;
}

vector<int>& insert_sort(vector<int>& arr){
	for(int i=1; i < arr.size(); i++){
		int tmp = arr[i]; // keep the value
		int j = i-1;
		
		while(j >= 0 && arr[j]>tmp){ // compare arr[j], tmp-value
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
	}
	
	return arr;
}

vector<int> merge_sort(vector<int> arr){

}

vector<int> quick_sort(vector<int> arr){

}

vector<int> radix_sort(vector<int> arr){

}

vector<int> bucket_sort(vector<int> arr){

}

void display(const vector<int>& arr){
	for(int x : arr){
		cout << x << " ";
	}
	cout << endl;
}
