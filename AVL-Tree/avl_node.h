#pragma once

class avl_node{
	// ������Ԫ
	friend class avl_tree;

private:
	avl_node* left; // ָ����ڵ� 
	avl_node* right; // ָ���ҽڵ�
	int key; // �ڵ������С����
	int height; // �ڵ�߶�
	int b_factor; // ƽ������

public:
	// ���캯��
	avl_node(){}
	avl_node(int key): key(key), height(1), left(nullptr), right(nullptr), b_factor(0) {}

	// ��������
	// ����Ҫ������������Ϊ�����������ٵ��߼���new�����ڴ����������������ɵģ��ڵ����в�δnew��
	// ~avl_node() {delete left; delete right; std::cout<<"���ýڵ����������"<<endl;}

	// get����
	int get_key() {return this->key;}
	int get_height() {return this==nullptr? 0 : this->height;}
	avl_node* get_left() {return this->left;}
	avl_node* get_right() {return this->right;}
	int get_b_factor() {return this->b_factor;}
	
	// set����
	void set_key(int key) {this->key = key;}
	void set_left(avl_node* left) {this->left = left;}
	void set_right(avl_node* right) {this->right = right;}
	// void set_height(int height) {this->height = height;}
	// void set_b_factor(int b_factor) {this->b_factor = b_factor;}
};

