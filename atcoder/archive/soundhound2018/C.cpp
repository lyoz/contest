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
using pii=pair<int,int>;

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

struct Edge{
	int src,dst,cap,flow;
	Edge(){}
	Edge(int s,int d,int c,int f=0):src(s),dst(d),cap(c),flow(f){}
};
struct Graph{
	vector<Edge> es;
	vi head,next;
	Graph(){}
	Graph(int n):head(n,-1){}
	// 有向辺を追加するとき逆辺の容量c2は普通0である．
	// 両方向に容量があるならc2も指定する．
	void AddEdge(int u,int v,int c1,int c2=0){
		es.emplace_back(u,v,c1); next.push_back(head[u]); head[u]=es.size()-1;
		es.emplace_back(v,u,c2); next.push_back(head[v]); head[v]=es.size()-1;
	}
};

void BFS(const Graph& g,int tap,vi& layer)
{
	queue<pii> q; q.emplace(tap,0);
	while(q.size()){
		int u,d; tie(u,d)=q.front(); q.pop();
		if(layer[u]!=INF) continue;
		layer[u]=d;
		for(int i=g.head[u];i!=-1;i=g.next[i])
			if(g.es[i].cap-g.es[i].flow>0)
				q.emplace(g.es[i].dst,d+1);
	}
}

int DFS(Graph& g,int v,int sink,const vi& layer,int flow)
{
	if(v==sink) return flow;
	int f=flow;
	for(int& i=g.head[v];i!=-1;i=g.next[i]){
		Edge& e=g.es[i];
		if(layer[e.src]>=layer[e.dst]) continue;
		int residue=e.cap-e.flow;
		if(residue==0) continue;
		int augment=DFS(g,e.dst,sink,layer,min(residue,f));
		e.flow+=augment;
		g.es[i^1].flow-=augment;
		f-=augment;
		if(f==0) break;
	}
	return flow-f;
}

int Dinic(Graph& g,int tap,int sink)
{
	int res=0;
	for(int n=g.head.size();;){
		vi layer(n,INF);
		BFS(g,tap,layer);
		if(layer[sink]==INF) break;
		vi temp=g.head;
		res+=DFS(g,tap,sink,layer,INF);
		swap(g.head,temp);
	}
	return res;
}

int solve(vs grid)
{
	int h=grid.size(),w=grid[0].size();
	Graph g(h*w+2);
	int tap=h*w,sink=tap+1;
	rep(i,h) rep(j,w){
		int u=i*w+j;
		int p=(i^j)&1;
		if(grid[i][j]=='.'){
			g.AddEdge(tap,u,p);
			g.AddEdge(u,sink,!p);
		}
		else{
			g.AddEdge(tap,u,0);
			g.AddEdge(u,sink,0);
		}
		rep(k,2){
			int ni=i+"\x1\0"[k],nj=j+"\0\x1"[k];
			if(h<=ni||w<=nj)
				continue;
			int v=ni*w+nj;
			g.AddEdge(u,v,p*INF,(!p)*INF);
		}
	}
	int cnt=0;
	rep(i,h) rep(j,w) cnt+=grid[i][j]=='.';
	return cnt-Dinic(g,tap,sink);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w;cin>>h>>w&&h|w;){
		vs grid(h);
		rep(i,h) cin>>grid[i];
		cout<<solve(grid)<<endl;
	}
}
