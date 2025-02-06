#pragma once

#include "rb_tree.h"
using namespace std;

bool rb_tree::is_red(rb_node* cur){
    return cur!=nullptr && cur->color==Color::RED;
}

bool rb_tree::is_black(rb_node* cur){
    return cur==nullptr || cur->color==Color::BLACK;
}