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

void rotate(int& h,int& w,vs& grid)
{
	vs tmp(w,string(h,' '));
	rep(i,h) rep(j,w) tmp[j][i]=grid[i][j];
	swap(h,w);
	rep(i,h) reverse(all(tmp[i]));
	swap(grid,tmp);
}

int solve_two_line(const string& a,const string& b)
{
	int n=a.size();
	vvi cost(n+1,vi(n+1));
	per(i,n) per(j,n)
		cost[i][j]=cost[i+1][j+1]+(a[i]==b[j]);
	vvi dp(n+1,vi(n+1,INF)); dp[0][0]=0;
	rep(i,n) rep(j,n){
		dp[i+1][j]=min(dp[i+1][j],dp[i][j]+cost[i][j]);
		dp[i][j+1]=min(dp[i][j+1],dp[i][j]+cost[i][j]);
	}
	rep(i,n){
		dp[i+1][n]=min(dp[i+1][n],dp[i][n]);
		dp[n][i+1]=min(dp[n][i+1],dp[n][i]);
	}
	return dp[n][n];
}

int solve(const vs& grid,const vi& costs,int i,int j,vvi& memo)
{
	if(memo[i][j]!=INF) return memo[i][j];
	if(j-i<=1) return memo[i][j]=0;
	int res=INF;
	repi(k,i+1,j){
		int tmp=solve(grid,costs,i,k,memo)+solve(grid,costs,k,j,memo)+costs[k-1];
		res=min(res,tmp);
	}
	return memo[i][j]=res;
}

int solve(const vs& grid,const vi& costs)
{
	int h=grid.size();
	vvi memo(h+1,vi(h+1,INF));
	return solve(grid,costs,0,h,memo);
}

int main()
{
	for(int h,w;cin>>h>>w && h|w;){
		vs grid(h);
		rep(i,h) cin>>grid[i];

		// 扱いやすくするために回転させる．左へ向かって落ちる
		rotate(h,w,grid);

		vi costs(h-1);  // costs[i]: i,i+1の2行だけの場合のコスト
		rep(i,h-1) costs[i]=solve_two_line(grid[i],grid[i+1]);
		cout<<solve(grid,costs)<<endl;
	}
}
