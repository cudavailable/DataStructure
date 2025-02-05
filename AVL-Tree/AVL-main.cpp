#include<iostream>
#include<vector>

#include "avl_tree.cpp"
using namespace std;

/**
	main��������	
*/

int main(){

	avl_tree* t = new avl_tree(); // root = nullptr
	
//	t->insert(12);
//	t->insert(13);
//	t->display_tree_attr();
//	
//	t->insert(14);
//	t->display_tree_attr();
//	t->display_layers(); 
//	
//	t->del(14);
//	t->display_tree_attr(); 

	vector<int> arr = {10, 5, 16, 20, 11};
	t->insert_batch(arr); // ���Բ��������� 
	t->display_layers(); // ����չʾ 
	
	t->del(16);
	t->display_layers();
	
	t->del(5);
	t->display_layers();

	delete t;
	return 0;
}
