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

template<typename T,typename U>bool chmin(T& a,const U& b){return a>b?(a=b,1):0;}
template<typename T,typename U>bool chmax(T& a,const U& b){return a<b?(a=b,1):0;}

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

struct UnionFind{
	vi data;
	UnionFind(int n):data(n,-1){}
	int Find(int i){
		return data[i]<0?i:(data[i]=Find(data[i]));
	}
	bool Unite(int a,int b){
		a=Find(a),b=Find(b);
		if(a==b) return false;
		if(-data[a]<-data[b]) swap(a,b);
		data[a]+=data[b];
		data[b]=a;
		return true;
	}
	int Size(int i){
		return -data[Find(i)];
	}
};

struct Edge{
	int src,dst,weight;
	Edge(){}
	Edge(int s,int d,int w):src(s),dst(d),weight(w){}
};
using Graph=vector<vector<Edge>>;

struct LCA{
	int n,h;
	vi ds;
	vvi ps;
	vvi ws;
	LCA(const Graph& g,int root):n(g.size()),h(32-__builtin_clz(n)),ds(n),ps(h,vi(n,-1)),ws(h,vi(n)){
		DFS(g,-1,root,0,0);
		rep(i,ps.size()-1) rep(j,ps[i].size()){
			ws[i+1][j]=ws[i][j];
			if(ps[i][j]!=-1){
				ps[i+1][j]=ps[i][ps[i][j]];
				chmax(ws[i+1][j],ws[i][ps[i][j]]);
			}
		}
	}
	void DFS(const Graph& g,int p,int v,int w,int d){
		ds[v]=d;
		ps[0][v]=p;
		ws[0][v]=w;
		for(auto e:g[v]) if(e.dst!=p)
			DFS(g,e.src,e.dst,e.weight,d+1);
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
	int MaxWeight(int u,int v){
		if(ds[u]>ds[v]) swap(u,v);
		int res=0;
		rep(i,ps.size())
			if(ds[v]-ds[u]>>i&1){
				chmax(res,ws[i][v]);
				v=ps[i][v];
			}
		if(u==v) return res;
		per(i,ps.size()){
			if(ps[i][u]!=ps[i][v]){
				chmax(res,max(ws[i][u],ws[i][v]));
				u=ps[i][u],v=ps[i][v];
			}
		}
		return max({res,ws[0][u],ws[0][v]});
	}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vector<tuple<int,int,int>> es;
		rep(i,m){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			es.emplace_back(u,v,w);
		}

		vi is(m); iota(all(is),0);
		sort(all(is),[&](int i,int j){return get<2>(es[i])<get<2>(es[j]);});

		UnionFind uf(m);
		vi used(m);
		ll w_mst=0;
		for(int i:is){
			int u,v,w; tie(u,v,w)=es[i];
			if(uf.Unite(u,v)){
				used[i]=1;
				w_mst+=w;
			}
		}

		Graph mst(n);
		for(int i:is) if(used[i]){
			int u,v,w; tie(u,v,w)=es[i];
			mst[u].emplace_back(u,v,w);
			mst[v].emplace_back(v,u,w);
		}

		LCA lca(mst,0);

		vl res(m,-1);
		for(int i:is){
			if(used[i])
				res[i]=w_mst;
			else{
				int u,v,w; tie(u,v,w)=es[i];
				res[i]=w_mst-lca.MaxWeight(u,v)+w;
			}
		}
		rep(i,m) cout<<res[i]<<endl;
	}
}
