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

int ModMul(int a,int b,int m)
{
	return (ll)a*b%m;
}

int ModDiv(int a,int b,int m)
{
	return ModMul(a,ModInverse(b,m),m);
}

int main()
{
	for(int n,k;cin>>n>>k&&n|k;){
		vi divs;
		for(int i=1;i*i<=n;i++){
			if(n%i==0){
				divs.push_back(i);
				if(i*i!=n)
					divs.push_back(n/i);
			}
		}
		sort(all(divs));

		int m=divs.size();
		vi dp(m);
		rep(i,m){
			dp[i]=ModPow(k,(divs[i]+1)/2,MOD);
			rep(j,i) if(divs[i]%divs[j]==0)
				dp[i]=(dp[i]-dp[j]+MOD)%MOD;
		}

		int res=0;
		rep(i,m)
			if(divs[i]%2==0)
				(res+=ModDiv(ModMul(divs[i],dp[i],MOD),2,MOD))%=MOD;
			else
				(res+=ModMul(divs[i],dp[i],MOD))%=MOD;
		cout<<res<<endl;
	}
}
