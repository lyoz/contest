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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Edge{
	int src,dst;
	ll weight;
	Edge(){}
	Edge(int s,int d,ll w):src(s),dst(d),weight(w){}
};
using Graph=vector<vector<Edge>>;

bool BellmanFord(const Graph& g,int src,vl& dist)
{
	int n=g.size();
	dist[src]=0;
	rep(k,n-1)
		rep(u,n) for(auto e:g[u])
			if(dist[e.dst]>dist[e.src]+e.weight)
				dist[e.dst]=dist[e.src]+e.weight;
	rep(k,n)
		rep(u,n) for(auto e:g[u])
			if(dist[e.dst]>dist[e.src]+e.weight){
				dist[e.dst]=dist[e.src]+e.weight;
				if(e.dst==n-1)
					return false;
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
		rep(i,m){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			g[u].emplace_back(u,v,-w);
		}

		vl cost(n,INF);
		if(!BellmanFord(g,0,cost))
			cout<<"inf"<<endl;
		else
			cout<<-cost[n-1]<<endl;
	}
}
