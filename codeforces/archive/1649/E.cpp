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

struct FenwickTree{
	vector<mint> data;
	FenwickTree(int n):data(n+1){}
	void Add(int i,mint x){
		for(i++;i<data.size();i+=i&-i)
			data[i]+=x;
	}
	mint Sum(int i){
		mint res=0;
		for(;i;i-=i&-i)
			res+=data[i];
		return res;
	}
	mint Sum(int i,int j){
		return Sum(j)-Sum(i);
	}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	vector<mint> facts(200001);
	facts[0]=1;
	repi(i,1,facts.size())
		facts[i]=i*facts[i-1];

	for(int m,n;cin>>m>>n&&m|n;){
		vi s(m),t(n);
		rep(i,m) cin>>s[i];
		rep(i,n) cin>>t[i];

		map<int,int> freq;
		rep(i,m)
			freq[s[i]]++;

		mint combi=facts[m];
		FenwickTree ft(200001);
		for(auto [k,v]:freq){
			combi/=facts[v];
			ft.Add(k,v);
		}

		mint res=0;
		for(int i=0;;i++){
			if(i==m||i==n){
				if(i==m&&m<n)
					res+=1;
				break;
			}
			mint add=ft.Sum(t[i])/(m-i);
			res+=combi*add;
			if(freq[t[i]]==0)
				break;
			combi/=mint(m-i)/freq[t[i]];
			freq[t[i]]--;
			ft.Add(t[i],-1);
		}
		cout<<res<<endl;
	}
}
