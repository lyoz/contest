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

void paint(const vvi& g,int v,int d,int c,vi& ns,vi& res)
{
	queue<tuple<int,int>> q;
	q.emplace(v,d);
	while(q.size()){
		int cv,cd; tie(cv,cd)=q.front(); q.pop();
		if(ns[cv]>=cd)
			continue;
		if(ns[cv]==-1)
			res[cv]=c;
		ns[cv]=cd;
		if(cd==0)
			continue;
		for(int nv:g[cv])
			q.emplace(nv,cd-1);
	}
}

int main()
{
	for(int n,m;cin>>n>>m&&n|m;){
		vvi g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int q; cin>>q;
		vi vs(q),ds(q),cs(q);
		rep(i,q){
			cin>>vs[i]>>ds[i]>>cs[i];
			vs[i]--;
		}

		vi ns(n,-1),res(n);
		per(i,q)
			paint(g,vs[i],ds[i],cs[i],ns,res);

		rep(i,n) cout<<res[i]<<endl;
	}
}
