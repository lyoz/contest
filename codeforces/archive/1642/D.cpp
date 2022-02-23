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

void solve(vi a)
{
	int n=a.size();

	{
		map<int,int> f;
		rep(i,n) f[a[i]]++;
		for(auto [k,v]:f)
			if(v&1){
				cout<<-1<<endl;
				return;
			}
	}

	vector<tuple<int,int>> opes;
	vi lens;
	for(int i=0,j=0;i<a.size();){
		for(j=i+1;j<a.size();j++)
			if(a[j]==a[i])
				break;
		assert(a[i]==a[j]);
		int m=j-i;
		vi b;
		repi(k,1,m){
			b.push_back(a[i+k]);
			opes.emplace_back(j+k,a[i+k]);
		}
		peri(k,1,m)
			b.push_back(a[i+k]);
		a.insert(begin(a)+j+1,all(b));
		i+=2*m;
		lens.push_back(2*m);
	}

	cout<<opes.size()<<endl;
	for(auto [p,c]:opes)
		cout<<p<<' '<<c<<endl;
	cout<<lens.size()<<endl;
	for(int len:lens)
		cout<<len<<endl;
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
		vi a(n);
		rep(i,n) cin>>a[i];
		solve(a);
	}
}
