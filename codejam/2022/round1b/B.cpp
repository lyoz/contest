#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vvvl=vector<vvl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vvvd=vector<vvd>;
using vs=vector<string>;
using vvs=vector<vs>;

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

ll diff(ll a,ll b)
{
	return abs(a-b);
}

void solve()
{
	int n,p; cin>>n>>p;
	vvl xs(n,vl(p));
	rep(i,n) rep(j,p) cin>>xs[i][j];

	vl mins(n),maxs(n);
	rep(i,n){
		mins[i]=*min_element(all(xs[i]));
		maxs[i]=*max_element(all(xs[i]));
	}

	vector dp(n+1,array<ll,2>());
	rep(i,n){
		ll d=maxs[i]-mins[i];
		{
			ll d0=dp[i][0]+diff(i?mins[i-1]:0,maxs[i])+d;
			ll d1=dp[i][1]+diff(i?maxs[i-1]:0,maxs[i])+d;
			dp[i+1][0]=min(d0,d1);
		}
		{
			ll d0=dp[i][0]+diff(i?mins[i-1]:0,mins[i])+d;
			ll d1=dp[i][1]+diff(i?maxs[i-1]:0,mins[i])+d;
			dp[i+1][1]=min(d0,d1);
		}
	}
	cout<<min(dp[n][0],dp[n][1])<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(_,tc){
		cout<<"Case #"<<_+1<<": ";
		solve();
	}
}
