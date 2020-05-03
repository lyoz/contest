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

	using vvvi=vector<vvi>;

	for(int h,w;cin>>h>>w&&h|w;){
		vvi grid(h,vi(w)); // S=0,G=10
		rep(i,h){
			string s; cin>>s;
			rep(j,w){
				if(s[j]=='S')
					grid[i][j]=0;
				else if(s[j]=='G')
					grid[i][j]=10;
				else
					grid[i][j]=s[j]-'0';
			}
		}

		queue<tuple<int,int,int,int>> q; // i,j,次に何番目を踏みに行くか,歩数
		rep(i,h) rep(j,w) if(grid[i][j]==0) q.emplace(i,j,0,0);

		vvvi vis(h,vvi(w,vi(11,INF)));
		while(q.size()){
			int ci,cj,ck,cw; tie(ci,cj,ck,cw)=q.front(); q.pop();
			if(vis[ci][cj][ck]!=INF)
				continue;
			vis[ci][cj][ck]=cw;

			int nk=ck+(grid[ci][cj]==ck);
			if(nk>10) // ゴールした
				continue;

			rep(d,4){
				int ni=ci+"\xff\x1\0\0"[d],nj=cj+"\0\0\xff\x1"[d];
				if(ni<0||h<=ni||nj<0||w<=nj)
					continue;
				q.emplace(ni,nj,nk,cw+1);
			}
		}

		rep(i,h) rep(j,w) if(grid[i][j]==10){
			int res=vis[i][j][10];
			cout<<(res==INF?-1:res)<<endl;
		}
	}
}
