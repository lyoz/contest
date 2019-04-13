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

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
using Graph=vector<vector<Edge>>;

bool is_unique(int a,int b,int c,int d)
{
	int t[]={a,b,c,d}; sort(all(t));
	return unique(all(t))-begin(t)==4;
}

int main()
{
	for(int n,m;cin>>n>>m && n|m;){
		Graph g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			g[u].emplace_back(u,v);
		}
		vvi d(n,vi(n,INF));
		rep(i,n){
			d[i][i]=0;
			queue<int> q; q.push(i);
			while(q.size()){
				int u=q.front(); q.pop();
				for(auto e:g[u]){
					int v=e.dst;
					if(d[i][v]==INF){
						d[i][v]=d[i][u]+1;
						q.push(v);
					}
				}
			}
		}
		
		vector<vector<tuple<int,int>>> d1(n),d2(n);
		rep(i,n) rep(j,n) if(d[i][j]!=INF){
			d1[j].emplace_back(d[i][j],i);
			d2[i].emplace_back(d[i][j],j);
		}
		rep(i,n){
			sort(all(d1[i]),greater<tuple<int,int>>());
			sort(all(d2[i]),greater<tuple<int,int>>());
		}
		
		tuple<int,int,int,int,int> res(-1,0,0,0,0);
		rep(i,n) rep(j,n) if(i!=j && d[i][j]!=INF){
			rep(k,min<int>(d1[i].size(),3))
				rep(l,min<int>(d2[j].size(),3)){
					int u,v,x,y; tie(x,u,y,v)=tuple_cat(d1[i][k],d2[j][l]);
					if(!is_unique(u,i,j,v)) continue;
					res=max(res,mt(x+d[i][j]+y,u,i,j,v));
				}
		}
		printf("%d %d %d %d\n",get<1>(res)+1,get<2>(res)+1,get<3>(res)+1,get<4>(res)+1);
	}
}
