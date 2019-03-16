#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(int n;cin>>n&&n;){
		vector<int> a(n);
		for(int& x:a) cin>>x;
		map<int,int> f;
		for(int x:a) f[x]++;

		vector<int> edges;
		for(int i=0;i<2;i++){
			int edge=0;
			for(auto p:f)
				if(p.second>=2)
					edge=p.first;
			edges.push_back(edge);
			f[edge]-=2;
		}
		cout<<(long long)edges[0]*edges[1]<<endl;
	}
}
