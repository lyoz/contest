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

int ModInverse(int a,int m)
{
	int x=1;
	for(int b=m,u=0;b;){
		ll t=a/b;
		swap(a-=b*t,b);
		swap(x-=u*t,u);
	}
	return (x+m)%m;
}

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

int ModMul(int a,int b,int m)
{
	return ll(a)*b%m;
}

int ModMul(int a,int b,int c,int m)
{
	return ModMul(ModMul(a,b,m),c,m);
}

int ModDiv(int a,int b,int m)
{
	return ModMul(a,ModInverse(b,m),m);
}

vl xinv(1001),f(1001),finv(1001);

// m! / ((x!)^k * (m-k*x)! * k!)
int calc(int m,int k,int x)
{
	return ModDiv(f[m],ModMul(ModPow(f[x],k,MOD),f[m-k*x],f[k],MOD),MOD);
}

int main()
{
	f[0]=finv[0]=1;
	for(int i=1;i<=1000;i++){
		xinv[i]=ModInverse(i,MOD);
		f[i]=f[i-1]*i%MOD;
		finv[i]=ModInverse(f[i],MOD);
	}

	for(int n,a,b,c,d;cin>>n>>a>>b>>c>>d&&n|a|b|c|d;){
		vvl dp(b-a+2,vl(n+1));
		dp[0][0]=1;
		rep(i,b-a+1){
			int x=a+i;
			rep(j,n+1){
				(dp[i+1][j]+=dp[i][j])%=MOD;
				for(int k=c;k<=d&&j+k*x<=n;k++)
					(dp[i+1][j+k*x]+=dp[i][j]*calc(n-j,k,x))%=MOD;
			}
		}
		cout<<dp[b-a+1][n]<<endl;
	}
}
