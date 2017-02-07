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

bool solve(const vvi& g,const vi& a,int u,vi& win)
{
	if(win[u]!=-1) return win[u];
	win[u]=0;
	for(int v:g[u]) if(!solve(g,a,v,win)) win[u]=1;
	return win[u];
}

int main()
{
	for(int n;cin>>n&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			if(a[u]>a[v]) g[u].push_back(v);
			if(a[v]>a[u]) g[v].push_back(u);
		}
		vi win(n,-1);
		rep(i,n) solve(g,a,i,win);
		vi res;
		rep(i,n) if(win[i]) res.push_back(i);
		rep(i,res.size()) cout<<res[i]+1<<(i+1<res.size()?" ":""); cout<<endl;
	}
}
