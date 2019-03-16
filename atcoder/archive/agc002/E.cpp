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

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

bool win(vi a,map<vi,bool>& memo)
{
	sort(all(a));
	if(memo.count(a)) return memo[a];
	int n=a.size();
	if(count(all(a),0)==n) return memo[a]=true;
	vi b=a; b[n-1]=0;
	if(!win(b,memo)) return memo[a]=true;
	rep(i,n) b[i]=max(a[i]-1,0);
	if(!win(b,memo)) return memo[a]=true;
	return memo[a]=false;
}

bool solve_small(vi a)
{
	map<vi,bool> memo;
	return win(a,memo);
}

int main()
{
	for(int n;cin>>n && n;){
		vi a(n);
		rep(i,n) cin>>a[i];
		sort(all(a),greater<int>());
		int i=0;
		while(i<n && i<a[i]) i++;
		i--;
		int x=a[i]-i,y=find_if(all(a),[&](int x){return x<=i;})-begin(a)-i;
		cout<<(x&y&1?"Second":"First")<<endl;
	}
}
