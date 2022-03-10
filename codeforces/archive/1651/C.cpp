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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

ll nearest(const vl& a,ll x)
{
	int n=a.size();
	int i=lower_bound(all(a),x)-begin(a);
	ll res=INF;
	if(i<n) chmin(res,a[i]-x);
	if(i>0) chmin(res,x-a[i-1]);
	return res;
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
		int n; cin>>n;
		vl a(n),b(n);
		rep(i,n) cin>>a[i];
		rep(i,n) cin>>b[i];

		ll al=a[0],ar=a[n-1],bl=b[0],br=b[n-1];
		sort(all(a));
		sort(all(b));
		ll res=INF;
		chmin(res,nearest(b,al)+nearest(b,ar)+nearest(a,bl)+nearest(a,br));
		chmin(res,abs(bl-al)+nearest(b,ar)+nearest(a,br));
		chmin(res,abs(br-al)+nearest(b,ar)+nearest(a,bl));
		chmin(res,abs(bl-ar)+nearest(b,al)+nearest(a,br));
		chmin(res,abs(br-ar)+nearest(b,al)+nearest(a,bl));
		chmin(res,abs(bl-al)+abs(br-ar));
		chmin(res,abs(br-al)+abs(bl-ar));
		cout<<res<<endl;
	}
}
