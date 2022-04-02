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

int takahashi(const vvi& g,int p,int u,vi& a,map<tuple<int,vi>,tuple<int,int>>& memo);

int aoki(const vvi& g,int p,int u,vi& a,map<tuple<int,vi>,tuple<int,int>>& memo)
{
	if(memo.count({u,a}))
		return get<0>(memo[{u,a}]);
	int n=g.size();
	int res=INF,mn=-1;
	rep(i,n) if(a[i]){
		int ai=a[i];
		a[i]=0;
		int tmp=takahashi(g,p,u,a,memo);
		if(res>tmp){
			res=tmp;
			mn=i;
		}
		a[i]=ai;
	}
	memo[{u,a}]={res,mn};
	return res;
}

int takahashi(const vvi& g,int p,int u,vi& a,map<tuple<int,vi>,tuple<int,int>>& memo)
{
	int res=0;
	for(int v:g[u]) if(v!=p){
		chmax(res,a[v]);
		chmax(res,aoki(g,u,v,a,memo));
	}
	return res;
}

int dfs(const vvi& g,const vi& a,int thres,int p,int u)
{
	int cnt=0;
	for(int v:g[u]) if(v!=p)
		cnt+=dfs(g,a,thres,u,v);
	return max(cnt-1,0)+(a[u]>thres);
}

// 青木君がthres点以下しかとられないようにできるならtrue
bool ok(const vvi& g,const vi& a,int thres)
{
	return dfs(g,a,thres,-1,0)==0;
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
		repi(i,1,n) cin>>a[i];
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}

		//map<tuple<int,vi>,tuple<int,int>> memo;
		//auto res=aoki(g,-1,0,a,memo);
		//cout<<res<<endl;

		int lo=0,hi=1e9;
		while(lo<hi){
			int mi=(lo+hi)/2;
			if(ok(g,a,mi))
				hi=mi;
			else
				lo=mi+1;
		}
		cout<<lo<<endl;
	}
}
