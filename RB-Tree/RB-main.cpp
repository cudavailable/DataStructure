#include<iostream>
#include "rb_tree.h"

using namespace std;

int main(){
    rb_tree<string>* t = new rb_tree<string>();

    t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    
//    string* s = t->get(3); 
//    if(s == nullptr){
//    	cout << "Null is found!" << endl;
//    }else{
//    	cout << "Content: " << *s << endl;
//    }

	cout << "Empty: " << t->empty() << endl;
	cout << "Size: " << t->size() << endl;
    
//    t->display();
    
    delete t;

    return 0;
}
