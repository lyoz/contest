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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];
		int q; cin>>q;
		vector<tuple<int,int,int>> qs;
		rep(i,q){
			int l,r; cin>>l>>r; l--;
			qs.emplace_back(i,l,r);
		}

		// Mo
		int sqrt_n=sqrt(n-1)+1;
		sort(all(qs),[&](auto a,auto b){
			auto [_a,al,ar]=a;
			auto [_b,bl,br]=b;
			return mt(al/sqrt_n,ar/sqrt_n)<mt(bl/sqrt_n,br/sqrt_n);
		});
		int cl=0,cr=0,cc=0;
		vi f(*max_element(all(a))+1);
		vi res(q);
		for(auto [i,l,r]:qs){
			for(;cl-1>=l;cl--)
				if(++f[a[cl-1]]%2==0)
					cc++;
			for(;cr<r;cr++)
				if(++f[a[cr]]%2==0)
					cc++;
			for(;cl<l;cl++)
				if(--f[a[cl]]%2)
					cc--;
			for(;cr-1>=r;cr--)
				if(--f[a[cr-1]]%2)
					cc--;
			res[i]=cc;
		}
		for(int x:res)
			cout<<x<<endl;
	}
}
