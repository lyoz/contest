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

struct ConvexHullTrick{
	vl as,bs;
	// 傾きaは単調非増加でなければならない
	void AddLine(ll a,ll b){
		while(as.size()>=2){
			ll a1=as[as.size()-2],b1=bs[bs.size()-2];
			ll a2=as[as.size()-1],b2=bs[bs.size()-1];
			if((a1-a2)*(b1-b)<(a1-a)*(b1-b2)) break;
			as.pop_back(); bs.pop_back();
		}
		as.push_back(a); bs.push_back(b);
	}
	// 最小のax+bを返す
	ll Find(ll x){
		int lo=0,hi=as.size()-1;
		while(lo<hi){
			int mi=(lo+hi)/2;
			if(F(mi,x)<=F(mi+1,x))
				hi=mi;
			else
				lo=mi+1;
		}
		return F(lo,x);
	}
	ll F(int i,ll x){
		return as[i]*x+bs[i];
	}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vl a(n);
		rep(i,n) cin>>a[i];

		vl s(n+1);
		rep(i,n) s[i+1]=s[i]+a[i];

		ll res=0;
		{
			ConvexHullTrick cht;
			per(i,n){
				cht.AddLine(i,s[i+1]);
				res=max(res,-a[i]*i+s[i+1]-cht.Find(-a[i]));
			}
		}
		{
			ConvexHullTrick cht;
			repi(i,1,n){
				cht.AddLine(-(i-1),s[i-1]);
				res=max(res,-a[i]*i+s[i]-cht.Find(a[i]));
			}
		}
		rep(i,n) res+=(i+1)*a[i];
		cout<<res<<endl;
	}
}
