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
constexpr int MOD=998244353;
constexpr double EPS=1e-9;

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
		unsigned x=1;
		for(unsigned a=val,b=M,u=0;b;){
			ll t=a/b;
			swap(a-=b*t,b);
			swap(x-=u*t,u);
		}
		return x;
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

using mint=modint<MOD>;

int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi xs(n),ys(n);
		rep(i,n) cin>>xs[i]>>ys[i];

		mint res=mint(2).pow(n)-mint(1+n);

		rep(i,n) repi(j,i+1,n){
			int x=xs[j]-xs[i],y=ys[j]-ys[i];
			vi is;
			rep(k,n) if(k!=i&&k!=j){
				int x2=xs[k]-xs[i],y2=ys[k]-ys[i];
				if(det(x,y,x2,y2)==0)
					is.push_back(k);
			}
			if(is.empty()||j<is[0]){
				int m=2+is.size();
				res-=mint(2).pow(m)-mint(1+m);
			}
		}

		cout<<res<<endl;
	}
}
