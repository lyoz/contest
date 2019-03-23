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

using Edge=tuple<int,int>;

int dfs(const vvi& g,int p,int u,vi& ord,vi& low,vector<Edge>& s,vector<vector<Edge>>& bcs)
{
	int cnt=1;
	for(int v:g[u]) if(v!=p){
		if(ord[v]<ord[u])
			s.emplace_back(u,v);
		if(ord[v]==-1){
			ord[v]=low[v]=ord[u]+cnt;
			cnt+=dfs(g,u,v,ord,low,s,bcs);
			low[u]=min(low[u],low[v]);
			if(ord[u]<=low[v]){
				bcs.emplace_back();
				for(;;){
					Edge e=s.back(); s.pop_back();
					bcs.back().push_back(e);
					if(e==Edge(u,v)) break;
				}
			}
		}
		else
			low[u]=min(low[u],ord[v]);
	}
	return cnt;
}

vector<vector<Edge>> biconnected_components(const vvi& g)
{
	int n=g.size();
	vi ord(n,-1),low(n);
	vector<Edge> s;
	vector<vector<Edge>> bcs;
	
	rep(i,n) if(ord[i]==-1){
		ord[i]=low[i]=0;
		dfs(g,-1,i,ord,low,s,bcs);
	}

	return bcs;
}

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

int ModInverse(int a,int m)
{
	int x=1;
	for(int b=m,u=0;b;){
		ll t=a/b;
		swap(a-=b*t,b);
		swap(x-=u*t,u);
	}
	return (x+m)%m;
}

int ModMul(int a,int b,int m)
{
	return (ll)a*b%m;
}

int ModDiv(int a,int b,int m)
{
	return ModMul(a,ModInverse(b,m),m);
}

int Choose(int n,int r,int m)
{
	int res=1;
	rep(i,r) res=ModMul(res,n-i,m);
	rep(i,r) res=ModDiv(res,i+1,m);
	return res;
}

int main()
{
	for(int n,m,k;cin>>n>>m>>k&&n|m|k;){
		vvi g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}

		ll res=1;
		for(auto bc:biconnected_components(g)){
			int m=bc.size();
			if(m==1)
				(res*=k)%=MOD;
			else{
				set<int> vs;
				for(Edge e:bc){
					vs.insert(get<0>(e));
					vs.insert(get<1>(e));
				}
				if(vs.size()==m){  // cycle
					ll tmp=0;
					rep(i,m)
						(tmp+=ModPow(k,__gcd(m,i),MOD))%=MOD;
					(res*=ModDiv(tmp,m,MOD))%=MOD;
				}
				else{
					(res*=Choose(k+m-1,m,MOD))%=MOD;
				}
			}
		}
		cout<<res<<endl;
	}
}
