#include <bits/stdc++.h>
#include <omp.h>
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

struct Edge{
	int src,dst,weight;
	Edge(){}
	Edge(int s,int d,int w):src(s),dst(d),weight(w){}
};
using Graph=vector<vector<Edge>>;

struct Solver{
	int n,m,k;
	Graph g;
	vi ss,ds;
	void input();
	string solve();
};

void Solver::input()
{
	cin>>n>>m>>k;
	g.resize(n);
	rep(i,m){
		int u,v,w; cin>>u>>v>>w; u--,v--;
		g[u].emplace_back(u,v,w);
		g[v].emplace_back(v,u,w);
	}
	ss.resize(k);
	ds.resize(k);
	rep(i,k){
		cin>>ss[i]>>ds[i];
		ss[i]--,ds[i]--;
	}
}

string Solver::solve()
{
	vvi dist(n,vi(n,INF));
	rep(i,n) dist[i][i]=0;
	for(auto es:g) for(auto e:es)
		dist[e.src][e.dst]=min(dist[e.src][e.dst],e.weight);
	rep(k,n) rep(i,n) rep(j,n)
		dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);

	ss.insert(begin(ss),0);
	ds.insert(begin(ds),0);
	vector<vvi> dp(2,vvi(k+1,vi(k+1,INF)));
	dp[0][0][0]=dp[1][0][0]=0;
	rep(i,k+1) rep(j,i+1){
		if(i<k && i<j+2)
			dp[0][i+1][j]=min({dp[0][i+1][j],dp[0][i][j]+dist[ss[i]][ss[i+1]],dp[1][i][j]+dist[ds[j]][ss[i+1]]});
		if(j<i)
			dp[1][i][j+1]=min({dp[1][i][j+1],dp[0][i][j]+dist[ss[i]][ds[j+1]],dp[1][i][j]+dist[ds[j]][ds[j+1]]});
	}

	return dp[1][k][k]==INF?"-1":to_string(dp[1][k][k]);
}

int main()
{
	int T; cin>>T;
	vector<Solver> solvers(T);
	rep(i,T) solvers[i].input();
	
	vector<string> results(T);
	#ifndef _OPENMP
	fputs("------- run with single thread -------\n",stderr);
	#else
	fprintf(stderr,"------- run with %d threads -------\n",omp_get_max_threads());
	#pragma omp parallel for schedule(dynamic)
	#endif
	rep(i,T){
		results[i]=solvers[i].solve();
		fprintf(stderr,"#%d finish\n",i+1);
	}
	
	rep(i,T) printf("Case #%d: %s\n",i+1,results[i].c_str());
}
