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

template<typename T> bool chmin(T& a,const T& b){return a>b?a=b,true:false;}
template<typename T> bool chmax(T& a,const T& b){return a<b?a=b,true:false;}

int solve_naive(int n,int m,vi a)
{
	vvl dp(m+1,vl(n+1,INF));
	dp[0][0]=0;
	rep(i,m){
		dp[i+1][0]=0;
		rep(j,n){
			vi f(n);
			ll t=0;
			per(k,j+1){
				t+=f[a[k]]++;
				chmin(dp[i+1][j+1],dp[i][k]+t);
			}
		}
	}
	return dp[m][n];
}

struct Cost{
	vi a,freq;
	ll cost;
	int cl,cr;
	Cost(const vi& a):a(a),freq(a.size()),cost(0),cl(0),cr(0){}
	ll Get(int l,int r){
		repi(i,l,cl) cost+=freq[a[i]]++;
		repi(i,cr,r) cost+=freq[a[i]]++;
		repi(i,cl,l) cost-=--freq[a[i]];
		repi(i,r,cr) cost-=--freq[a[i]];
		cl=l,cr=r;
		return cost;
	}
};

void dfs(vvl& dp,int i,int l,int r,int cl,int cr,Cost& cost)
{
	if(l==r) return;
	int j=(l+r)/2;

	// dp[i+1][j]=min_k{dp[i][k]+cost[k,j)}
	int best=cl;
	for(int k=cl;k<min(cr,j);k++)
		if(chmin(dp[i+1][j],dp[i][k]+cost.Get(k,j)))
			best=k;

	dfs(dp,i,l,j,cl,best+1,cost);
	dfs(dp,i,j+1,r,best,cr,cost);
}

ll solve(int n,int m,vi a)
{
	vvl dp(m+1,vl(n+1,INF));
	dp[0][0]=0;
	rep(i,m){
		Cost cost(a);
		dp[i+1]=dp[i];
		dfs(dp,i,0,n+1,0,n,cost);
	}
	return dp[m][n];
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vi a(n);
		rep(i,n) cin>>a[i],a[i]--;
		cout<<solve(n,m,a)<<endl;
	}
}
