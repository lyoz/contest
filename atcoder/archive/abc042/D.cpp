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

ll mod_inverse(ll a,ll m)
{
	ll x=1;
	for(ll b=m,u=0;b;){
		ll t=a/b;
		swap(a-=b*t,b);
		swap(x-=u*t,u);
	}
	return (x+m)%m;
}

vl fact(200005);
vl ifact(200005);

ll ncr(ll n,ll r,ll m=MOD)
{
	return fact[n]*ifact[n-r]%m*ifact[r]%m;
}

int main()
{
	fact[0]=ifact[0]=1;
	repi(i,1,fact.size()) fact[i]=i*fact[i-1]%MOD;
	repi(i,1,ifact.size()) ifact[i]=mod_inverse(fact[i],MOD);

	for(ll h,w,a,b;cin>>h>>w>>a>>b && h|w|a|b;){
		ll d1=h-a,d2=a,r1=b,r2=w-b;
		ll res=ncr(h-1+w-1,h-1);
		ll sub=0;
		for(ll k=d1;k<=min(h-1,d1+r1-1);k++)
			(sub+=ncr(d1+r1-1,k)*ncr(h-1+w-1-(d1+r1-1),h-1-k))%=MOD;
		res=(res-sub+MOD)%MOD;
		cout<<res<<endl;
	}
}
