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

struct UnionFind{
	vi data;
	UnionFind(int n):data(n,-1){}
	int Find(int i){
		return data[i]<0?i:(data[i]=Find(data[i]));
	}
	bool Unite(int a,int b){
		a=Find(a),b=Find(b);
		if(a==b) return false;
		if(-data[a]<-data[b]) swap(a,b);
		data[a]+=data[b];
		data[b]=a;
		return true;
	}
	int Size(int i){
		return -data[Find(i)];
	}
};

bool IsBipartite(const vvi& g)
{
	int n=g.size();
	UnionFind uf(2*n);
	rep(i,n) repi(j,i+1,n) if(g[i][j]){
		uf.Unite(i,n+j);
		uf.Unite(n+i,j);
	}
	rep(i,n) if(uf.Find(i)==uf.Find(n+i))
		return false;
	return true;
}

void dfs(const vvi& g,int u,int c,vi& vis,int& l,int& r)
{
	if(!vis[u]){
		vis[u]=1;
		int n=g.size();
		(c==0?l:r)++;
		rep(v,n) if(g[u][v])
			dfs(g,v,!c,vis,l,r);
	}
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vvi g(n,vi(n));
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			g[u][v]=g[v][u]=1;
		}
		rep(i,n) repi(j,i+1,n){
			g[i][j]^=1;
			g[j][i]^=1;
		}

		if(!IsBipartite(g)){
			cout<<-1<<endl;
			continue;
		}

		vi dp(n+1); dp[0]=1;

		vi vis(n);
		rep(i,n) if(!vis[i]){
			int l=0,r=0;
			dfs(g,i,0,vis,l,r);
			vi dp2(n+1);
			for(int x:{l,r})
				repi(i,x,n+1)
					dp2[i]|=dp[i-x];
			dp=move(dp2);
		}

		int res=INF;
		rep(i,n) if(dp[i])
			chmin(res,i*(i-1)/2+(n-i)*(n-i-1)/2);
		cout<<res<<endl;
	}
}
