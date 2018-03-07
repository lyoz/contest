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

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
using Graph=vector<vector<Edge>>;

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

void calc(const Graph& g,int u,vi& vis,vector<Edge>& es)
{
	for(auto e:g[u]){
		int v=e.dst;
		if(!vis[v]){
			vis[v]=1;
			calc(g,v,vis,es);
			es.emplace_back(u,v);
		}
	}
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		Graph g(n);
		rep(i,n){
			int v; cin>>v; v--;
			g[i].emplace_back(i,v);
		}

		vi vis(n);
		vector<Edge> es;
		for(auto vs:SCC(g)) for(int v:vs)
			if(!vis[v]){
				vis[v]=1;
				calc(g,v,vis,es);
			}
		for(auto e:es)
			cout<<e.src+1<<' '<<e.dst+1<<endl;
	}
}
