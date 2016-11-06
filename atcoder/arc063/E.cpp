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

void dfs(const vvi& g,int p,int u,bool odd,const vi& ps,vector<tuple<int,int>>& rs)
{
	int mn=-INF,mx=INF;
	if(ps[u]!=-1){
		if(ps[u]%2!=odd)
			throw "X";
		tie(mn,mx)=mt(ps[u],ps[u]);
	}
	for(int v:g[u]) if(v!=p)
		dfs(g,u,v,!odd,ps,rs);
	for(int v:g[u]) if(v!=p){
		mn=max(mn,get<0>(rs[v])-1);
		mx=min(mx,get<1>(rs[v])+1);
	}
	if(mn>mx)
		throw "X";
	rs[u]=mt(mn,mx);
}

void dfs2(const vvi& g,int p,int u,vi& ps,const vector<tuple<int,int>>& rs)
{
	for(int v:g[u]) if(v!=p){
		int p=ps[u]-1;
		if(p<get<0>(rs[v])) p+=2;
		ps[v]=p;
		dfs2(g,u,v,ps,rs);
	}
}

void solve(const vvi& g,vi& ps)
{
	int n=g.size();
	vector<tuple<int,int>> rs(n);
	rep(i,n) if(ps[i]!=-1){
		dfs(g,-1,i,ps[i]%2,ps,rs);
		dfs2(g,-1,i,ps,rs);
		break;
	}
}

int main()
{
	for(int n;cin>>n && n;){
		vvi g(n);
		vi ps(n,-1);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int k; cin>>k;
		rep(i,k){
			int v,p; cin>>v>>p; v--;
			ps[v]=p;
		}

		try{
			solve(g,ps);
			cout<<"Yes"<<endl;
			for(int p:ps)
				cout<<p<<endl;
		}
		catch(...){
			cout<<"No"<<endl;
		}
	}
}
