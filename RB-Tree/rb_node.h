#pragma once

enum Color{
    RED, BLACK
};

/**
 * Definition of red-black node
 */
class rb_node{
    friend class rb_tree;
    
private:
    int key;
    rb_node* left;
    rb_node* right;
    rb_node* parent;
    Color color = RED; // default: red

public:
    bool is_left_child(); // whether it's a left child of some node
    rb_node* uncle(); // return its father's sibling (nullptr for null)
    rb_node* sibling(); // return its sibling (nullptr for null)

};
