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

int bfs(vs& grid,int si,int sj,int gi,int gj)
{
	int h=grid.size(),w=grid[0].size();
	vvi vis(h,vi(w));
	queue<tuple<int,int,int>> q;
	q.emplace(si,sj,0);
	while(q.size()){
		int i,j,d; tie(i,j,d)=q.front(); q.pop();
		if(i<0 || h<=i || j<0 || w<=j || grid[i][j]=='X' || vis[i][j]) continue;
		vis[i][j]=1;
		if(i==gi && j==gj) return d;
		rep(k,4) q.emplace(i+"\xff\x1\0\0"[k],j+"\0\0\xff\x1"[k],d+1);
	}
	return -1;
}

int main()
{
	for(int h,w,n;cin>>h>>w>>n;){
		vs grid(h,"#");
		rep(i,h) cin>>grid[i];
		
		rep(i,h) rep(j,w) if(grid[i][j]=='S') grid[i][j]='0';
		int res=0;
		rep(k,n){
			int si,sj,gi,gj;
			rep(i,h) rep(j,w){
				if(grid[i][j]=='0'+k)
					si=i,sj=j;
				if(grid[i][j]=='0'+k+1)
					gi=i,gj=j;
			}
			res+=bfs(grid,si,sj,gi,gj);
		}
		cout<<res<<endl;
	}
}
