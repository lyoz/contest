#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vvvl=vector<vvl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vvvd=vector<vvd>;
using vs=vector<string>;
using vvs=vector<vs>;

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

ll calc(const vl& sum,int x,int lb,int rb)
{
	int n=sum.size()-1;
	ll ares=0,bres=0;
	if(lb<x){
		int r=min(rb,x); // [r,...,x) is free
		r+=(x-r)/2;
		if(chmax(bres,sum[r]))
			ares=sum[n]-sum[r];
	}
	if(x<rb-1){
		int l=max(lb,x+1); // [x+1,...,l) is free
		l-=(l-(x+1))/2;
		if(chmax(bres,sum[n]-sum[l]))
			ares=sum[l];
	}
	return ares;
}

void solve()
{
	int n; cin>>n;
	vi ss(n);
	rep(i,n) cin>>ss[i];
	int la,ra,lb,rb; cin>>la>>ra>>lb>>rb; la--,lb--;

	vl sum(n+1);
	rep(i,n) sum[i+1]=sum[i]+ss[i];
	ll res=0;
	repi(i,la,ra)
		chmax(res,calc(sum,i,lb,rb));
	cout<<res<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(_,tc){
		cout<<"Case #"<<_+1<<": ";
		solve();
	}
}
