#pragma once

#include<iostream>
#include<queue>

#include "rb_node.h"

template<typename Value>
class rb_tree{

private:
    rb_node<Value>* root; // root of red-black tree
    int count; // the number of nodes

    void destroy_node(rb_node<Value>* cur){
        if(cur == nullptr){
            return ;
        }

        destroy_node(cur->left);
        destroy_node(cur->right);
        delete cur;
        this->count--;
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
    
    bool empty(){
    	return this->count == 0;
    }
    
    int size(){
    	return this->count;
    }

};
