#include <bits/stdc++.h>
using namespace std;

#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,n) repi(i,0,n)

using vi=vector<int>;
using vvi=vector<vi>;

int res;

int dfs(const vvi& g,int k,int u)
{
	int d=0;
	for(int v:g[u]){
		int t=dfs(g,k,v);
		if(t==k-1)
			res+=u!=0;
		else
			d=max(d,1+t);
	}
	return d;
}

int main()
{
	for(int n,k;cin>>n>>k && n|k;){
		vi a(n);
		rep(i,n) cin>>a[i],a[i]--;

		res=0;
		if(a[0]!=0) a[0]=0,res++;

		vvi g(n);
		repi(i,1,n) g[a[i]].push_back(i);

		dfs(g,k,0);
		cout<<res<<endl;
	}
}
