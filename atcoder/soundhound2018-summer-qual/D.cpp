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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Edge{
	int src,dst;
	ll weight;
	Edge(int s,int d,ll w):src(s),dst(d),weight(w){}
};
using Graph=vector<vector<Edge>>;

template<typename T,typename Compare>
auto make_priority_queue(const Compare& comp)
{
	return priority_queue<T,vector<T>,Compare>(comp);
}

vl Dijkstra(const Graph& g,int s)
{
	int n=g.size();
	vl res(n,INF);
	auto pq=make_priority_queue<tuple<int,ll>>([](auto a,auto b){
		return get<1>(a)>get<1>(b);
	});
	pq.emplace(s,0);
	while(pq.size()){
		int u; ll w; tie(u,w)=pq.top(); pq.pop();
		if(res[u]<=w) continue;
		res[u]=w;
		for(auto e:g[u])
			pq.emplace(e.dst,w+e.weight);
	}
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m,s,t;cin>>n>>m>>s>>t&&n|m|s|t;){
		s--,t--;
		Graph gy(n),gs(n);
		rep(_,m){
			int u,v; cin>>u>>v; u--,v--;
			ll a,b; cin>>a>>b;
			gy[u].emplace_back(u,v,a);
			gy[v].emplace_back(v,u,a);
			gs[u].emplace_back(u,v,b);
			gs[v].emplace_back(v,u,b);
		}
		vl dys=Dijkstra(gy,s);
		vl dss=Dijkstra(gs,t);
		vl res(n);
		rep(i,n) res[i]=dys[i]+dss[i];
		per(i,n-1) chmin(res[i],res[i+1]);
		rep(i,n) cout<<ll(1e15)-res[i]<<endl;
	}
}
