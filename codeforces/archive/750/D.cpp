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

int main()
{
	using vvvi=vector<vvi>;

	for(int n;cin>>n&&n;){
		vi ts(n);
		rep(i,n) cin>>ts[i];

		vi sum(n+1);
		rep(i,n) sum[i+1]=sum[i]+ts[i];
		int m=sum[n];

		int di[]={0,-1,-1,-1,0,1,1,1};
		int dj[]={1,1,0,-1,-1,-1,0,1};

		vvvi vis(m+1,vvi(301,vi(301)));  // vis[歩数][i][j]の(歩数)ビット目を立てる
		queue<tuple<int,int,int,int>> q;
		q.emplace(2,1,149,150);
		while(q.size()){
			int cd,cs,ci,cj; tie(cd,cs,ci,cj)=q.front(); q.pop();
			if(vis[cs][ci][cj]>>cd&1) continue;
			vis[cs][ci][cj]|=1<<cd;
			if(cs==m) continue;
			if(binary_search(all(sum),cs)){
				int nd=(cd+1)%8;
				q.emplace(nd,cs+1,ci+di[nd],cj+dj[nd]);
				nd=(cd+7)%8;
				q.emplace(nd,cs+1,ci+di[nd],cj+dj[nd]);
			}
			else{
				q.emplace(cd,cs+1,ci+di[cd],cj+dj[cd]);
			}
		}

		vvi grid(301,vi(301));
		rep(s,m+1) rep(i,301) rep(j,301)
			grid[i][j]|=!!vis[s][i][j];

		int res=0;
		rep(i,301) rep(j,301) res+=grid[i][j];
		cout<<res<<endl;
	}
}
