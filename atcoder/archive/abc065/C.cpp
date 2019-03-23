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

template<unsigned M>
struct mint{
	unsigned val;
	mint(unsigned x):val((x%M+M)%M){}
	mint inv()const{
		unsigned x=1;
		for(unsigned a=val,b=M,u=0;b;){
			ll t=a/b;
			swap(a-=b*t,b);
			swap(x-=u*t,u);
		}
		return mint(x+M);
	}
	mint& operator+=(const mint& x)&{if((val+=x.val)>=M) val-=M; return *this;}
	mint& operator-=(const mint& x)&{if((val+=M-x.val)>=M) val-=M; return *this;}
	mint& operator*=(const mint& x)&{val=(ll)val*x.val%M; return *this;}
	mint& operator/=(const mint& x)&{val=(ll)val*x.inv().val%M; return *this;}
};

template<unsigned M> bool operator==(const mint<M>& a,const mint<M>& b){return a.val==b.val;}
template<unsigned M> bool operator!=(const mint<M>& a,const mint<M>& b){return a.val!=b.val;}
template<unsigned M> mint<M> operator+(mint<M> a,const mint<M>& b){a+=b; return a;}
template<unsigned M> mint<M> operator-(mint<M> a,const mint<M>& b){a-=b; return a;}
template<unsigned M> mint<M> operator*(mint<M> a,const mint<M>& b){a*=b; return a;}
template<unsigned M> mint<M> operator/(mint<M> a,const mint<M>& b){a/=b; return a;}
template<unsigned M> ostream& operator<<(ostream& os,const mint<M>& x){return os<<x.val;}

int main()
{
	for(int a,b;cin>>a>>b&&a|b;){
		if(a>b)
			swap(a,b);
		if(b-a>1)
			cout<<0<<endl;
		else{
			mint<MOD> res=1;
			rep(i,a) res*=a-i;
			rep(i,b) res*=b-i;
			if(a==b) res*=2;
			cout<<res<<endl;
		}
	}
}
