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
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
using Graph=vector<vector<Edge>>;
using pii=pair<int,int>;

bool BFS(const Graph& g,const vi& side,const vi& match,vi& level)
{
	int n=g.size();
	level.assign(n,n);
	queue<pii> q;
	rep(i,n) if(side[i]==0 && match[i]==-1)
		q.push(mp(i,0));
	bool res=false;
	while(!q.empty()){
		pii cur=q.front(); q.pop();
		int u=cur.first,l=cur.second;
		if(level[u]<=l) continue;
		level[u]=l;
		rep(i,g[u].size()){
			int v=g[u][i].dst;
			if(match[v]==-1)
				res=true;
			else
				q.push(mp(match[v],l+2));
		}
	}
	return res;
}

bool DFS(const Graph& g,const vi& side,int u,vi& match,vi& level)
{
	rep(i,g[u].size()){
		int v=g[u][i].dst;
		if(match[v]==-1 || level[match[v]]>level[u] && DFS(g,side,match[v],match,level)){
			match[u]=v;
			match[v]=u;
			return true;
		}
	}
	level[u]=-1;
	return false;
}

int HopcroftKarp(const Graph& g,const vi& side,vi& match)
{
	int n=g.size();
	match.assign(n,-1);
	int res=0;
	for(vi level;BFS(g,side,match,level);)
		rep(i,n) if(side[i]==0 && match[i]==-1)
			res+=DFS(g,side,i,match,level);
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		Graph g(2*n);
		vi side(2*n),match;
		fill(n+all(side),1);
		{
			vi a(n),b(n),c(n),d(n);
			rep(i,n) cin>>a[i]>>b[i];
			rep(i,n) cin>>c[i]>>d[i];
			rep(i,n) rep(j,n)
				if(a[i]<c[j]&&b[i]<d[j])
					g[i].emplace_back(i,n+j);
		}
		cout<<HopcroftKarp(g,side,match)<<endl;
	}
}
