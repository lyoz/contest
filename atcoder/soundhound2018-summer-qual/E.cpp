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
	ll weight;
	Edge(int s,int d,ll w):src(s),dst(d),weight(w){}
};
using Graph=vector<vector<Edge>>;

void dfs(const Graph& g,int u,vector<tuple<ll,ll>>& cs)
{
	for(auto e:g[u]){
		int v=e.dst;
		ll w=e.weight;
		int c0,c1; tie(c0,c1)=cs[u];
		tuple<ll,ll> cv(w-c0,-c1);  // w-(c0+c1*x)
		if(cs[v]==mt(0,0)){
			cs[v]=cv;
			dfs(g,v,cs);
		}
		else{
			if(cs[v]==cv)
				continue;
			else if(get<1>(cs[v])!=get<1>(cv)){
				// 奇数長閉路なのでxは一意に決まる
				// get<0>(cs[v])+get<1>(cs[v])*x == get<0>(cv)+get<1>(cv)*x
				ll num=get<0>(cv)-get<0>(cs[v]);
				ll den=get<1>(cs[v])-get<1>(cv);
				throw num%den==0?num/den:0;
			}
			else{
				assert(get<0>(cs[v])!=get<0>(cv));
				throw 0ll;
			}
		}
	}
}

bool validate(const Graph& g,int u,vl& xs)
{
	for(auto e:g[u]){
		int v=e.dst;
		ll w=e.weight;
		if(xs[v]){
			if(xs[v]!=w-xs[u])
				return false;
		}
		else{
			if(w-xs[u]<=0)
				return false;
			xs[v]=w-xs[u];
			if(!validate(g,v,xs))
				return false;
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
		rep(_,m){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			g[u].emplace_back(u,v,w);
			g[v].emplace_back(v,u,w);
		}
		// 頂点0の値をxとする
		try{
			vector<tuple<ll,ll>> cs(n);  // c0+c1*x
			cs[0]=mt(0,1);
			dfs(g,0,cs);
			ll mn=1,mx=INF;
			repi(i,1,n){
				int c0,c1; tie(c0,c1)=cs[i];
				// 1<=c0+c1*x
				if(c1==1){
					// 1-c0<=x
					chmax(mn,1-c0);
				}
				else{
					// 1-c0<=-x
					chmin(mx,c0-1);
				}
			}
			cout<<max<ll>(mx-mn+1,0)<<endl;
		}
		catch(ll x){
			if(x<=0)
				cout<<0<<endl;
			else{
				vl xs(n); xs[0]=x;
				cout<<validate(g,0,xs)<<endl;
			}
		}
	}
}
