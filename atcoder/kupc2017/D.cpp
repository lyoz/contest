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

void dfs(int n,int m,vvi& a,int i,int j,vector<vvi>& res)
{
	if(i==n){
		cout<<"!!!found!!!"<<endl;
		rep(i,n) cout<<a[i]<<endl;
		res.push_back(a);
		return;
	}
	rep(k,m){
		a[i][j]=k;
		bool ok=true;
		ok&=!(2<=i&&set<int>({a[i-2][j],a[i-1][j],a[i][j]}).size()<2);
		ok&=!(2<=j&&set<int>({a[i][j-2],a[i][j-1],a[i][j]}).size()<2);
		ok&=!(2<=i&&2<=j&&set<int>({a[i-2][j-2],a[i-1][j-1],a[i][j]}).size()<2);
		ok&=!(2<=i&&j+2<n&&set<int>({a[i-2][j+2],a[i-1][j+1],a[i][j]}).size()<2);
		if(ok) dfs(n,m,a,i+(j+1)/n,(j+1)%n,res);
	}
}

void test(int n)
{
	for(int m=1;;m++){
		vector<vvi> res;
		vvi a(n,vi(n));
		dfs(n,m,a,0,0,res);
		if(res.size()){
			dump(n,m,res.size());
			break;
		}
	}
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		//test(n);
		switch(n){
		case 1: cout<<"1 1"<<endl; break;
		case 2: cout<<"1 1"<<endl; break;
		case 3: cout<<"2 32"<<endl; break;
		case 4: cout<<"2 18"<<endl; break;
		default: cout<<"2 8"<<endl;
		}
	}
}
