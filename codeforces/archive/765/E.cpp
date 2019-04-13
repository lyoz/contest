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

vi get_distances(const vvi& g,int root)
{
	vi ds(g.size(),INF);
	queue<tuple<int,int>> q; q.emplace(root,0);
	while(q.size()){
		int u,d; tie(u,d)=q.front(); q.pop();
		if(ds[u]!=INF) continue;
		ds[u]=d;
		for(int v:g[u]) q.emplace(v,d+1);
	}
	return ds;
}

int get_centroid(const vvi& g)
{
	vi ds0=get_distances(g,0);
	int a=max_element(all(ds0))-begin(ds0);
	vi dsa=get_distances(g,a);
	int b=max_element(all(dsa))-begin(dsa);
	vi dsb=get_distances(g,b);
	int diameter=*max_element(all(dsa));
	rep(i,g.size())
		if(dsa[i]==diameter/2&&dsb[i]==(diameter+1)/2)
			return i;
	return -1;
}

tuple<int,bool> dfs(const vvi& g,int p,int u)
{
	map<int,bool> f;
	for(int v:g[u]) if(v!=p){
		int d; bool single; tie(d,single)=dfs(g,u,v);
		if(f.count(d)==0)
			f[d]=single;
		else
			f[d]&=single;
	}
	if(f.empty())
		return mt(0,true);
	else if(f.size()==1)
		return mt(f.begin()->first+1,f.begin()->second);
	else
		return mt(f.rbegin()->first,false);
}

int solve(const vvi& g,int centroid)
{
	set<int> ds;
	for(int v:g[centroid]){
		int d; bool single; tie(d,single)=dfs(g,centroid,v);
		if(!single) return -1;
		ds.insert(d+1);
	}
	if(ds.size()>=3) return -1;
	int res=accumulate(all(ds),0);
	while(res%2==0) res/=2;
	return res;
}

int main()
{
	for(int n;cin>>n&&n;){
		vvi g(n);
		rep(_,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int centroid=get_centroid(g);
		cout<<solve(g,centroid)<<endl;
	}
}
