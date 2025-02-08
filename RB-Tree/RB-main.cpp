#include<iostream>
#include "rb_tree.h"

using namespace std;

void test1(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    
    t->display();
	
	t->remove(8);
	t->display(); 
	
	t->remove(2);
	t->display();
	
	t->remove(3);
	t->display();
}

void test2(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    
    t->display();
	
	t->remove(8);
	t->display(); 
	
	t->remove(3);
	t->display();
}

void test3(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    t->put(5, "you");
    t->put(12, "do");
    t->put(20, "us");
    t->put(30, "we");
    t->put(40, "guy");
    
    t->display();
	
//	t->remove(8);
//	t->display(); 
//	
//	t->remove(3);
//	t->display();
}

int main(){
    rb_tree<string>* t = new rb_tree<string>();

    test3(t);
	
    
//    string* s = t->get(3); 
//    if(s == nullptr){
//    	cout << "Null is found!" << endl;
//    }else{
//    	cout << "Content: " << *s << endl;
//    }

//	cout << "Empty: " << t->empty() << endl;
//	cout << "Size: " << t->size() << endl;
    
//    t->display();
    
    delete t;

    return 0;
}
