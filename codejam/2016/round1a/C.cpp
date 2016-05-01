#include <bits/stdc++.h>
using namespace std;

#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using vi=vector<int>;
using vvi=vector<vi>;

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
typedef vector<vector<Edge>> Graph;

void DFS(const Graph& g,int v,vi& vis,vi& order)
{
	if(vis[v]) return;
	vis[v]=1;
	for(auto e:g[v]) DFS(g,e.dst,vis,order);
	order.push_back(v);
}

vvi SCC(const Graph& g)
{
	int n=g.size();
	vi vis(n),order;
	rep(i,n) DFS(g,i,vis,order);
	Graph t(n);
	rep(i,n) for(auto e:g[i])
		t[e.dst].emplace_back(e.dst,e.src);
	fill(all(vis),0);
	vvi res;
	per(i,n) if(!vis[order[i]]){
		res.resize(res.size()+1);
		DFS(t,order[i],vis,res.back());
	}
	return res;
}

int rec(const Graph& g,int v)
{
	int res=0;
	for(auto e:g[v])
		res=max(res,rec(g,e.dst));
	return 1+res;
}

void solve()
{
	int n; cin>>n;
	Graph g(n);
	rep(i,n){
		int x; cin>>x; x--;
		g[x].emplace_back(x,i);
	}
	
	int sum=0,mx=0;
	for(vi scc:SCC(g)){
		if(scc.size()==2){
			int u=scc[0],v=scc[1];
			int x=0,y=0;
			for(auto e:g[u]) if(e.dst!=v) x=max(x,rec(g,e.dst));
			for(auto e:g[v]) if(e.dst!=u) y=max(y,rec(g,e.dst));
			sum+=2+x+y;
		}
		else
			mx=max<int>(mx,scc.size());
	}
	cout<<max(mx,sum)<<endl;
}

void solve_small()
{
	int n; cin>>n;
	vi fs(n);
	rep(i,n) cin>>fs[i],fs[i]--;
	for(int m=n;m>=2;m--){
		vi p(n); iota(all(p),0);
		do{
			bool ok=true;
			rep(i,m){
				int x=p[i],y=p[(i+1)%m],z=p[(i+m-1)%m];
				ok&=y==fs[x]||z==fs[x];
			}
			if(ok){
				cout<<m<<endl;
				rep(i,m) cout<<p[i]+1<<' '; cout<<endl;
				return;
			}
			reverse(m+all(p));
		}while(next_permutation(all(p)));
	}
}

int main()
{
	int T; cin>>T;
	for(int _case=1;_case<=T;_case++){
		cout<<"Case #"<<_case<<": ";
		//solve_small();
		solve();
	}
}
