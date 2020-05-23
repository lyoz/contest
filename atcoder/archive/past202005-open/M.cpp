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

vi calc(const vvi& g,int s,const vi& ts)
{
	queue<tuple<int,int>> q;
	q.emplace(s,0);
	vi ds(g.size(),INF);
	while(q.size()){
		int u,d; tie(u,d)=q.front(); q.pop();
		if(ds[u]!=INF)
			continue;
		ds[u]=d;
		for(int v:g[u])
			q.emplace(v,d+1);
	}
	vi res;
	for(int t:ts)
		res.push_back(ds[t]);
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
		int s,k; cin>>s>>k; s--;
		vi ts(k);
		rep(i,k) cin>>ts[i],ts[i]--;

		vi sd=calc(g,s,ts);
		vvi ds(k);
		rep(i,k) ds[i]=calc(g,ts[i],ts);

		vvi dp(k,vi(1<<k,INF));
		rep(i,k)
			dp[i][1<<i]=sd[i];
		rep(b,1<<k){
			rep(i,k) if(b>>i&1){
				rep(j,k) if(!(b>>j&1)){
					chmin(dp[j][b|1<<j],dp[i][b]+ds[i][j]);
				}
			}
		}
		int res=INF;
		rep(i,k) chmin(res,dp[i].back());
		cout<<res<<endl;
	}
}
