#pragma once

class avl_node{
	// 定义友元
	friend class avl_tree;

private:
	avl_node* left; // 指向左节点 
	avl_node* right; // 指向右节点
	int key; // 节点排序大小依据
	int height; // 节点高度
	int b_factor; // 平衡因子

public:
	// 构造函数
	avl_node(){}
	avl_node(int key): key(key), height(1), left(nullptr), right(nullptr), b_factor(0) {}

	// 析构函数
	// 不需要析构函数，因为树类会调用销毁的逻辑。new开辟内存操作是在树类中完成的，节点类中并未new过
	// ~avl_node() {delete left; delete right; std::cout<<"调用节点的析构函数"<<endl;}

	// get函数
	int get_key() {return this->key;}
	int get_height() {return this==nullptr? 0 : this->height;}
	avl_node* get_left() {return this->left;}
	avl_node* get_right() {return this->right;}
	int get_b_factor() {return this->b_factor;}
	
	// set函数
	void set_key(int key) {this->key = key;}
	void set_left(avl_node* left) {this->left = left;}
	void set_right(avl_node* right) {this->right = right;}
	// void set_height(int height) {this->height = height;}
	// void set_b_factor(int b_factor) {this->b_factor = b_factor;}
};

