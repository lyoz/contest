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

vi get_reachable(const Graph& g)
{
	int n=g.size();
	vi res(n,1);

	{
		queue<int> q; q.push(0);
		vi vis(n);
		while(q.size()){
			int u=q.front(); q.pop();
			if(exchange(vis[u],1))
				continue;
			for(auto e:g[u])
				q.push(e.dst);
		}

		rep(i,n)
			res[i]&=vis[i];
	}

	{
		Graph gt(n); // transpose
		rep(i,n) for(auto e:g[i])
			gt[e.dst].emplace_back(e.dst,e.src,e.weight);

		queue<int> q; q.push(n-1);
		vi vis(n);
		while(q.size()){
			int u=q.front(); q.pop();
			if(exchange(vis[u],1))
				continue;
			for(auto e:gt[u])
				q.push(e.dst);
		}

		rep(i,n)
			res[i]&=vis[i];
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

	for(int n,m,p;cin>>n>>m>>p&&n|m|p;){
		Graph g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			ll w; cin>>w;
			g[u].emplace_back(u,v,w);
		}
		vi rs=get_reachable(g);

		Graph gn(n); // negative
		rep(i,n) for(auto e:g[i])
			gn[e.src].emplace_back(e.src,e.dst,p-e.weight);

		bool has_negative_cycle=false;

		vl ds(n,INF);
		ds[0]=0;
		rep(k,n-1){
			rep(u,n) if(rs[u]){
				for(auto e:gn[u]){
					if(ds[e.dst]>ds[e.src]+e.weight)
						ds[e.dst]=ds[e.src]+e.weight;
				}
			}
		}
		{
			rep(u,n) if(rs[u]){
				for(auto e:gn[u]){
					if(ds[e.dst]>ds[e.src]+e.weight)
						has_negative_cycle=true;
				}
			}
		}

		if(has_negative_cycle)
			cout<<-1<<endl;
		else
			cout<<max(-ds[n-1],0ll)<<endl;
	}
}
