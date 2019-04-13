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

vvl solve(const vvi& g,int m,int k,int x,int p,int u)
{
	vvl r(3,vl(x+1));
	r[0][0]=k-1;
	r[1][1]=1;
	r[2][0]=m-k;
	for(int v:g[u]) if(v!=p){
		vvl s=solve(g,m,k,x,u,v);
		vvl t(3,vl(x+1));
		rep(i,x+1) rep(j,x+1) if(i+j<=x){
			(t[0][i+j]+=r[0][i]*(s[0][j]+s[1][j]+s[2][j]))%=MOD;
			(t[1][i+j]+=r[1][i]*(s[0][j]))%=MOD;
			(t[2][i+j]+=r[2][i]*(s[0][j]+s[2][j]))%=MOD;
		}
		r=t;
	}
	return r;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int k,x; cin>>k>>x;

		vvl r=solve(g,m,k,x,-1,0);
		ll res=0;
		rep(i,3) rep(j,x+1) (res+=r[i][j])%=MOD;
		cout<<res<<endl;
	}
}
