#include <bits/stdc++.h>
using namespace std;

#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vs=vector<string>;

template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	return os<<'('<<p.first<<','<<p.second<<')';
}

template<typename Tuple>
void print_tuple(ostream&,const Tuple&){}
template<typename Car,typename... Cdr,typename Tuple>
void print_tuple(ostream& os,const Tuple& t){
	print_tuple<Cdr...>(os,t);
	os<<(sizeof...(Cdr)?",":"")<<get<sizeof...(Cdr)>(t);
}
template<typename... Args>
ostream& operator<<(ostream& os,const tuple<Args...>& t){
	print_tuple<Args...>(os<<'(',t);
	return os<<')';
}

template<typename Ch,typename Tr,typename C>
basic_ostream<Ch,Tr>& operator<<(basic_ostream<Ch,Tr>& os,const C& c){
	os<<'[';
	for(auto i=begin(c);i!=end(c);++i)
		os<<(i==begin(c)?"":" ")<<*i;
	return os<<']';
}

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
typedef vector<vector<Edge>> Graph;

struct LCA{
	vi ds;
	vvi ps;
	LCA(const Graph& g,int root):ds(g.size()),ps(32-__builtin_clz(g.size()),vi(g.size(),-1)){
		DFS(g,-1,root,0);
		rep(i,ps.size()-1) rep(j,ps[i].size())
			ps[i+1][j]=ps[i][j]==-1?-1:ps[i][ps[i][j]];
	}
	void DFS(const Graph& g,int p,int v,int d){
		ds[v]=d;
		ps[0][v]=p;
		for(auto e:g[v]) if(e.dst!=p)
			DFS(g,e.src,e.dst,d+1);
	}
	int Find(int u,int v){
		if(ds[u]>ds[v]) swap(u,v);
		rep(i,ps.size())
			if(ds[v]-ds[u]>>i&1)
				v=ps[i][v];
		if(u==v) return u;
		per(i,ps.size())
			if(ps[i][u]!=ps[i][v])
				u=ps[i][u],v=ps[i][v];
		return ps[0][u];
	}
};

int main()
{
	for(int n,q;cin>>n>>q&&n|q;){
		Graph g(n);
		rep(i,n-1){
			int v; cin>>v; v--;
			g[i+1].emplace_back(i+1,v);
			g[v].emplace_back(v,i+1);
		}

		LCA lca(g,0);

		rep(_,q){
			vi vs(3);
			rep(i,3) cin>>vs[i],vs[i]--;
			sort(all(vs));
			int res=0;
			do{
				int s=vs[0],t=vs[1],f=vs[2];
				int u=lca.Find(s,t);
				int v=lca.Find(u,f);
				if(v==u){  // s,t,fはuの子
					int a=lca.Find(s,f);
					int b=lca.Find(t,f);
					if(a==u){
						int x=abs(lca.ds[b]-lca.ds[f])+1;
						res=max(res,x);
					}
					else{
						int x=abs(lca.ds[a]-lca.ds[f])+1;
						res=max(res,x);
					}
				}
				else{
					int x=abs(lca.ds[u]-lca.ds[v])+abs(lca.ds[f]-lca.ds[v])+1;
					res=max(res,x);
				}
			}while(next_permutation(all(vs)));
			cout<<res<<endl;
		}
	}
}
