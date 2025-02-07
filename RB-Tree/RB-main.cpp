#include<iostream>
#include "rb_tree.h"

using namespace std;

int main(){
    rb_tree<string>* t = new rb_tree<string>();

    t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    
    t->display();
    
    delete t;

    return 0;
}
