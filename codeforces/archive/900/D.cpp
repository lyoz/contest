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

ll dfs(int rest,int g,vi& memo)
{
	if(rest==0){
		//if(g==1) dump(memo);
		return g==1;
	}
	ll res=0;
	for(int i=1;i<=rest;i++){
		memo.push_back(i);
		res+=dfs(rest-i,__gcd(i,g),memo);
		memo.pop_back();
	}
	return res;
}

int solve_naive(int x,int y)
{
	if(y%x) return 0;
	tie(x,y)=mt(1,y/x);
	ll res=0;
	for(int i=1;i<=y;i++){
		vi memo={i};
		res+=dfs(y-i,i,memo);
	}
	return res;
}

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

vector<tuple<int,int>> get_prime_factors(int n)
{
	vector<tuple<int,int>> res;
	for(int i=2;i*i<=n;i++){
		int cnt=0;
		while(n%i==0){
			n/=i;
			cnt++;
		}
		if(cnt)
			res.emplace_back(i,cnt);
	}
	if(n!=1)
		res.emplace_back(n,1);
	return res;
}

vi get_divisors(int n)
{
	vi res;
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			res.push_back(i);
			if(n/i>i)
				res.push_back(n/i);
		}
	}
	return res;
}

int moebius(int n)
{
	int res=1;
	for(auto t:get_prime_factors(n)){
		if(get<1>(t)>=2) res*=0;
		res*=-1;
	}
	return res;
}

int solve(int x,int y)
{
	if(y%x) return 0;
	tie(x,y)=mt(1,y/x);

	// http://oeis.org/A000740
	mint res=0;
	for(int d:get_divisors(y)){
		int m=moebius(y/d);
		if(m==1)
			res+=mint(2).pow(d-1);
		else if(m==-1)
			res-=mint(2).pow(d-1);
	}
	return res.val;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int x,y;cin>>x>>y&&x|y;){
		cout<<solve(x,y)<<endl;
	}
}
