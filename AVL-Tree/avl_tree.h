#pragma once

#include "avl_node.h"
#include<vector>

using namespace std;

class avl_tree{
private:
	avl_node* root; // �����ڵ�

	avl_node* search_node(avl_node* cur, int key); // ���Ҷ�Ӧ���Ľڵ�
	avl_node* insert_node(avl_node* cur, int new_key); // �ݹ�����½ڵ�
	void destroy_tree(avl_node* cur); // �ݹ�������������Ľڵ�
	avl_node* delete_node(avl_node* cur, int key); // �ݹ�ɾ���ڵ�
	avl_node* get_sub_tree_min(avl_node* cur); // ����Ե�ǰ�ڵ�Ϊ���ڵ�������У���С��ֵ�Ľڵ�

public:
	// ���캯��
	avl_tree() {this->root = nullptr;}
	// avl_tree(avl_node* root): root(root) {}
	avl_tree(int key) {this->root = new avl_node(key);}

	// ��������
	~avl_tree();

	// get����
	avl_node* get_root() {return this->root;}

	avl_node* insert(int new_key); // �����½ڵ�
	avl_node* rebanlance(avl_node* cur); // ��Ե�ǰ�ڵ�Ϊ���ڵ������������ƽ��
	avl_node* turn_left_left(avl_node* cur); // LL
	avl_node* turn_right_right(avl_node* cur); // RR
	avl_node* turn_left_right(avl_node* cur); // LR
	avl_node* turn_right_left(avl_node* cur); // RL

	void update_height_b_factor(avl_node* cur); // ����ָ���ڵ���������������ߺ�ƽ������

	avl_node* search(int key); // ���Ҷ�Ӧ���Ľڵ�
	void del(int key); // ɾ����Ӧ�Ľڵ�
	void display_tree_attr(); // չʾ��������
	void display_layers(); // ���������չʾ��������Ԫ�� 
	void insert_batch(vector<int>& arr); // һ���Բ���һ������ 
};
