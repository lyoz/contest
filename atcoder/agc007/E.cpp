#include <bits/stdc++.h>
using namespace std;

#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,n) repi(i,0,n)
#define all(c) begin(c),end(c)
#define mt make_tuple

constexpr int INF=1e9;

struct Edge{
	int u,v,w;
	Edge(){}
	Edge(int u,int v,int w):u(u),v(v),w(w){}
};
using Tree=vector<vector<Edge>>;

vector<tuple<int,int>> dfs(const Tree& t,int x,int p)
{
	if(t[p].empty()) return {mt(0,0)};
	auto e0=t[p][0],e1=t[p][1];
	auto s0=dfs(t,x,e0.v),s1=dfs(t,x,e1.v);

	vector<tuple<int,int>> res;
	rep(_,2){
		for(int i=0,j=0;i<s0.size();i++){
			int a,b; tie(a,b)=s0[i];
			for(;j<s1.size();j++){
				int c,d; tie(c,d)=s1[j];
				if(e0.w+b+c+e1.w>x) break;
			}
			if(j>0){
				int d=get<1>(s1[j-1]);
				res.emplace_back(e0.w+a,d+e1.w);
			}
		}
		swap(e0,e1); swap(s0,s1);
	}

	sort(all(res),[](auto a,auto b){return a<b;});
	res.erase(unique(all(res),[](auto a,auto b){return get<1>(a)<=get<1>(b);}),end(res));
	return res;
}

bool ok(const Tree& t,int x)
{
	return dfs(t,x,0).size();
}

int main()
{
	for(int n;cin>>n&&n;){
		Tree t(n);
		rep(i,n-1){
			int u,v=i+1,w; cin>>u>>w; u--;
			t[u].emplace_back(u,v,w);
		}
		int lo=-1,hi=INF;
		while(hi-lo>1){
			int mi=(lo+hi)/2;
			(ok(t,mi)?hi:lo)=mi;
		}
		cout<<hi<<endl;
	}
}
