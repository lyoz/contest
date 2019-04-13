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

template<uint M>
struct modint{
	uint val;
	modint(uint x=0):val((x%M+M)%M){}
	modint pow(uint r)const{
		ll a=val,x=1;
		for(;r;r>>=1){
			if(r&1)
				(x*=a)%=M;
			(a*=a)%=M;
		}
		return x;
	}
	modint inv()const{
		ll x=1;
		for(ll a=val,b=M,u=0;b;){
			ll t=a/b;
			swap(a-=b*t,b);
			swap(x-=u*t,u);
		}
		return (x+M)%M;
	}
	modint& operator=(const modint& x)&{val=x.val; return *this;}
	modint& operator+=(const modint& x)&{if((val+=x.val)>=M) val-=M; return *this;}
	modint& operator-=(const modint& x)&{if((val+=M-x.val)>=M) val-=M; return *this;}
	modint& operator*=(const modint& x)&{val=(ll)val*x.val%M; return *this;}
	modint& operator/=(const modint& x)&{val=(ll)val*x.inv().val%M; return *this;}
	explicit operator uint()const{return val;}
};

template<uint M> bool operator==(const modint<M>& a,const modint<M>& b){return a.val==b.val;}
template<uint M> bool operator!=(const modint<M>& a,const modint<M>& b){return a.val!=b.val;}
template<uint M> modint<M> operator+(modint<M> a,const modint<M>& b){a+=b; return a;}
template<uint M> modint<M> operator-(modint<M> a,const modint<M>& b){a-=b; return a;}
template<uint M> modint<M> operator*(modint<M> a,const modint<M>& b){a*=b; return a;}
template<uint M> modint<M> operator/(modint<M> a,const modint<M>& b){a/=b; return a;}
template<uint M> ostream& operator<<(ostream& os,const modint<M>& x){return os<<x.val;}

using mint=modint<MOD>;

template<unsigned M>
void FWHT(vector<modint<M>>& a,bool inverse=false)
{
	int n=a.size();
	for(int m=2;m<=n;m*=2)
		for(int i=0;i<m/2;i++)
			for(int j=0;j<n;j+=m){
				modint<M> &x=a[i+j],&y=a[i+m/2+j];
				tie(x,y)=mt(x+y,x-y);
			}
	if(inverse)
		rep(i,n)
			a[i]/=n;
}

inline int clz(uint x)
{
	int i=0;
	if(!(x&0xffff0000)) i+=16,x<<=16;
	if(!(x&0xff000000)) i+=8,x<<=8;
	if(!(x&0xf0000000)) i+=4,x<<=4;
	if(!(x&0xc0000000)) i+=2,x<<=2;
	if(!(x&0x80000000)) i+=1,x<<=1;
	return i+!x;
}

template<unsigned M>
void Zeta(vector<modint<M>>& f)
{
	int n=32-clz(f.size()-1);
	rep(i,n) rep(s,1<<n)
		//if(s>>i&1) f[s]+=f[s^1<<i];
		if(s>>i&1) f[s^1<<i]+=f[s];
}

template<unsigned M>
void Moebius(vector<modint<M>>& f)
{
	int n=32-clz(f.size()-1);
	rep(i,n) rep(s,1<<n)
		//if(s>>i&1) f[s]-=f[s^1<<i];
		if(s>>i&1) f[s^1<<i]-=f[s];
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi s(n);
		rep(i,n) cin>>s[i];

		const int m=1<<17;

		vector<mint> cnt(m);
		rep(i,n) cnt[s[i]]+=1;

		vector<mint> cnt_or(m);
		rep(i,m)
			for(int j=i;;j=(j-1)&i){
				int k=i^j;
				cnt_or[i]+=mint(cnt[j])*mint(cnt[k]);
				if(!j) break;
			}

		vector<mint> cnt_xor=cnt;
		FWHT(cnt_xor);
		for(auto& x:cnt_xor) x*=x;
		FWHT(cnt_xor,true);

		vector<mint> f(m); f[0]=0,f[1]=1;
		repi(i,2,m) f[i]=f[i-2]+f[i-1];

		vector<mint> sab(m),sc(m),sde(m);
		rep(i,m){
			sab[i]=f[i]*cnt_or[i];
			sc[i]=f[i]*cnt[i];
			sde[i]=f[i]*cnt_xor[i];
		}

		Zeta(sab); Zeta(sc); Zeta(sde);
		vector<mint> sabcde(m);
		rep(i,m) sabcde[i]=sab[i]*sc[i]*sde[i];
		Moebius(sabcde);

		mint res=0;
		for(int i=0;(1<<i)<m;i++) res+=sabcde[1<<i];
		cout<<res<<endl;
	}
}
