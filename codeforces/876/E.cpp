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

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
using Graph=vector<vector<Edge>>;
ostream& operator<<(ostream& os,const Edge& e){
	return os<<'('<<e.src<<','<<e.dst<<')';
}

void DFS(const Graph& g,int v,vi& vis,vi& order)
{
	if(vis[v]) return;
	vis[v]=1;
	for(auto e:g[v]) DFS(g,e.dst,vis,order);
	order.push_back(v);
}

vvi SCC(const Graph& g)
{
	int n=g.size();
	vi vis(n),order;
	rep(i,n) DFS(g,i,vis,order);
	Graph t(n);
	rep(i,n) for(auto e:g[i])
		t[e.dst].emplace_back(e.dst,e.src);
	fill(all(vis),0);
	vvi res;
	per(i,n) if(!vis[order[i]]){
		res.resize(res.size()+1);
		DFS(t,order[i],vis,res.back());
	}
	return res;
}

bool has_cycle(const Graph& g)
{
	for(auto cc:SCC(g))
		if(cc.size()>1)
			return true;
	return false;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vvi ss(n);
		rep(i,n){
			int size; cin>>size;
			ss[i].resize(size);
			rep(j,size) cin>>ss[i][j],ss[i][j]--;
		}

		Graph g(m);  // (文字u)<(文字v)ならば辺(u,v)を追加する
		bool prefix=false;
		rep(i,n-1){
			int j;
			for(j=0;j<min(ss[i].size(),ss[i+1].size());j++)
				if(ss[i][j]!=ss[i+1][j]){
					int u=ss[i][j],v=ss[i+1][j];
					g[u].emplace_back(u,v);
					break;
				}
			if(ss[i].size()>ss[i+1].size()&&j==ss[i+1].size())
				prefix=true;
		}

		if(prefix){
			cout<<"No"<<endl;
			continue;
		}

		if(has_cycle(g)){
			cout<<"No"<<endl;
			continue;
		}

		vi vis(m),order;
		rep(i,m) DFS(g,i,vis,order);

		Graph g2(m);
		rep(i,m) for(auto e:g[i]) g2[e.dst].emplace_back(e.dst,e.src);

		bool ok=true;
		vi cap(m);
		rep(i,order.size()){
			for(auto e:g2[order[i]]){
				if(cap[e.src]&&e.src<e.dst)
					ok=false;
				if(cap[e.src]||e.src<e.dst)
					cap[e.dst]=1;
			}
		}

		if(!ok){
			cout<<"No"<<endl;
			continue;
		}

		cout<<"Yes"<<endl;
		vi res;
		rep(i,m) if(cap[i]) res.push_back(i);
		cout<<res.size()<<endl;
		rep(i,res.size()) cout<<res[i]+1<<"\n "[i+1<res.size()];
	}
}
