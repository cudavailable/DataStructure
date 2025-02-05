#pragma once

#include "avl_node.h"
#include<vector>

using namespace std;

class avl_tree{
private:
	avl_node* root; // 树根节点

	avl_node* search_node(avl_node* cur, int key); // 查找对应键的节点
	avl_node* insert_node(avl_node* cur, int new_key); // 递归插入新节点
	void destroy_tree(avl_node* cur); // 递归销毁树所分配的节点
	avl_node* delete_node(avl_node* cur, int key); // 递归删除节点
	avl_node* get_sub_tree_min(avl_node* cur); // 获得以当前节点为根节点的子树中，最小键值的节点

public:
	// 构造函数
	avl_tree() {this->root = nullptr;}
	// avl_tree(avl_node* root): root(root) {}
	avl_tree(int key) {this->root = new avl_node(key);}

	// 析构函数
	~avl_tree();

	// get函数
	avl_node* get_root() {return this->root;}

	avl_node* insert(int new_key); // 插入新节点
	avl_node* rebanlance(avl_node* cur); // 针对当前节点为根节点的子树进行重平衡
	avl_node* turn_left_left(avl_node* cur); // LL
	avl_node* turn_right_right(avl_node* cur); // RR
	avl_node* turn_left_right(avl_node* cur); // LR
	avl_node* turn_right_left(avl_node* cur); // RL

	void update_height_b_factor(avl_node* cur); // 对于指定节点的子树，更新树高和平衡因子

	avl_node* search(int key); // 查找对应键的节点
	void del(int key); // 删除对应的节点
	void display_tree_attr(); // 展示树的属性
	void display_layers(); // 层序遍历，展示树的所有元素 
	void insert_batch(vector<int>& arr); // 一次性插入一批数据 
};
