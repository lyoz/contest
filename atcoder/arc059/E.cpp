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

int solve_small(int n,int c,vi as,vi bs)
{
	rep(i,n) assert(as[i]==bs[i]);

	vvi xs(n,vi(c+1));  // xs[i][j]=x_iのj乗
	rep(i,n){
		xs[i][0]=1;
		rep(j,c) xs[i][j+1]=ll(xs[i][j])*as[i]%MOD;
	}

	vvi dp(n+1,vi(c+1));  // dp[i][j]: [0,i)までにj個使う
	dp[0][0]=1;
	rep(i,n) rep(j,c+1) rep(k,j+1)
		dp[i+1][j]=(dp[i+1][j]+(ll)dp[i][j-k]*xs[i][k])%MOD;

	return dp[n][c];
}

int solve(int n,int c,vi as,vi bs)
{
	vvi pow(401,vi(401));  // pow[i][j]: pow(i,j)
	rep(i,pow.size()){
		pow[i][0]=1;
		repi(j,1,pow[i].size())
			pow[i][j]=(ll)pow[i][j-1]*i%MOD;
	}

	vvi xs(n,vi(c+1));
	rep(i,n)
		rep(j,c+1)
			repi(x,as[i],bs[i]+1)
				(xs[i][j]+=pow[x][j])%=MOD;

	vvi dp(n+1,vi(c+1));
	dp[0][0]=1;
	rep(i,n) rep(j,c+1) rep(k,j+1)
		dp[i+1][j]=(dp[i+1][j]+(ll)dp[i][j-k]*xs[i][k])%MOD;

	return dp[n][c];
}

int main()
{
	for(int n,c;cin>>n>>c && n|c;){
		vi as(n),bs(n);
		rep(i,n) cin>>as[i];
		rep(i,n) cin>>bs[i];
		cout<<solve(n,c,as,bs)<<endl;
	}
}
