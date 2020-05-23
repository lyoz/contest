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

	constexpr int di[]={1,0,-1,1,-1,0};
	constexpr int dj[]={1,1,1,0,0,-1};

	for(int n,i1,j1;cin>>n>>i1>>j1&&n;){
		// offset: 210
		i1+=210,j1+=210;
		int i0=210,j0=210;

		set<tuple<int,int>> obs;
		rep(k,n){
			int i,j; cin>>i>>j;
			obs.emplace(i+210,j+210);
		}

		vvi grid(420,vi(420,INF));
		queue<tuple<int,int,int>> q;
		q.emplace(i0,j0,0);
		while(q.size()){
			int ci,cj,cc; tie(ci,cj,cc)=q.front(); q.pop();
			if(ci<0||420<=ci||cj<0||420<=cj||obs.count(mt(ci,cj))||grid[ci][cj]!=INF)
				continue;
			grid[ci][cj]=cc;
			rep(k,6){
				int ni=ci+di[k],nj=cj+dj[k];
				q.emplace(ni,nj,cc+1);
			}
		}
		cout<<(grid[i1][j1]!=INF?grid[i1][j1]:-1)<<endl;
	}
}
