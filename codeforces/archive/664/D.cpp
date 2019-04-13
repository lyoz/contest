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
	int src,dst,color;
	Edge(){}
	Edge(int s,int d,int c):src(s),dst(d),color(c){}
};
using Graph=vector<vector<Edge>>;

bool dfs(const Graph& g,int color,Edge e,int flg,vi& vis,vi& use)
{
	if(vis[e.dst]!=-1)
		return (color==e.color)==(vis[e.src]==vis[e.dst]);
	vis[e.dst]=flg;
	if(flg) use.push_back(e.dst);
	for(Edge e2:g[e.dst])
		if(!dfs(g,color,e2,flg==(e2.color==color),vis,use))
			return false;
	return true;
}

bool solve(Graph g,int color,vi& res)
{
	int n=g.size();
	vi vis1(n,-1),vis2(n,-1);
	rep(i,n) if(vis1[i]==-1){
		vi use1,use2,use;
		bool ok1=dfs(g,color,Edge(-1,i,0),0,vis1,use1);
		bool ok2=dfs(g,color,Edge(-1,i,0),1,vis2,use2);
		if(ok1 && ok2) use=use1.size()<use2.size()?use1:use2;
		else if(ok1) use=use1;
		else if(ok2) use=use2;
		else return false;
		res.insert(end(res),all(use));
	}
	return true;
}

int main()
{
	for(int n,m;cin>>n>>m && n|m;){
		Graph g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			string c; cin>>c;
			g[u].emplace_back(u,v,c=="R");
			g[v].emplace_back(v,u,c=="R");
		}
		
		vi r,b;
		bool ok1=solve(g,1,r);
		bool ok2=solve(g,0,b);
		
		vi res;
		if(ok1 && ok2)
			res=r.size()<b.size()?r:b;
		else if(ok1)
			res=r;
		else if(ok2)
			res=b;
		else{
			cout<<-1<<endl;
			continue;
		}
		
		cout<<res.size()<<endl;
		rep(i,res.size()) cout<<res[i]+1<<(i<res.size()-1?' ':'\n');
	}
}
