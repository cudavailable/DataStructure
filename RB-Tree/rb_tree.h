#pragma once

#include<iostream>
#include<queue>

#include "rb_node.h"

template<typename Value>
class rb_tree{

private:
    rb_node<Value>* root; // root of red-black tree
    int count; // the number of nodes

    /**
     * destroy all the nodes in post-order
     */
    void destroy_node(rb_node<Value>* cur){
        if(cur == nullptr){
            return ;
        }

        destroy_node(cur->left);
        destroy_node(cur->right);
        delete cur;
        this->count--;
    }

    /**
     * LL
     */
    void right_rotate(rb_node<Value>* cur){
        rb_node<Value>* t1 = cur->left;
        rb_node<Value>* t2 = t1->right;
        rb_node<Value>* parent = cur->parent;

        if(t2 != nullptr){
            t2->parent = cur;
        }

        cur->left = t2;
        cur->parent = t1;
        t1->right = cur;
        t1->parent = parent;

        if(parent == nullptr){
            this->root = t1;
        }else if(parent->left == cur){
            parent->left = t1;
        }else{
            parent->right = t1;
        }

    }

    /**
     * RR
     */
    void left_rotate(rb_node<Value>* cur){
        rb_node<Value>* t1 = cur->right;
        rb_node<Value>* t2 = t1->left;
        rb_node<Value>* parent = cur->parent;

        if(t2 != nullptr){
            t2->parent = cur;
        }

        cur->right = t2;
        cur->parent = t1;
        t1->left = cur;
        t1->parent = parent;

        if(parent == nullptr){
            this->root = t1;
        }else if(parent->left == cur){
            parent->left = t1;
        }else{
            parent->right = t1;
        }

    }

    /**
     * fix the problem of red-next-to-red
     */
    void fix_red_red(rb_node<Value>* cur){
        // Case1: Root -> just change color
        if(cur == this->root){
            cur->color = Color::BLACK;
            return ;
        }

        // Case2: Parent is black -> just return
        if(this->is_black(cur->parent)){
            return ;
        }

        // Case3: uncle is red
        rb_node<Value>* parent = cur->parent;
        rb_node<Value>* uncle = cur->uncle();
        rb_node<Value>* grandparent = parent->parent;
        if(this->is_red(uncle)){
            parent->color = Color::BLACK;
            uncle->color = Color::BLACK;
            grandparent->color = Color::RED;

            this->fix_red_red(grandparent); // use recursion
            return ;
        }

        // Case4: uncle is black
        if(cur->is_left_child() && parent->is_left_child()){
            // LL
            parent->color = Color::BLACK;
            grandparent->color = Color::RED;
            this->right_rotate(grandparent);
        }else if(!cur->is_left_child() && parent->is_left_child()){
            // LR
            this->left_rotate(parent);
            cur->color = Color::BLACK;
            grandparent->color = Color::RED;
            this->right_rotate(grandparent);
        }else if(!cur->is_left_child() && !parent->is_left_child()){
            // RR
            parent->color = Color::BLACK;
            grandparent->color = Color::RED;
            this->left_rotate(grandparent);
        }else{
            // RL
            this->right_rotate(parent);
            cur->color = Color::BLACK;
            grandparent->color = Color::RED;
            this->left_rotate(grandparent);
        }
        
    }

    /**
     * return remaining parts given deleted node
     */
    rb_node<Value>* find_replaced(rb_node<Value>* deleted){
        if(deleted->left == nullptr && delete->right == nullptr){
            return nullptr;
        }

        if(delete->left == nullptr){
            return deleted->right;
        }

        if(delete->right == nullptr){
            return deleted->left;
        }

        // non-leaf node
        rb_node<Value>* s = deleted->right;
        while (s->left != nullptr){
            s = s->left;
        }

        return s;
    }

    /**
     * fix the problem of lack-of-black
     */
    void fix_double_black(rb_node<Value>* x){
        if(x == this->root){
            return ;
        }

        rb_node<Value>* parent = x->parent;
        rb_node<Value>* sibling = x->sibling();
        
        // Case3: red sibling
        if(this->is_red(sibling)){ 
            if(x->is_left_child()){
                this->left_rotate(parent);
            }else{
                this->right_rotate(parent);
            }

            parent->color = Color::RED;
            sibling->color = Color::BLACK;

            this->fix_double_black(x);
            return ;
        }

        if(sibling != nullptr){
            // Case4: black sibling with two black sons
            if(this->is_black(sibling->left) && this->is_black(sibling->right)){
                sibling->color = Color::RED;
                if(this->is_red(parent)){
                    parent->color = Color::BLACK;
                }else{
                    this->fix_double_black(parent);
                }

            }
            // Case5: black sibling with red son
            else{
                // LL
                if(sibling->is_left_child() && this->is_red(sibling->left)){
                    this->right_rotate(parent);
                    sibling->left->color = Color::BLACK;
                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                }

                // LR
                else if(sibling->is_left_child() && this->is_red(sibling->right)){
                    sibling->right->color = parent->color;
                    this->left_rotate(sibling);
                    this->right_rotate(parent);
                    parent->color = Color::BLACK;
                }

                // RL
                else if(!sibling->is_left_child() && this->is_red(sibling->left)){
                    sibling->left->color = parent->color;
                    this->right_rotate(sibling);
                    this->left_rotate(parent);
                    parent->color = Color::BLACK;
                }

                // RR
                else if(!sibling->is_left_child() && this->is_red(sibling->right)){
                    this->left_rotate(parent);
                    sibling->right->color = Color::BLACK;
                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                }
            }
        }else{
            this->fix_double_black(parent);
        }
        
    }

    /**
     * remove a node which actually exists given a pointer 
     */
    void remove_node(rb_node<Value>* deleted){
        rb_node<Value>* replaced = this->find_replaced(deleted);
        rb_node<Value>* parent = deleted->parent;

        if(replaced == nullptr){ // deleted node without children

            if(deleted == this->root){ // deleted node is root 
                this->root = nullptr;
                delete deleted;
            }else{ // is not root

                if(this->is_black(deleted)){ // black node
                    this->fix_double_black(deleted);
                }else{ // red node
                    // don't need to handle it
                }

                if(deleted->is_left_child()){
                    parent->left = nullptr;
                }else{
                    parent->right = nullptr;
                }

                delete deleted;
            }

            return ;
        }

        if(deleted->left == nullptr || deleted->right == nullptr){ // with only one chlid

            if(deleted == this->root){ // deleted node is root 
                root->key = replaced->key;
                root->value = replaced->value;
                root->left = nullptr;
                root->right = nullptr;

                delete replaced;
            }else{ // is not root
                if(deleted->is_left_child()){
                    parent->left = replaced;
                }else{
                    parent->right = replaced;
                }

                replaced->parent = parent;

                // deleted node could only be a black node
                if(this->is_black(deleted) && this->is_black(replaced)){
                    this->fix_double_black(replaced);
                }else{ 
                    replaced->color = Color::BLACK; 
                }

                delete deleted;
            }

            return ;
        }

        // with two children
        int t = deleted->key;
        deleted->key = replaced->key;
        replaced->key = t;

        Value v = deleted->value;
        deleted->value = replaced->value;
        replaced->value = v;

        remove_node(replaced);
    }

public:
    rb_tree(): root(nullptr), count(0) {}

    ~rb_tree() {this->destroy_node(this->root); cout << "Calling the destructor" << endl;}

    /**
     * whether the node is red
     */
    bool is_red(rb_node<Value>* cur){
        return cur!=nullptr && cur->color==Color::RED;
    }

    /**
     * whether the node is black
     */
    bool is_black(rb_node<Value>* cur){
        return cur==nullptr || cur->color==Color::BLACK;
    }

    /**
     * INSERT/UPDATE a pair of <key, value>
     */
    void put(int key, Value value){
        rb_node<Value>* p = this->root;
        rb_node<Value>* parent = nullptr;

        while(p != nullptr){
            parent = p;
            
            if(key < p->key){
                p = p->left;
            }else if(key > p->key){
                p = p->right;
            }else{
                // UPDATE
                p->value = value;
                return ;
            }
        }

        // INSERT
        rb_node<Value>* inserted = new rb_node<Value>(key, value);
        this->count++;
        
        if(parent == nullptr){
            // empty tree
            this->root = inserted;
        }else if (key < parent->key){
            parent->left = inserted;
            inserted->parent = parent;
        }else{
            parent->right = inserted;
            inserted->parent = parent;
        }


        // fix red-next-to-red after insertion
        this->fix_red_red(inserted);
    }
    
    /**
     * print all nodes in order of layers
     */
    void display(){
        if(this->root == nullptr){
            cout << "The root of the tree is empty, please insert a node!" << endl;
            return ;
        }

        cout << "-----------Print Info-----------" << endl;

        queue<rb_node<Value>*> que;
        que.push(this->root);

        while(!que.empty()){
            int size = que.size();

            for(int i=0; i < size; i++){
                rb_node<Value>* cur = que.front();
                que.pop();

                cur->print(); // >>12(r)
                cout << " ";

                if(cur->left != nullptr){
                    que.push(cur->left);
                }
                if(cur->right != nullptr){
                    que.push(cur->right);
                }
            }
            cout << endl;
        }

        cout << "Total count of nodes: " << this->count << endl;
        cout << "--------------------------------" << endl;
    }

    /**
     * get value's pointer by provided key (nullptr for not found)
     */
    Value* get(int key){
        if(this->root == nullptr){
            cout << "The root of the tree is empty, please insert a node!" << endl;
            return nullptr;
        }

        rb_node<Value>* p = this->root;
        while(p != nullptr){
            if(key < p->key){
                p = p->left;
            }else if(key > p->key){
                p = p->right;
            }else{
                cout << "key(" << key << ") is found, value("<< p->value << ")" << endl;
                return (Value*)(&p->value);
            }
        }

        cout << "key(" << key << ") is not found!" << endl;
        return nullptr;
    }
    
    /**
     * whether contains a specific key (false for not found)
     */
    bool contains(int key){
        if(this->root == nullptr){
            cout << "The root of the tree is empty, please insert a node!" << endl;
            return false;
        }

        rb_node<Value>* p = this->root;
        while(p != nullptr){
            if(key < p->key){
                p = p->left;
            }else if(key > p->key){
                p = p->right;
            }else{
                cout << "key(" << key << ") is found" << endl;
                return true;
            }
        }

        cout << "key(" << key << ") is not found!" << endl;
        return false;
    }
    
    /**
     * whether rb-tree is empty
     */
    bool empty(){
    	return this->count == 0;
    }
    
    /**
     * return the count of nodes
     */
    int size(){
    	return this->count;
    }

    /**
     * return the node given specific key (nullptr for not found)
     */
    rb_node<Value>* find(int key){
        rb_node<Value>* p = this->root;
        while(p != nullptr){
            if(key < p->key){
                p = p->left;
            }else if(key > p->key){
                p = p->right;
            }else{
                return p;
            }
        }

        return nullptr;
    }

    /**
     * remove a node given a specific key
     */
    void remove(int key){
        // find the node
        rb_node<Value>* deleted = this->find(key);

        if(deleted == nullptr){
            // No such node
            return nullptr;
        }

        // remove a node literally
        remove_node(deleted);
    }

};
