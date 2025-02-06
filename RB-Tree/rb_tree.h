#pragma once

#include "rb_node.h"

template<typename Value>
class rb_tree{

private:
    rb_node<Value>* root; // root of red-black tree
    int count; // the number of nodes

public:
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
        
    }

    /**
     * RR
     */
    void left_rotate(rb_node<Value>* cur){

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

};