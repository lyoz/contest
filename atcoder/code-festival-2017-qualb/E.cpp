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

int ncr(int n,int r)
{
	static int memo[2001][2001];
	int& res=memo[n][r];
	if(res==0){
		if(r==0||r==n)
			res=1;
		else
			res=(ncr(n-1,r-1)+ncr(n-1,r))%MOD;
	}
	return res;
}

int ncrsum(int n,int r)
{
	static int memo[2001][2001];
	int& res=memo[n][r];
	if(res==0){
		if(r>0)
			res=ncrsum(n,r-1);
		(res+=ncr(n,r))%=MOD;
	}
	return res;
}

int calc(int p,int q,vvi& memo)
{
	int& res=memo[p][q];
	if(res==-1){
		if(p==0||q==0)
			res=1;
		else
			res=(calc(p-1,q,memo)+ncrsum(q-1,min(p,q-1)))%MOD;
	}
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int a,b;cin>>a>>b&&a|b;){
		ll res=0;
		vvi memo(a+1,vi(b+1,-1));
		for(int t=0;t<=a;t++){
			for(int p=0;p<=t;p++){
				int q=t-p;
				if(b<=q) continue;
				assert(0<=p&&p<=a&&0<=q&&q<b);
				(res+=(ll)ncr(b-1,t-p)*calc(p,q,memo))%=MOD;
			}
		}
		cout<<res<<endl;
	}
}
