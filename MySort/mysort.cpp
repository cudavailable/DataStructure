#include "mysort.h"

using namespace std;

void swap(int& a, int& b){
	int t = a;
	a = b;
	b = t;
}

void merge(vector<int>& arr, int left, int mid, int right){
	vector<int> left_arr(arr.begin()+left, arr.begin()+mid+1); // [left, mid]
	vector<int> right_arr(arr.begin()+mid+1, arr.begin()+right+1); // [mid+1, right]
	
	int i=0, j=0, k=left;
	while(i < left_arr.size() && j < right_arr.size()){
		if(left_arr[i] <= right_arr[j]){
			arr[k++] = left_arr[i++];
		}else{
			arr[k++] = right_arr[j++];
		}
	}
	
	while(i < left_arr.size()) arr[k++] = left_arr[i++];
	while(j < right_arr.size()) arr[k++] = right_arr[j++];
}

void m_sort(vector<int>& arr, int left, int right){
	if(left >= right)
		return ;
		
	// devision
	int mid = left + (right-left)/2;
	m_sort(arr, left, mid); // left sort: [left, mid]
	m_sort(arr, mid+1, right); // right sort: [mid+1, right]
	merge(arr, left, mid, right); // merge specifying the boundary
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

vector<int>& merge_sort(vector<int>& arr){
	// sort index: [0, size-1]
	m_sort(arr, 0, arr.size()-1);
}

int partition(vector<int>& arr, int left, int right){
	int pivot = arr[right];
	int i = left-1;
	
	for(int j=left; j < right; j++){
		if(arr[j] <= pivot){
			i++;
			swap(arr[i], arr[j]);
		}
	}
	
	swap(arr[i+1], arr[right]);
	return i+1;
}

void q_sort(vector<int>& arr, int left, int right){
	if(left < right){
		int pivot = partition(arr, left, right);
		q_sort(arr, left, pivot-1);
		q_sort(arr, pivot+1, right);
	}
}

vector<int>& quick_sort(vector<int>& arr){
	// sort index: [0, size-1]
	q_sort(arr, 0, arr.size()-1);
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
