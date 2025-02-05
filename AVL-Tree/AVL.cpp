#include<iostream>
using namespace std;

/**
	AVL��CPP����ʵ��	
*/

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
};

/**
 * �ݹ�������������Ľڵ�
 */
void avl_tree::destroy_tree(avl_node* cur){
	if(cur == nullptr){
		return ;
	}

	// ������������
	this->destroy_tree(cur->left);
	this->destroy_tree(cur->right);

	// ���ٵ�ǰ�ڵ�
	delete cur;
}

/**
 * ��������
 */
avl_tree::~avl_tree(){
	this->destroy_tree(this->root);
	std::cout << "����������������" << endl;
}

/**
 * �������ߺ�ƽ������
 */
void avl_tree::update_height_b_factor(avl_node* cur){
	if(cur == nullptr){
		cerr << "����ڵ�Ϊ�գ��޷��������ߣ�" << endl;
		return;
	}

	int left_height = cur->left->get_height();
	int right_height = cur->right->get_height();

	// ��������
	cur->height = max(left_height, right_height) + 1;
	// ����ƽ������
	cur->b_factor = left_height - right_height;
}

/**
 * �ݹ�����½ڵ�
 */
avl_node* avl_tree::insert_node(avl_node* cur, int new_key){
	// �߽�����
	if(cur == nullptr){
		avl_node* new_node = new avl_node(new_key); // �����½ڵ�
		return new_node;
	}
	
	// �ݹ����
	if(new_key == cur->key){
		cerr << "Ҫ�����ֵ�Ѿ����ڣ�����ʧ�ܣ�" << endl;
		return cur;
	}else if(new_key > cur->key){
		cur->right = insert_node(cur->right, new_key);
	}else if(new_key < cur->key){
		cur->left = insert_node(cur->left, new_key);
	}

	// �������ߺ�ƽ������
	this->update_height_b_factor(cur);

	// Ӧ��ִ����ƽ������������ڵ������ת
	cur = this->rebanlance(cur);

	// �Ըò�ڵ�Ϊ���ڵ������ƽ��
	// ƽ������ �� [-1, 1]
	return cur;
}

/**
 * �����½ڵ�
 */
avl_node* avl_tree::insert(int new_key){
	this->root = insert_node(this->root, new_key); // ���¸��ڵ� 
	return this->root;
}

/**
 * ��Ե�ǰ�ڵ�Ϊ���ڵ������������ƽ��
 */
avl_node* avl_tree::rebanlance(avl_node* cur){
	if(cur->b_factor > 1){
		// ��߱Ƚ���
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

	// �����������ڵ�
	return cur;
}

/**
 * LL ����
 */
avl_node* avl_tree::turn_left_left(avl_node* cur){
	avl_node* t1 = cur->left;
	avl_node* t2 = t1->right;

	t1->right = cur;
	cur->left = t2;

	// ���� cur
	this->update_height_b_factor(cur);

	// ���� t1
	this->update_height_b_factor(t1);

	cur = t1;
	return cur;
}

/**
 * RR ����
 */
avl_node* avl_tree::turn_right_right(avl_node* cur){
	avl_node* t1 = cur->right;
	avl_node* t2 = t1->left;

	t1->left = cur;
	cur->right = t2;

	// ���� cur
	this->update_height_b_factor(cur);

	// ���� t1
	this->update_height_b_factor(t1);

	cur = t1;
	return cur;
}

/**
 * LR ��������������
 */
avl_node* avl_tree::turn_left_right(avl_node* cur){
	// ������
	avl_node* t1 = cur->left;
	cur->left = this->turn_right_right(t1);

	// ������
	cur = this->turn_left_left(cur);
	return cur;
}

/**
 * RL ��������������
 */
avl_node* avl_tree::turn_right_left(avl_node* cur){
	// ������
	avl_node* t1 = cur->right;
	cur->right = this->turn_left_left(t1);

	// ������
	cur = this->turn_right_right(cur);
	return cur;
}

/**
 * ���Ҷ�Ӧ���Ľڵ�
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
 * ���Ҷ�Ӧ���Ľڵ�
 */
avl_node* avl_tree::search(int key){
	return this->search_node(this->root, key);
}

/**
 * ����Ե�ǰ�ڵ�Ϊ���ڵ�������У���С��ֵ�Ľڵ�
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
 * �ݹ�ɾ���ڵ�
 */
avl_node* avl_tree::delete_node(avl_node* cur, int key){
	if(cur == nullptr){
		cout << "δ�ҵ���Ӧ��ֵ�Ľڵ㣡" << endl;
		return nullptr;
	}

	if(key < cur->key){
		cur->left = delete_node(cur->left, key);
	}else if(key > cur->key){
		cur->right = delete_node(cur->right, key);
	}else{
		// key == cur->key  �ҵ�Ҫɾ���Ľڵ�
		if(cur->left == nullptr){
			// ���������������ǰ�ڵ�ֻ��һ�����ӽڵ㡢��ǰ��Ҷ�ӽڵ�
			avl_node* temp = cur->right;
			delete cur;
			return temp;
		}else if(cur->right == nullptr){
			// ֻ��һ�����ӽڵ�
			avl_node* temp = cur->left;
			delete cur;
			return temp;
		}else{
			// ��Ҷ�ӽڵ㣬��Ҫ������������С�ڵ����֮
			avl_node* temp = get_sub_tree_min(cur->right);
			cur->key = temp->key;
			delete temp;

			// update_height_b_factor(cur);
			// return cur;
			cur->right = delete_node(cur->right, cur->key);
		}

	}

	this->update_height_b_factor(cur);

	return this->rebanlance(cur);

}

/**
 * ɾ����Ӧ�Ľڵ�
 */
void avl_tree::del(int key){
	this->root = this->delete_node(this->root, key);
}

int max(int a, int b){
	return a >= b ? a : b;
}

int main(){
	// avl_node* n1 = new avl_node(12);
	// std::cout << n1->get_key() << " " << n1->get_height() << endl;
	// avl_node n1 = nullptr;
	// n1->getheight()
	// cout<< "n1's height: " << n1->get_height() << endl;
	// cout<< "n1's left subtree's height: "<< n1->get_left()->get_height() << endl;

	avl_tree* t = new avl_tree(); // root = nullptr
	t->insert(12);
	t->insert(13);
//	t->insert(14);
	cout << t->get_root()->get_key() << endl;
	cout << t->get_root()->get_height() << endl;
	cout << t->get_root()->get_b_factor() << endl;
	t->insert(14);

	cout << "---------------" << endl;	
	cout << t->get_root()->get_key() << endl;
	cout << t->get_root()->get_height() << endl;
	cout << t->get_root()->get_b_factor() << endl;

	delete t;
	return 0;
}
