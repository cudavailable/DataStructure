#pragma once

enum Color{
    RED, BLACK
};

/**
 * Definition of red-black node
 */
template<typename Value>
class rb_node{
    friend class rb_tree;
    
private:
    int key;
    Value value;
    rb_node* left;
    rb_node* right;
    rb_node* parent;
    Color color = RED; // default: red

public:
    rb_node() {}

    rb_node(int key, Value Value): key(key), value(value), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}

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

};
