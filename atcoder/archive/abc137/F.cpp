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

struct ModOperation{
	int p;
	vi fact,ifact;
	vvi pmemo,cmemo;
	ModOperation(int p):p(p),fact(p),ifact(p),pmemo(p,vi(p,-1)),cmemo(p,vi(p,-1)){
		fact.resize(p);
		fact[0]=1;
		repi(i,1,p)
			fact[i]=ll(fact[i-1]*i)%p;
		ifact.resize(p);
		rep(i,p)
			ifact[i]=ModInverse(fact[i],p);

		rep(i,p){
			pmemo[i][0]=1;
			repi(j,1,p)
				pmemo[i][j]=(ll)pmemo[i][j-1]*i%p;
		}

		rep(i,p)
			rep(j,i+1)
				cmemo[i][j]=(ll)fact[i]*ifact[i-j]%p*ifact[j]%p;
	}
	int pow(int a,int r){
		return pmemo[a][r];
	}
	int choose(int n,int r){
		return cmemo[n][r];
	}
};

// (1-pow(x-i,p-1)) mod p
vi calc(ModOperation& mo,int i,int p)
{
	vi c(p);
	rep(j,p){
		ll t=ll(j%2==0?1:-1)*mo.choose(p-1,j)*mo.pow(i,p-1-j);
		c[j]=(t%p+p)%p;
	}
	c[0]=(1-c[0]+p)%p;
	repi(j,1,p)
		c[j]=(-c[j]+p)%p;
	return c;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int p;cin>>p&&p;){
		vi a(p);
		rep(i,p) cin>>a[i];

		ModOperation mo(p);

		vi b(p);
		rep(i,p) if(a[i]){
			vi c=calc(mo,i,p);
			rep(j,p)
				(b[j]+=c[j])%=p;
		}

		rep(i,p)
			cout<<b[i]<<"\n "[i+1<p];
	}
}
