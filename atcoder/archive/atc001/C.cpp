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
constexpr double PI=acos(-1);

using Complex=complex<double>;
constexpr Complex I(0,1);

void FFT(vector<Complex>& a,bool inverse=false)
{
	int n=a.size();
	for(int i=0;i<n;i++){
		int j=0;
		for(int k=0;(1<<k)<n;k++)
			(j<<=1)|=i>>k&1;
		if(i<j)
			swap(a[i],a[j]);
	}
	int sign=inverse?1:-1;
	for(int m=2;m<=n;m*=2){
		double theta=sign*2*PI/m;
		for(int i=0;i<m/2;i++){
			Complex wi=exp(I*theta*(double)i);
			for(int j=0;j<n;j+=m){
				Complex &x=a[i+j],&y=a[i+m/2+j];
				tie(x,y)=mt(x+y*wi,x-y*wi);
			}
		}
	}
	if(inverse)
		for(int i=0;i<n;i++)
			a[i]/=n;
}

template<unsigned M>
struct modint{
	unsigned val;
	modint(unsigned x):val((x%M+M)%M){}
	modint pow(unsigned r)const{
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
};

template<unsigned M> bool operator==(const modint<M>& a,const modint<M>& b){return a.val==b.val;}
template<unsigned M> bool operator!=(const modint<M>& a,const modint<M>& b){return a.val!=b.val;}
template<unsigned M> modint<M> operator+(modint<M> a,const modint<M>& b){a+=b; return a;}
template<unsigned M> modint<M> operator-(modint<M> a,const modint<M>& b){a-=b; return a;}
template<unsigned M> modint<M> operator*(modint<M> a,const modint<M>& b){a*=b; return a;}
template<unsigned M> modint<M> operator/(modint<M> a,const modint<M>& b){a/=b; return a;}
template<unsigned M> ostream& operator<<(ostream& os,const modint<M>& x){return os<<x.val;}

template<unsigned M>
void NTT(vector<modint<M>>& a,unsigned root,bool inverse=false){
	int n=a.size();
	for(int i=0;i<n;i++){
		int j=0;
		for(int k=0;(1<<k)<n;k++)
			(j<<=1)|=i>>k&1;
		if(i<j)
			swap(a[i],a[j]);
	}
	for(int m=2;m<=n;m*=2){
		modint<M> r=modint<M>(root).pow((M-1)/m);
		for(int i=0;i<m/2;i++){
			modint<M> wi=r.pow(i);
			if(inverse) wi=wi.inv();
			for(int j=0;j<n;j+=m){
				modint<M> &x=a[i+j],&y=a[i+m/2+j];
				tie(x,y)=mt(x+y*wi,x-y*wi);
			}
		}
	}
	if(inverse)
		for(int i=0;i<n;i++)
			a[i]/=n;
}

vi solve_by_fft(int n,vi a,vi b)
{
	int m=1;
	for(;m<=2*n;m*=2);

	vector<Complex> f(m),g(m),h(m);
	rep(i,n+1) f[i]=a[i],g[i]=b[i];

	FFT(f);
	FFT(g);
	rep(i,m) h[i]=f[i]*g[i];
	FFT(h,true);

	vi res;
	repi(i,1,2*n+1)
		res.push_back(real(h[i])+0.5);
	return res;
}

vi solve_by_ntt(int n,vi a,vi b)
{
	int m=1;
	for(;m<=2*n;m*=2);

	constexpr unsigned mod=1224736769,root=3;
	vector<modint<mod>> f(m,0),g(m,0),h(m,0);
	rep(i,n+1) f[i]=a[i],g[i]=b[i];

	NTT(f,root);
	NTT(g,root);

	rep(i,m) h[i]=f[i]*g[i];
	NTT(h,root,true);

	vi res;
	repi(i,1,2*n+1) res.push_back(h[i].val);
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi a(n+1),b(n+1);
		rep(i,n) cin>>a[i+1]>>b[i+1];

		for(int x:solve_by_fft(n,a,b))
			cout<<x<<endl;
		//for(int x:solve_by_ntt(n,a,b))
		//	cout<<x<<endl;
	}
}
