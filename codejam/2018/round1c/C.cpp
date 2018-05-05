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

void solve_set1(int n,vl ws)
{
	ll mx=*max_element(all(ws));
	vvl dp(n+1,vl(7*mx+1));
	rep(i,n){
		dp[i+1]=dp[i];
		rep(j,6*ws[i]+1)
			chmax(dp[i+1][j+ws[i]],dp[i][j]+1);
	}
	cout<<*max_element(all(dp[n]))<<endl;
}

void solve_set2(int n,vl ws)
{
	vvl dp(n+1,vl(150,INF));
	dp[0][0]=0;
	rep(i,n){
		dp[i+1]=dp[i];
		rep(j,min(i+1,150))
			if(dp[i][j]<=ws[i]*6)
				chmin(dp[i+1][j+1],dp[i][j]+ws[i]);
	}
	per(i,dp[n].size())
		if(dp[n][i]!=INF){
			cout<<i<<endl;
			return;
		}
}

void solve()
{
	int n; cin>>n;
	vl ws(n);
	rep(i,n) cin>>ws[i];

	solve_set2(n,ws);
}

void test()
{
	vl a(150);
	a[0]=1;
	ll sum=1;
	repi(i,1,a.size()){
		a[i]=(sum+5)/6;
		sum+=a[i];
	}
	rep(i,a.size()) dump(i,a[i]);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	//test(); return 0;

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}
