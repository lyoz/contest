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

tuple<ll,ll,ll> solve_set1(ll l,ll r)
{
	ll cnt=0;
	for(int i=1;max(l,r)>=i;i++,cnt++){
		if(l>=r)
			l-=i;
		else
			r-=i;
	}
	//cout<<cnt<<' '<<l<<' '<<r<<endl;
	return {cnt,l,r};
}

ll calc(ll& x,ll k0)
{
	ll lo=0,hi=1.5e9;
	while(lo<hi){
		ll mi=(lo+hi)/2;
		if(k0*mi+(mi-1)*mi>x)
			hi=mi;
		else
			lo=mi+1;
	}
	ll n=lo-1;
	x-=k0*n+(n-1)*n;
	return n;
}

tuple<ll,ll,ll> solve_set2(ll l,ll r)
{
	ll k=-1;
	{
		ll d=abs(l-r);
		ll lo=0,hi=1.5e9;
		while(lo<hi){
			ll mi=(lo+hi)/2;
			if(mi*(mi+1)/2>d)
				hi=mi;
			else
				lo=mi+1;
		}
		k=lo-1;
	}

	if(l>=r)
		l-=k*(k+1)/2;
	else
		r-=k*(k+1)/2;

	ll kl,kr;
	if(l>=r){
		kl=calc(l,k+1);
		kr=calc(r,k+2);
	}
	else{
		kr=calc(r,k+1);
		kl=calc(l,k+2);
	}

	return {k+kl+kr,l,r};
}

void solve()
{
	ll l,r; cin>>l>>r;
	//solve_set1(l,r);

	ll rn,rl,rr; tie(rn,rl,rr)=solve_set2(l,r);
	cout<<rn<<' '<<rl<<' '<<rr<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}
