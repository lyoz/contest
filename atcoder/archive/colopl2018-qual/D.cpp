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

void dfs(ll n,ll x,vl& ts,vvl& dp,int i,int l,int r,int cl,int cr)
{
	if(l==r) return;
	int j=(l+r)/2;
	int best=cl;
	for(int k=cl;k<min(cr,j);k++)
		if(chmin(dp[i+1][j],dp[i][k]+max(ts[j]-ts[k]-x,0ll)))
			best=k;
	dfs(n,x,ts,dp,i,l,j,cl,best+1);
	dfs(n,x,ts,dp,i,j+1,r,best,cr);
}

vl solve(ll n,ll x,vl ts)
{
	constexpr ll INF=1e18;
	ts.insert(begin(ts),-x);
	vvl dp(n+1,vl(n+1,INF));
	dp[0][0]=0;
	rep(i,n){
		dp[i+1]=dp[i];
		dfs(n,x,ts,dp,i,0,n+1,0,n);
	}
	vl res(n);
	ll sum=x+ts[n];
	rep(i,n) res[i]=sum-dp[i+1][n];
	return res;
}


int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(ll n,x;cin>>n>>x&&n|x;){
		vl ts(n);
		rep(i,n) cin>>ts[i];
		vl res=solve(n,x,ts);
		for(ll x:res) cout<<x<<endl;
	}
}
