#pragma once

#include "rb_node.h"

template<typename Value>
class rb_tree{

private:
    rb_node* root; // root of red-black tree
    int count;

public:
    bool rb_tree::is_red(rb_node* cur){
        return cur!=nullptr && cur->color==Color::RED;
    }

    bool rb_tree::is_black(rb_node* cur){
        return cur==nullptr || cur->color==Color::BLACK;
    }
};