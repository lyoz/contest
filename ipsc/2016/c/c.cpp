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
constexpr int MOD=1e9+9;
constexpr double EPS=1e-9;

int mod_pow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

int mod_inverse(int a,int m)
{
	int x=1;
	for(int b=m,u=0;b;){
		ll t=a/b;
		swap(a-=b*t,b);
		swap(x-=u*t,u);
	}
	return (x+m)%m;
}

vi p(100001),f(100001),finv(100001);

int solve(vi a)
{
	int n=a.size();
	vi vis(n),cs;
	rep(i,n) if(!vis[i]){
		int cnt=0;
		for(int j=i;;){
			vis[j]=1;
			cnt++;
			if((j=a[j])==i) break;
		}
		cs.push_back(cnt);
	}

	ll res=1;
	for(int c:cs)
		(res*=p[c])%=MOD;
	(res*=f[n-cs.size()])%=MOD;
	for(int c:cs)
		(res*=finv[c-1])%=MOD;

	return res;
}

int main()
{
	p[0]=p[1]=1;
	repi(i,2,p.size())
		p[i]=mod_pow(i,i-2,MOD);

	f[0]=finv[0]=1;
	repi(i,1,f.size()){
		f[i]=(ll)f[i-1]*i%MOD;
		finv[i]=mod_inverse(f[i],MOD);
	}

	int T; cin>>T;
	rep(_,T){
		int n; cin>>n;
		vi a(n);
		rep(i,n) cin>>a[i];
		rep(i,n) a[i]--;
		cout<<solve(a)<<endl;
	}
}
