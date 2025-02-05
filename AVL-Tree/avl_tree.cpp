#include<iostream>
#include<vector>
#include<queue>

#include "avl_node.h"
#include "avl_tree.h"
using namespace std;

/**
	AVL树CPP代码实现	
*/

/**
 * 递归销毁树所分配的节点
 */
void avl_tree::destroy_tree(avl_node* cur){
	if(cur == nullptr){
		return ;
	}

	// 销毁左右子树
	this->destroy_tree(cur->left);
	this->destroy_tree(cur->right);

	// 销毁当前节点
	delete cur;
}

/**
 * 析构函数
 */
avl_tree::~avl_tree(){
	this->destroy_tree(this->root);
	std::cout << "调用树的析构函数" << endl;
}

/**
 * 更新树高和平衡因子
 */
void avl_tree::update_height_b_factor(avl_node* cur){
	if(cur == nullptr){
		cerr << "传入节点为空，无法更新树高！" << endl;
		return;
	}

	int left_height = cur->left->get_height();
	int right_height = cur->right->get_height();

	// 更新树高
	cur->height = max(left_height, right_height) + 1;
	// 更新平衡因子
	cur->b_factor = left_height - right_height;
}

/**
 * 递归插入新节点
 */
avl_node* avl_tree::insert_node(avl_node* cur, int new_key){
	// 边界条件
	if(cur == nullptr){
		avl_node* new_node = new avl_node(new_key); // 创建新节点
		return new_node;
	}
	
	// 递归插入
	if(new_key == cur->key){
		cerr << "要插入的值已经存在，插入失败！" << endl;
		return cur;
	}else if(new_key > cur->key){
		cur->right = insert_node(cur->right, new_key);
	}else if(new_key < cur->key){
		cur->left = insert_node(cur->left, new_key);
	}

	// 更新树高和平衡因子
	this->update_height_b_factor(cur);

	// 应该执行重平衡操作，对树节点进行旋转
	cur = this->rebanlance(cur);

	// 以该层节点为根节点的树已平衡
	// 平衡因子 在 [-1, 1]
	return cur;
}

/**
 * 插入新节点
 */
avl_node* avl_tree::insert(int new_key){
	this->root = insert_node(this->root, new_key); // 更新根节点 
	return this->root;
}

/**
 * 一次性插入一批数据
 */
void avl_tree::insert_batch(vector<int>& arr){
	for(int& x : arr){
		this->insert(x);
	}
	cout << "成功插入批数据" << endl;
}

/**
 * 针对当前节点为根节点的子树进行重平衡
 */
avl_node* avl_tree::rebanlance(avl_node* cur){
	if(cur->b_factor > 1){
		// 左边比较重
		if(cur->left->b_factor >= 0){
			// LL
			cur = this->turn_left_left(cur);
		}else{
			// LR
			cur = this->turn_left_right(cur);
		}
	}else if(cur->b_factor < -1){
		if(cur->right->b_factor < 0){
			// RR
			cur = this->turn_right_right(cur);
		}else{
			// RL
			cur = this->turn_right_left(cur);
		}
	}

	// 返回子树根节点
	return cur;
}

/**
 * LL 右旋
 */
avl_node* avl_tree::turn_left_left(avl_node* cur){
	avl_node* t1 = cur->left;
	avl_node* t2 = t1->right;

	t1->right = cur;
	cur->left = t2;

	// 更新 cur
	this->update_height_b_factor(cur);

	// 更新 t1
	this->update_height_b_factor(t1);

	cur = t1;
	return cur;
}

/**
 * RR 左旋
 */
avl_node* avl_tree::turn_right_right(avl_node* cur){
	avl_node* t1 = cur->right;
	avl_node* t2 = t1->left;

	t1->left = cur;
	cur->right = t2;

	// 更新 cur
	this->update_height_b_factor(cur);

	// 更新 t1
	this->update_height_b_factor(t1);

	cur = t1;
	return cur;
}

/**
 * LR 先左旋，再右旋
 */
avl_node* avl_tree::turn_left_right(avl_node* cur){
	// 先左旋
	avl_node* t1 = cur->left;
	cur->left = this->turn_right_right(t1);

	// 再右旋
	cur = this->turn_left_left(cur);
	return cur;
}

/**
 * RL 先右旋，再左旋
 */
avl_node* avl_tree::turn_right_left(avl_node* cur){
	// 先右旋
	avl_node* t1 = cur->right;
	cur->right = this->turn_left_left(t1);

	// 再左旋
	cur = this->turn_right_right(cur);
	return cur;
}

/**
 * 查找对应键的节点
 */
avl_node* avl_tree::search_node(avl_node* cur, int key){
	if(cur == nullptr){
		return nullptr;
	}
	if(key == cur->key){
		return cur;
	}

	if(key < cur->key){
		return search_node(cur->left, key);
	}else if(key > cur->key){
		return search_node(cur->right, key);
	}
} 

/**
 * 查找对应键的节点
 */
avl_node* avl_tree::search(int key){
	return this->search_node(this->root, key);
}

/**
 * 获得以当前节点为根节点的子树中，最小键值的节点
 */
avl_node* avl_tree::get_sub_tree_min(avl_node* cur){
	if(cur == nullptr){
		return nullptr;
	}

	while(cur->left != nullptr){
		cur = cur->left;
	}

	return cur;
}

/**
 * 递归删除节点
 */
avl_node* avl_tree::delete_node(avl_node* cur, int key){
	if(cur == nullptr){
		cerr << "未找到对应键值的节点！" << endl;
		return nullptr;
	}

	if(key < cur->key){
		cur->left = delete_node(cur->left, key);
	}else if(key > cur->key){
		cur->right = delete_node(cur->right, key);
	}else{
		// key == cur->key  找到要删除的节点
		if(cur->left == nullptr){
			// 包含两种情况：当前节点只有一个右子节点、当前是叶子节点
			avl_node* temp = cur->right;
			delete cur;
			return temp;
		}else if(cur->right == nullptr){
			// 只有一个左子节点
			avl_node* temp = cur->left;
			delete cur;
			return temp;
		}else{
			// 非叶子节点，需要用右子树中最小节点代替之
			avl_node* temp = get_sub_tree_min(cur->right);
			cur->key = temp->key;

			cur->right = delete_node(cur->right, cur->key);
		}

	}

	this->update_height_b_factor(cur);

	return this->rebanlance(cur);
}

/**
 * 删除对应的节点
 */
void avl_tree::del(int key){
	this->root = this->delete_node(this->root, key);
}

/**
 * 展示树的属性 
 */
void avl_tree::display_tree_attr(){
	if(this->get_root() == nullptr){
		cerr << "树的根节点尚为空，需要先插入！" << endl;
	} 
	
	cout << "--------展示AVL树的属性--------" << endl;	
	cout << "root key: " << this->get_root()->get_key() << endl;
	cout << "root height: " << this->get_root()->get_height() << endl;
	cout << "root b_factor: " << this->get_root()->get_b_factor() << endl;
	cout << "-------------------------------" << endl << endl;	
}

/**
 * 层序遍历，展示树的元素 
 */
void avl_tree::display_layers(){
	if(this->get_root() == nullptr){
		cerr << "树的根节点尚为空，需要先插入！" << endl;
	} 
	
	queue<avl_node*> que;
	que.push(this->root); // 压入根节点 
	
	cout << "---------层序遍历AVL树---------" << endl;
	
	while(!que.empty()){
		int size = que.size();
		
		for(int i=0; i < size; i++){
			avl_node* cur = que.front(); // 取得队首的节点
			que.pop();
			cout << cur->get_key() << " ";
			
			if(cur->left != nullptr){
				que.push(cur->left);
			} 
			if(cur->right != nullptr){
				que.push(cur->right);
			}	
		}
	
		cout << endl;	 
	}
	cout << "-------------------------------" << endl << endl;
}

int max(int a, int b){
	return a >= b ? a : b;
}