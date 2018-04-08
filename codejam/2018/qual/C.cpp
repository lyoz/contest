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

tuple<int,int> print(int i,int j)
{
	cout<<i+2<<' '<<j+2<<endl;
	cin>>i>>j;
	return {i-2,j-2};
	//i+=rand()%3-1;
	//j+=rand()%3-1;
	//return {i,j};
}

int count(const vvi& grid,int i,int j)
{
	int res=0;
	for(int di=-1;di<=1;di++)
		for(int dj=-1;dj<=1;dj++)
			res+=grid[i+di][j+dj];
	return res;
}

void solve()
{
	int s; cin>>s;
	int n=ceil(sqrt(s));

	vvi grid(n,vi(n));
	for(;;){
		//{
		//	int cnt=0;
		//	rep(i,n) rep(j,n)
		//		cnt+=grid[i][j];
		//	if(cnt==n*n)
		//		break;
		//}
		vector<tuple<int,int,int>> ts;
		repi(i,1,n-1) repi(j,1,n-1)
			ts.emplace_back(count(grid,i,j),i,j);
		int i,j; tie(ignore,i,j)=*min_element(all(ts));
		tie(i,j)=print(i,j);
		if(i<0&&j<0) break;
		grid[i][j]=1;
	}
}

int main()
{
	int tc; cin>>tc;
	rep(i,tc)
		solve();
}
