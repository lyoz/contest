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

constexpr ll INF=1e10;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int solve(int k,vi cs)
{
	ll inc=k,dec=k;
	{  // inc
		ll lo=0,hi=INF;
		while(lo<hi){
			ll mi=(lo+hi)/2,sum=0;
			for(int c:cs) sum+=max<ll>(mi-c,0);
			if(sum>k)
				hi=mi;
			else
				lo=mi+1;
		}
		int x=lo-1;
		for(int& c:cs) if(c<x){
			inc-=x-c;
			c=x;
		}
	}
	{  // dec
		ll lo=0,hi=INF;
		while(lo<hi){
			ll mi=(lo+hi)/2,sum=0;
			for(int c:cs) sum+=max<ll>(c-mi,0);
			if(sum<=k)
				hi=mi;
			else
				lo=mi+1;
		}
		int x=lo;
		for(int& c:cs) if(c>x){
			dec-=c-x;
			c=x;
		}
	}
	
	map<int,int> f;
	for(int& c:cs) f[c]++;
	rep(_,inc){
		auto it=begin(f);
		f[it->first+1]++;
		if(--it->second==0)
			f.erase(it);
	}
	rep(_,dec){
		auto it=--end(f);
		f[it->first-1]++;
		if(--it->second==0)
			f.erase(it);
	}
	return (--end(f))->first-begin(f)->first;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	for(int n,k;cin>>n>>k&&n|k;){
		vi cs(n);
		rep(i,n) cin>>cs[i];
		cout<<solve(k,cs)<<endl;
	}
}
