#pragma once

#include "rb_node.h"
using namespace std;

/**
 * whether it's a left child of some node
 */
bool rb_node::is_left_child(){
    return parent != nullptr && parent->left == this;
}

/**
 * return its father's sibling (nullptr for null)
 */
rb_node* rb_node::uncle(){
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
rb_node* rb_node::sibling(){
    if(this->parent == nullptr){
        return nullptr;
    }

    if(this->is_left_child()){
        return this->parent->right;
    }else{
        return this->parent->left;
    }
}