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

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

ll solve(ll b,ll x)
{
	vi a;
	for(ll t=x;t;t/=b) a.push_back(t%b);
	reverse(all(a));
	int n=a.size();

	constexpr int n_max=64;
	constexpr int b_max=10;

	static vvl memo[n_max][b_max];
	if(memo[n][b].empty()){
		vvl dp(n,vl(1<<b));
		dp[n-1][0]=1;
		per(i,n-1)
			rep(d,b)
				rep(j,1<<b)
					dp[i][(1<<d)^j]+=dp[i+1][j];
		memo[n][b]=dp;
	}
	vvl& dp=memo[n][b];

	ll res=0;
	repi(i,1,n)
		repi(d,1,b)
			res+=dp[i][1<<d];

	int mask=0;
	rep(i,n){
		repi(d,i==0,a[i])
			res+=dp[i][mask^1<<d];
		mask^=1<<a[i];
	}

	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int q;cin>>q&&q;){
		rep(_,q){
			ll b,l,r; cin>>b>>l>>r;
			cout<<solve(b,r+1)-solve(b,l)<<endl;
		}
	}
}
