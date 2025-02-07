#pragma once

#include<iostream>
using namespace std;

enum Color{
    RED, BLACK
};

/**
 * Definition of red-black node
 */
template<typename Value> class rb_tree; // pre-definition
 
template<typename Value>
class rb_node{
    friend class rb_tree<Value>;
    
private:
    int key;
    Value value;
    rb_node* left;
    rb_node* right;
    rb_node* parent;
    Color color = Color::RED; // default: red

public:
    rb_node() {}

    rb_node(int key, Value value): key(key), value(value), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}

    /**
     * whether it's a left child of some node
     */
    bool is_left_child(){
        return parent != nullptr && parent->left == this;
    }

    /**
     * return its father's sibling (nullptr for null)
     */
    rb_node* uncle(){
        if(this->parent == nullptr || this->parent->parent == nullptr){
            return nullptr;
        }

        if(this->parent->is_left_child()){
            return this->parent->parent->right;
        }else{
            return this->parent->parent->left;
        }
        
    }

    /**
     * return its sibling (nullptr for null)
     */
    rb_node* sibling(){
        if(this->parent == nullptr){
            return nullptr;
        }

        if(this->is_left_child()){
            return this->parent->right;
        }else{
            return this->parent->left;
        }
    }

    /**
     * print a node
     */
    void print(){
        cout << this->key << "(" << (this->color==Color::BLACK? "b" : "r") << ")"; // "12(r)" "12(b)"
    }

};
