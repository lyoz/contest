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

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

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

struct Factorial{
	vi fact,ifact;
	int m;
	Factorial(int size,int m):fact(size),ifact(size),m(m){
		fact[0]=1;
		repi(i,1,size) fact[i]=(ll)fact[i-1]*i%m;
		rep(i,size) ifact[i]=ModInverse(fact[i],m);
	}
	int Choose(int n,int r){
		return (ll)fact[n]*ifact[n-r]%m*ifact[r]%m;
	}
};

int solve(int n,int m)
{
	Factorial f(n+1,m);

	vvl dp(n+1,vl(n+1));
	rep(i,n+1) dp[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			dp[i][j]=(dp[i-1][j-1]+ll(j+1)*dp[i-1][j])%m;
	
	int res=0;
	for(int i=0;i<=n;i++){
		ll add=0;
		for(int j=0;j<=i;j++)
			(add+=dp[i][j]*ModPow(2,(n-i)*j,m))%=m;
		(add*=ModPow(2,ModPow(2,n-i,m-1),m))%=m;
		(add*=f.Choose(n,i))%=m;
		if(i&1) add=m-add;
		(res+=add)%=m;
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

	for(int n,m;cin>>n>>m&&n|m;){
		cout<<solve(n,m)<<endl;
	}
}
