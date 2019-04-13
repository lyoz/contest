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

void dfs(const vvi& g,int p,int u,vi& cs)
{
	set<int> used;
	used.insert(cs[u]);
	for(int v:g[u]) if(cs[v]!=-1)
		used.insert(cs[v]);
	int c=0;
	for(int v:g[u]) if(cs[v]==-1){
		for(;used.count(c);c++);
		cs[v]=c++;
		dfs(g,u,v,cs);
	}
}

int main()
{
	for(int n;cin>>n&&n;){
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int m=0;
		rep(i,n) m=max<int>(m,g[i].size()+1);
		vi cs(n,-1); cs[0]=0;
		dfs(g,-1,0,cs);

		cout<<m<<endl;
		rep(i,n) cout<<cs[i]+1<<" \n"[i==n-1];
	}
}
