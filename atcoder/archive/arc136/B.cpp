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

void solve(vi a,vi b)
{
	int n=a.size();
	{
		map<int,int> ma,mb;
		for(int c:a) ma[c]++;
		for(int c:b) mb[c]++;
		if(ma!=mb){
			cout<<"No"<<endl;
			return;
		}
		for(auto [k,v]:ma){
			if(v>=2){
				cout<<"Yes"<<endl;
				return;
			}
		}
	}
	rep(i,n-2){
		repi(j,i,n) if(a[j]==b[i]){
			int k=j;
			for(;k-2>=i;k-=2)
				tie(a[k-2],a[k-1],a[k])=mt(a[k],a[k-2],a[k-1]);
			for(;k-1>=i;k--)
				tie(a[k-1],a[k],a[k+1])=mt(a[k],a[k+1],a[k-1]);
			break;
		}
	}
	if(a[n-2]==b[n-2]&&a[n-1]==b[n-1])
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi a(n),b(n);
		rep(i,n) cin>>a[i];
		rep(i,n) cin>>b[i];
		solve(a,b);
	}
}
