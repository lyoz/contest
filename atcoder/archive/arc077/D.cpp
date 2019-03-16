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

int mod_pow(int a,int b,int m)
{
	int x=1;
	for(;b;b>>=1){
		if(b&1)
			x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

vl f(100000),g(100000);
ll choose(int n,int r)
{
	if(r<0||n<r)
		return 0;
	return f[n]*g[n-r]%MOD*g[r]%MOD;
}

int main()
{
	f[0]=g[0]=1;
	repi(i,1,f.size()){
		f[i]=i*f[i-1]%MOD;
		g[i]=mod_pow(f[i],MOD-2,MOD);
	}

	for(int n;cin>>n&&n;){
		vi a(n+1);
		rep(i,n+1) cin>>a[i];

		int l=0,c=0,r=0;
		{
			vi cnt(n+1);
			rep(i,n+1) cnt[a[i]]++;
			int x=find(all(cnt),2)-begin(cnt);
			rep(i,n+1) if(cnt[i]==2) x=i;
			l=find(all(a),x)-begin(a);
			c=find(l+1+all(a),x)-begin(a)-l-1;
			r=n-1-l-c;
		}

		repi(i,1,n+2){
			ll x=choose(n-1,i);
			ll y=(choose(n-1,i-1)*2-choose(l+r,i-1)+MOD)%MOD;
			ll z=choose(n-1,i-2);
			cout<<(x+y+z)%MOD<<endl;
		}
	}
}
