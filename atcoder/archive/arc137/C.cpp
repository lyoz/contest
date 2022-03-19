#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vvvl=vector<vvl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vvvd=vector<vvd>;
using vs=vector<string>;
using vvs=vector<vs>;

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

vi encode(vi a)
{
	return {rbegin(a),rend(a)};
}

int solve(vi a,map<vi,int>& memo)
{
	if(memo.count(encode(a)))
		return memo[encode(a)];
	set<int> gs;
	per(i,a.size()) if(a[i]){
		rep(j,i) if(a[j]==0){
			a[j]=1,a[i]=0;
			gs.insert(solve(a,memo));
			a[j]=0,a[i]=1;
		}
		break;
	}
	for(int i=0;;i++)
		if(!gs.count(i))
			return memo[encode(a)]=i;
	return -1;
}

void test()
{
	map<vi,int> memo;
	int n=9;
	repi(s,1,1<<n){
		if(__builtin_popcount(s)!=3)
			continue;
		vi a(n);
		rep(i,n)
			a[i]=s>>i&1;
		solve(a,memo);
	}
	for(auto [k,v]:memo)
		dump(k,v);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];

		sort(all(a));
		// 大きい数2つが隣接し,残りの空きマスが偶数個なら先手必敗
		if(a[n-1]-a[n-2]==1&&(a[n-2]-(n-2))%2==0)
			cout<<"Bob"<<endl;
		else
			cout<<"Alice"<<endl;
	}
}
