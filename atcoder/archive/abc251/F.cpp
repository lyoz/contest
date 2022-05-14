#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vvvl=vector<vvl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vvvd=vector<vvd>;
using vs=vector<string>;
using vvs=vector<vs>;

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

void dfs(const vvi& g,int u,vi& vis,vector<tuple<int,int>>& res)
{
	for(int v:g[u]) if(!vis[v]){
		res.emplace_back(u,v);
		vis[v]=1;
		dfs(g,v,vis,res);
	}
}

vector<tuple<int,int>> solve1(const vvi& g){
	int n=g.size();
	vector<tuple<int,int>> res;
	vi vis(n); vis[0]=1;
	dfs(g,0,vis,res);
	return res;
}

vector<tuple<int,int>> solve2(const vvi& g){
	int n=g.size();
	vector<tuple<int,int>> res;
	vi vis(n); vis[0]=1;
	queue<int> q; q.push(0);
	while(q.size()){
		int u=q.front(); q.pop();
		for(int v:g[u]) if(!vis[v]){
			res.emplace_back(u,v);
			vis[v]=1;
			q.push(v);
		}
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

	for(int n,m;cin>>n>>m&&n|m;){
		vvi g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for(auto [u,v]:solve1(g))
			cout<<u+1<<' '<<v+1<<endl;
		for(auto [u,v]:solve2(g))
			cout<<u+1<<' '<<v+1<<endl;
	}
}
