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
	Edge(){}
	Edge(int s,int d,ll w):src(s),dst(d),weight(w){}
};
using Graph=vector<vector<Edge>>;
bool operator<(const Edge& a,const Edge& b){return a.weight<b.weight;}
bool operator>(const Edge& a,const Edge& b){return a.weight>b.weight;}
ostream& operator<<(ostream& os,const Edge& e){return os<<mt(e.src,e.dst,e.weight);}

void Dijkstra(const Graph& g,int src,vl& dist)
{
	priority_queue<Edge,vector<Edge>,greater<Edge>> pq;
	pq.emplace(-1,src,0);
	while(pq.size()){
		Edge cur=pq.top(); pq.pop();
		if(dist[cur.dst]!=INF) continue;
		dist[cur.dst]=cur.weight;
		for(Edge e:g[cur.dst])
			pq.emplace(e.src,e.dst,cur.weight+e.weight);
	}
}

vl count(const Graph& g,int src,vl& cnt)
{
	int n=g.size();
	vi deg(n);
	rep(i,n) for(auto e:g[i]) deg[e.dst]++;
	cnt[src]=1;
	queue<int> q; q.push(src);
	while(q.size()){
		int u=q.front(); q.pop();
		for(auto e:g[u]){
			(cnt[e.dst]+=cnt[u])%=MOD;
			if(--deg[e.dst]==0)
				q.push(e.dst);
		}
	}
	return cnt;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		int s,t; cin>>s>>t; s--,t--;
		Graph g(n);
		rep(i,m){
			int u,v,d; cin>>u>>v>>d; u--,v--;
			g[u].emplace_back(u,v,d);
			g[v].emplace_back(v,u,d);
		}
		vl d1(n,INF),d2(n,INF);
		Dijkstra(g,s,d1);
		Dijkstra(g,t,d2);

		ll total=d1[t];

		Graph g1(n),g2(n);
		rep(i,n) for(auto e:g[i]){
			if(d1[e.src]+e.weight+d2[e.dst]==total)
				g1[e.src].push_back(e);
			if(d2[e.src]+e.weight+d1[e.dst]==total)
				g2[e.src].push_back(e);
		}

		vl c1(n),c2(n);
		count(g1,s,c1);
		count(g2,t,c2);

		ll sum=c1[t]*c2[s]%MOD;

		// 頂点上で衝突する
		ll sub1=0;
		rep(i,n) if(d1[i]*2==total&&d2[i]*2==total){
			ll x=c1[i]*c2[i]%MOD;
			(sub1+=x*x)%=MOD;
		}

		// 辺上で衝突する
		ll sub2=0;
		rep(i,n) for(auto e:g1[i]) if(2*d1[e.src]<total&&2*d2[e.dst]<total){
			ll x=c1[e.src]*c2[e.dst]%MOD;
			(sub2+=x*x)%=MOD;
		}

		cout<<(sum-sub1+MOD-sub2+MOD)%MOD<<endl;
	}
}
