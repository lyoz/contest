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
constexpr int MOD=998244353;
constexpr double EPS=1e-9;

template<uint M>
struct modint{
	uint val;
	modint(ll x=0):val((x%M+M)%M){}
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
	modint& operator+=(const modint& x)&{if((val+=x.val)>=M) val-=M; return *this;}
	modint& operator-=(const modint& x)&{if((val+=M-x.val)>=M) val-=M; return *this;}
	modint& operator*=(const modint& x)&{val=(ll)val*x.val%M; return *this;}
	modint& operator/=(const modint& x)&{val=(ll)val*x.inv().val%M; return *this;}
	explicit operator uint()const{return val;}
	friend bool operator==(const modint& a,const modint& b){return a.val==b.val;}
	friend bool operator!=(const modint& a,const modint& b){return a.val!=b.val;}
	friend modint operator+(modint a,const modint& b){a+=b; return a;}
	friend modint operator-(modint a,const modint& b){a-=b; return a;}
	friend modint operator*(modint a,const modint& b){a*=b; return a;}
	friend modint operator/(modint a,const modint& b){a/=b; return a;}
	friend ostream& operator<<(ostream& os,const modint& x){return os<<x.val;}
};

using mint=modint<MOD>;

mint ncr(int n,int r)
{
	static vector memo(2501,vector<mint>(2501));
	if(r<0||n<r)
		return 0;
	if(memo[n][r]==0){
		if(r==0||r==n)
			memo[n][r]=1;
		else
			memo[n][r]=ncr(n-1,r-1)+ncr(n-1,r);
	}
	return memo[n][r];
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w,a,b;cin>>h>>w>>a>>b&&h|w|a|b;){
		vector dp(h+1,vector<mint>(w+1));
		rep(ah,h+1) rep(aw,w+1)
			rep(i,ah+1) rep(j,aw+1)
				dp[ah][aw]+=ncr(i*j,a)*ncr(ah,i)*ncr(aw,j)*(((ah+aw)-(i+j))%2?-1:1);
		mint res=0;
		rep(ah,h+1) rep(aw,w+1){
			int bh=h-ah,bw=w-aw;
			res+=dp[ah][aw]*ncr(h,ah)*ncr(w,aw)*ncr(bh*bw,b);
		}
		cout<<res<<endl;
	}
}
