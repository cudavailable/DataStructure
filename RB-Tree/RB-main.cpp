#include<iostream>
#include "rb_tree.h"

using namespace std;

// get/contains
void test1(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    
    string* s = t->get(3); 
    if(s == nullptr){
    	cout << "Null is found!" << endl;
    }else{
    	cout << "Content: " << *s << endl;
    }
    
	cout << (t->contains(3)? "Exist" : "Not exist")<< endl;
}

// delete root node
void test2(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    
    t->display();
	
	// delete root with 2 sons
	t->remove(3);
	t->display();
	
	// delete root with 1 son
	t->remove(8);
	t->display();
	
	// delete root without son
	t->remove(2);
	t->display();
}

// insert nodes
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
}

// 1.delete red node without son
// 2.test Case4
// 3.test Case3 
void test4(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    t->put(5, "you");
    t->put(12, "do");
    t->put(20, "us");
    t->put(30, "we");
    t->put(40, "guy");

	t->display();
    
    t->remove(40);
    t->display();
    
    // Case4: black sibling with 2 black sons
    t->remove(30);
    t->display();
    
    t->remove(12);
    t->display();
    
    // Case3: red sibling
    t->remove(20);
    t->display();
}

// delete black node without son
void test5(rb_tree<string>* t){
	t->put(8, "ok");
    t->put(3, "what");
    t->put(2, "are");
    t->put(5, "you");
    t->put(12, "do");
    t->put(20, "us");
    t->put(30, "we");
    t->put(4, "me");
	t->put(40, "no");
	
	t->display();
    
    // Case5 RR
//    t->remove(12); 
//    t->display();
    
    // Case5 RL
//    t->remove(2);
//    t->display();
}

int main(){
    rb_tree<string>* t = new rb_tree<string>();

    test4(t);
    
    delete t;

    return 0;
}
