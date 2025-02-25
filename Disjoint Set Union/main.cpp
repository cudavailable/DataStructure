#include "union-find.h"

using namespace std;

int main(){
	UnionFind* uf = new UnionFind(6); // initialize for 6 nodes
	uf->join(2,3);
	cout << uf->isConnect(2,3) << endl;
	cout << uf->isConnect(2,4) << endl;
	uf->join(2,4);
	cout << uf->isConnect(2,4) << endl;
	return 0;
}
