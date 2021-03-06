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
using Graph=vector<vector<Edge>>;
ostream& operator<<(ostream& os,const Edge& e){return os<<'('<<e.src<<"->"<<e.dst<<')';}

int dfs(const Graph& g,int p,int u,int d)
{
	if(d==0) return 1;
	int res=1;
	for(auto e:g[u]) if(e.dst!=p)
		res+=dfs(g,u,e.dst,d-1);
	return res;
}

int main()
{
	for(int n,k;cin>>n>>k && n|k;){
		Graph g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].emplace_back(u,v);
			g[v].emplace_back(v,u);
		}
		
		int res=INF;
		if(k&1){ // 辺の両端の頂点を中心として深さ(k-1)/2まで残す
			for(auto es:g) for(auto e:es) if(e.src<e.dst){
				int cnt=dfs(g,e.dst,e.src,(k-1)/2)+dfs(g,e.src,e.dst,(k-1)/2);
				res=min(res,n-cnt);
			}
		}
		else{ // ある頂点を中心として深さk/2まで残す
			rep(c,n){
				int cnt=dfs(g,-1,c,k/2);
				res=min(res,n-cnt);
			}
		}
		cout<<res<<endl;
	}
}
