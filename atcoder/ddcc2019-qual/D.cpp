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

bool input(vi& a)
{
	repi(i,2,31)
		cin>>a[i];
	return !cin.eof();
}

ll ExtendedGCD(ll a,ll b,ll& x,ll& y)
{
	x=1,y=0;
	for(ll u=0,v=1;b;){
		ll t=a/b;
		swap(a-=b*t,b);
		swap(x-=u*t,u);
		swap(y-=v*t,v);
	}
	return a;
}

ll ModMul(ll a,ll b,ll m)
{
	ll res=a*b-ll(1.0l*a*b/m)*m;
	return (res%m+m)%m;
}

ll CRT(ll a1,ll n1,ll a2,ll n2)
{
	ll x,y;
	ExtendedGCD(n1,n2,x,y);
	ll m=n1*n2;
	ll t1=ModMul(ModMul(a1,n2,m),y,m);
	ll t2=ModMul(ModMul(a2,n1,m),x,m);
	return (t1+t2)%m;
}

ll CRT(vl& as,vl& ns)
{
	ll a=as[0],n=ns[0];
	repi(i,1,as.size())
		tie(a,n)=mt(CRT(a,n,as[i],ns[i]),n*ns[i]);
	return a;
}

bool verify(vi a,ll res)
{
	if(res<0 || 1000000000000LL<res)
		return false;
	repi(i,2,a.size()){
		int sum=0;
		for(ll x=res;x;x/=i)
			sum+=x%i;
		if(sum!=a[i])
			return false;
	}
	return true;
}

string solve(vi a)
{
	vi is={16,27,25,7,11,13,17,19,23,29};
	for(int& i:is) i++;
	vl as,ns;
	for(int i:is){
		as.push_back(a[i]);
		ns.push_back(i-1);
	}
	ll res=CRT(as,ns);
	return verify(a,res)?to_string(res):"invalid";
}


int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(vi a(31);input(a);)
		cout<<solve(a)<<endl;
}
