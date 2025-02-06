#pragma once

#include "rb_node.h"
#include "rb_node.cpp"

class rb_tree{

private:
    rb_node* root; // root of red-black tree

public:
    bool is_red(rb_node* node); // whether the node is red
    bool is_black(rb_node* node); // whether the node is black 
};