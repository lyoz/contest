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

bool dfs(const vvi& g,const vl& a,int p,int u,vl& xs)
{
	int m=0;
	for(int v:g[u]) if(v!=p) m++;
	if(m==0){
		xs[u]=a[u];
		return true;
	}
	ll sum=0,mx=0;
	for(int v:g[u]) if(v!=p){
		if(!dfs(g,a,u,v,xs))
			return false;
		sum+=xs[v];
		mx=max(mx,xs[v]);
	}
	xs[u]=2*a[u]-sum;
	if(xs[u]<0||sum-xs[u]<0||(sum-xs[u])/2>sum-mx)
		return false;
	if(u==0){	// root
		if(m==1&&xs[u]!=sum)
			return false;
		if(m>1&&xs[u]>0)
			return false;
	}
	return true;
}

int main()
{
	for(int n;cin>>n&&n;){
		vl a(n);
		rep(i,n) cin>>a[i];
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		vl xs(n);
		cout<<(dfs(g,a,-1,0,xs)?"YES":"NO")<<endl;
	}
}
