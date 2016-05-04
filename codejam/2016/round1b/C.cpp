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
using pii=pair<int,int>;

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

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
typedef vector<vector<Edge> > Graph;

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

struct Solver{
	void input();
	string solve();
	int n;
	vs ss,ts;
};

void Solver::input()
{
	cin>>n;
	ss.assign(n,"#"),ts.assign(n,"#");
	rep(i,n) cin>>ss[i]>>ts[i];
}

string Solver::solve()
{
	int l,r;
	vi us(n),vs(n);
	{
		map<string,int> f,g;
		rep(i,n){
			f.emplace(ss[i],f.size());
			g.emplace(ts[i],g.size());
			us[i]=f[ss[i]];
			vs[i]=g[ts[i]];
		}
		l=f.size(),r=g.size();
	}
	
	Graph g(l+r);
	rep(i,n) g[us[i]].emplace_back(us[i],l+vs[i]);
	vi side(l+r),match; fill(l+all(side),1);
	
	int cover=l+r-HopcroftKarp(g,side,match);
	return to_string(n-cover);
}

int main()
{
	int T; cin>>T;
	vector<Solver> solvers(T);
	rep(i,T) solvers[i].input();
	
	vector<string> results(T);
	#pragma omp parallel for schedule(dynamic)
	rep(i,T){
		results[i]=solvers[i].solve();
		fprintf(stderr,"#%d finish\n",i+1);
	}
	
	rep(i,T) printf("Case #%d: %s\n",i+1,results[i].c_str());
}
