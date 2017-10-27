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

int calc(vs ops,vi xs,int a)
{
	rep(i,ops.size()){
		if(ops[i]=="&") a&=xs[i];
		if(ops[i]=="^") a^=xs[i];
		if(ops[i]=="|") a|=xs[i];
	}
	return a;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vs ops(n);
		vi xs(n);
		rep(i,n) cin>>ops[i]>>xs[i];

		constexpr int m=10;
		int z=calc(ops,xs,0);
		int o=calc(ops,xs,(1<<m)-1);

		// ((x&a)^b)|c
		int a=0,b=0,c=0;
		rep(i,m){
			int zb=z>>i&1,ob=o>>i&1;
			if(zb==0&&ob==0) continue;
			if(zb==1&&ob==0) a|=1<<i,b|=1<<i;
			if(zb==0&&ob==1) a|=1<<i;
			if(zb==1&&ob==1) c|=1<<i;
		}
		cout<<3<<endl;
		cout<<"& "<<a<<endl;
		cout<<"^ "<<b<<endl;
		cout<<"| "<<c<<endl;
	}
}
