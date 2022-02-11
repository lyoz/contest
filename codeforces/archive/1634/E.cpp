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

using Edge=tuple<int,int,int>; // u,v,rev

void dfs(vector<vector<Edge>>& g,int u,vector<Edge>& order)
{
	while(g[u].size()){
		auto [_,v,rev]=g[u].back();
		g[u].pop_back();
		if(rev>=g[v].size())
			continue;
		dfs(g,v,order);
		order.emplace_back(u,v,rev);
	}
}

vector<vector<Edge>> EulerianTrails(const vector<vector<Edge>>& g)
{
	vector<vector<Edge>> g2=g;
	vector<vector<Edge>> orders;
	rep(u,g2.size())
		if(g2[u].size()){
			vector<Edge> order;
			dfs(g2,u,order);
			reverse(all(order));
			orders.push_back(order);
		}
	return orders;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int m;cin>>m&&m;){
		vvi a(m);
		rep(i,m){
			int n; cin>>n;
			a[i].resize(n);
			for(int& x:a[i])
				cin>>x;
		}

		if(![&](){
			map<int,int> f;
			rep(i,m) for(int x:a[i])
				f[x]++;
			for(auto [k,v]:f)
				if(v&1)
					return false;
			return true;
		}()){
			cout<<"NO"<<endl;
			continue;
		}

		map<int,int> rank;
		{
			set<int> s;
			rep(i,m)
				s.insert(all(a[i]));
			for(auto x:s)
				rank.emplace(x,rank.size());
		}

		vector<vector<Edge>> g(m+rank.size());
		rep(i,m) for(int x:a[i]){
			int u=i,v=m+rank[x];
			g[u].emplace_back(u,v,g[v].size());
			g[v].emplace_back(v,u,g[u].size()-1);
		}

		vector<vector<Edge>> orders=EulerianTrails(g);
		map<tuple<int,int>,int> f;
		for(auto o:orders)
			for(auto [u,v,_]:o)
				f[{u,v}]++;

		vs res(m);
		rep(i,m) for(int x:a[i])
			res[i]+=f[{i,m+rank[x]}]-->0?'L':'R';

		cout<<"YES"<<endl;
		rep(i,m)
			cout<<res[i]<<endl;
	}
}
