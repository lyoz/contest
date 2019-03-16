#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
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

void print_vars(ostream&){}
template<typename Car,typename... Cdr>
void print_vars(ostream& os,const Car& car,const Cdr&... cdr){
	print_vars(os<<car<<(sizeof...(cdr)?",":""),cdr...);
}

template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	return os<<'('<<p.first<<','<<p.second<<')';
}

template<int I,typename Tuple>
void print_tuple(ostream&,const Tuple&){}
template<int I,typename Car,typename... Cdr,typename Tuple>
void print_tuple(ostream& os,const Tuple& t){
	os<<get<I>(t)<<(sizeof...(Cdr)?",":"");
	print_tuple<I+1,Cdr...>(os,t);
}
template<typename... Args>
ostream& operator<<(ostream& os,const tuple<Args...>& t){
	print_tuple<0,Args...>(os<<'(',t);
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
	ll weight;
	Edge(){}
	Edge(int s,int d,ll w):src(s),dst(d),weight(w){}
};
ostream& operator<<(ostream& os,const Edge& e){
	return os<<'('<<e.src<<','<<e.dst<<','<<e.weight<<')';
}
using Graph=vector<vector<Edge>>;

void dfs(const Graph& g,int v,vi& vis,vl& hs,vvi& used)
{
	rep(i,g[v].size()){
		auto e=g[v][i];
		if(vis[e.dst]) continue;
		vis[e.dst]=1;
		used[v][i]=1;
		hs[e.dst]=hs[v]+e.weight;
		dfs(g,e.dst,vis,hs,used);
	}
}

void dfs2(const Graph& g,const vvi& can_use,int v,vi& vis,vl& hs)
{
	rep(i,g[v].size()) if(can_use[v][i]){
		auto e=g[v][i];
		if(vis[e.dst]) continue;
		vis[e.dst]=1;
		hs[e.dst]=hs[v]+e.weight;
		dfs2(g,can_use,e.dst,vis,hs);
	}
}

bool ok(const Graph& g,const vvi& rev,vvi& cand)
{
	int n=g.size();
	vvi can_use(n);
	rep(i,n) can_use[i].resize(g[i].size(),1);

	rep(i,n) rep(j,g[i].size()) if(cand[i][j]){
		int v=g[i][j].dst;
		vi vis(n); vis[v]=1;
		vl hs(n);
		can_use[i][j]=can_use[v][rev[i][j]]=0;
		dfs2(g,can_use,v,vis,hs);

		bool zero_cycle=true;
		rep(k,n) rep(l,g[k].size()) if(can_use[k][l]){
			auto e=g[k][l];
			zero_cycle&=hs[e.src]+e.weight-hs[e.dst]==0;
		}
		if(zero_cycle) return true;

		can_use[i][j]=can_use[v][rev[i][j]]=1;
		cand[i][j]=cand[v][rev[i][j]]=0;
	}
	return false;
}

bool solve(const Graph& g,const vvi& rev)
{
	int n=g.size();
	vi vis(n); vis[0]=1;
	vl hs(n);  // 頂点0からの距離
	vvi used(n);  // DFS treeの構成辺として使ったかどうか
	rep(i,n) used[i].resize(g[i].size());
	dfs(g,0,vis,hs,used);

	rep(i,n) rep(j,g[i].size()){
		auto e=g[i][j];
		if(hs[e.src]+e.weight-hs[e.dst]){
			vvi cand=used;
			cand[i][j]=cand[e.dst][rev[i][j]]=1;
			return ok(g,rev,cand);
		}
	}
	return true;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		Graph g(n);
		vvi rev(n);
		rep(i,m){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			g[u].emplace_back(u,v,w);
			int usize=g[u].size();
			g[v].emplace_back(v,u,-w);
			int vsize=g[v].size();
			rev[u].push_back(vsize-1);
			rev[v].push_back(usize-1);
		}
		cout<<(solve(g,rev)?"Yes":"No")<<endl;
	}
}
