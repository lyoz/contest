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

tuple<ll,ll> dfs(const vvi& g,const vl& b,int p,int u,ll& cnt)
{
	ll zcnt=0,ocnt=0;
	for(int v:g[u]) if(v!=p){
		ll x,y; tie(x,y)=dfs(g,b,u,v,cnt);
		cnt+=x*ocnt+y*zcnt;
		if(b[u]) swap(x,y);
		zcnt+=x,ocnt+=y;
	}
	(b[u]?ocnt:zcnt)++;
	cnt+=ocnt;
	return mt(zcnt,ocnt);
}

ll solve(const vvi& g,const vl& b,int root)
{
	ll cnt=0;
	dfs(g,b,-1,root,cnt);
	return cnt;
}

int main()
{
	for(int n;cin>>n&&n;){
		vl a(n);
		rep(i,n) cin>>a[i];
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}

		if(n==1){
			cout<<a[0]<<endl;
			continue;
		}

		int root=-1;
		rep(i,n) if(g[i].size()==1){
			root=i;
			break;
		}
		ll res=0;
		rep(i,30){
			vl b(n);
			rep(j,n) b[j]=a[j]>>i&1;
			res+=solve(g,b,root)<<i;
		}
		cout<<res<<endl;
	}
}
