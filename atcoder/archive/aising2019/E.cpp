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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

vvl solve(const vvi& g,const vl& a,int u,int p)
{
	// udp[0][i]: uを根とする部分木をi回切断した場合の、uを含む連結成分がバッテリーだけのときのsumの最小値
	// udp[1][i]: uを根とする部分木をi回切断した場合の、uを含む連結成分のsumの最小値
	vvl udp(2,vl(1,INF));
	if(a[u]>0)
		udp[0][0]=a[u];
	udp[1][0]=a[u];
	for(int v:g[u]) if(v!=p){
		vvl vdp=solve(g,a,v,u);
		int usize=udp[0].size(),vsize=vdp[0].size();
		vvl dp(2,vl(usize+vsize,INF));
		rep(i,usize) rep(j,vsize){
			// u-v間を切断しない
			chmin(dp[0][i+j],udp[0][i]+vdp[0][j]);
			chmin(dp[1][i+j],udp[1][i]+vdp[1][j]);
			// u-v間を切断する
			if(vdp[0][j]!=INF||vdp[1][j]<0){
				chmin(dp[0][i+j+1],udp[0][i]);
				chmin(dp[1][i+j+1],udp[1][i]);
			}
		}
		udp=dp;
	}
	return udp;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vl a(n);
		rep(i,n) cin>>a[i];
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}

		vvl dp=solve(g,a,0,-1);
		int res=n-1;
		rep(i,n){
			if(dp[0][i]!=INF)
				chmin(res,i);
			if(dp[1][i]<0)
				chmin(res,i);
		}
		cout<<res<<endl;
	}
}
