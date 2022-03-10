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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi xs(n),ys(n);
		rep(i,n) cin>>xs[i]>>ys[i];

		set<tuple<int,int>> given;
		rep(i,n)
			given.emplace(xs[i],ys[i]);

		constexpr int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
		map<tuple<int,int>,tuple<int,int>> nearest;
		queue<tuple<int,int>> q;
		rep(i,n) rep(k,4){
			int x=xs[i]+dx[k],y=ys[i]+dy[k];
			if(!given.count({x,y})){
				nearest[{x,y}]={x,y};
				q.emplace(x,y);
			}
		}
		while(q.size()){
			auto [cx,cy]=q.front(); q.pop();
			auto [nx,ny]=nearest[{cx,cy}];
			rep(k,4){
				int x=cx+dx[k],y=cy+dy[i];
				if(given.count({x,y})&&!nearest.count({x,y})){
					nearest[{x,y}]={nx,ny};
					q.emplace(x,y);
				}
			}
		}
		rep(i,n){
			auto [x,y]=nearest[{xs[i],ys[i]}];
			cout<<x<<' '<<y<<endl;
		}
	}
}
