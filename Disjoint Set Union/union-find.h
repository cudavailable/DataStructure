#include<iostream>
#include<cstdlib>
#include<vector>
using std::vector;

class UnionFind{
private:
	vector<int> pre;
	vector<int> rank;

public:
	UnionFind(int n){
		pre.resize(n);
		rank.resize(n, 1);
		
		for(int i=1; i <= n; i++){
			pre[i] = i;
		}
	}
	
	int find(int x){
		if(pre[x] == x)
			return x;
			
		return pre[x]=find(pre[x]);
	}
	
	bool isConnect(int x, int y){
		return find(x)==find(y);
	}
	
	bool join(int x, int y){
		if(isConnect(x, y))
			return false;
		
		x = find(x);
		y = find(y);
		
		if(rank[x] > rank[y]){
			pre[y] = x;
		}else{
			if(rank[x]==rank[y]) rank[y]++;
			pre[x] = y;
		}
		
		return true;
	}
}; 
