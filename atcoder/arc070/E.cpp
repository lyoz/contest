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

int solve_small(int n,vi ls,vi rs)
{
	int m=*max_element(all(ls));
	vvi dp(n,vi(m+1,INF));
	rep(x,m+1)
		dp[0][x]=abs(x-ls[0]);
	repi(i,1,n){
		rep(j,m+1){
			int c=abs(j-ls[i]);
			int l=max(j-(rs[i-1]-ls[i-1]),0);
			int r=min(j+(rs[i]-ls[i]),m);
			repi(x,l,r+1)
				dp[i][j]=min(dp[i][j],dp[i-1][x]+c);
		}
	}
	return *min_element(all(dp.back()));
}

int main()
{
	for(int n;cin>>n&&n;){
		vi ls(n),rs(n);
		rep(i,n) cin>>ls[i]>>rs[i];
		if(n<=400&&*max_element(all(rs))<=400){
			cout<<solve_small(n,ls,rs)<<endl;
		}
		else{
			cout<<"(>_<)"<<endl;
		}
	}
}
