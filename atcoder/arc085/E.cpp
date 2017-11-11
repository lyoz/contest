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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Edge{
	int src,dst;
	ll cap,flow;
	Edge(){}
	Edge(int s,int d,ll c,ll f=0):src(s),dst(d),cap(c),flow(f){}
};

struct Graph{
	vector<Edge> es;
	vi head,next;
	Graph(){}
	Graph(int n):head(n,-1){}
	// 有向辺を追加するとき逆辺の容量c2は普通0である．
	// 両方向に容量があるならc2も指定する．
	void AddEdge(int u,int v,ll c1,ll c2=0){
		es.emplace_back(u,v,c1); next.push_back(head[u]); head[u]=es.size()-1;
		es.emplace_back(v,u,c2); next.push_back(head[v]); head[v]=es.size()-1;
	}
};

void BFS(const Graph& g,int tap,vl& layer)
{
	queue<tuple<int,ll>> q; q.emplace(tap,0);
	while(q.size()){
		int u,d; tie(u,d)=q.front(); q.pop();
		if(layer[u]!=INF) continue;
		layer[u]=d;
		for(int i=g.head[u];i!=-1;i=g.next[i])
			if(g.es[i].cap-g.es[i].flow>0)
				q.emplace(g.es[i].dst,d+1);
	}
}

ll DFS(Graph& g,int v,int sink,const vl& layer,ll flow)
{
	if(v==sink) return flow;
	ll f=flow;
	for(int& i=g.head[v];i!=-1;i=g.next[i]){
		Edge& e=g.es[i];
		if(layer[e.src]>=layer[e.dst]) continue;
		ll residue=e.cap-e.flow;
		if(residue==0) continue;
		ll augment=DFS(g,e.dst,sink,layer,min(residue,f));
		e.flow+=augment;
		g.es[i^1].flow-=augment;
		f-=augment;
		if(f==0) break;
	}
	return flow-f;
}

ll Dinic(Graph& g,int tap,int sink)
{
	ll res=0;
	for(int n=g.head.size();;){
		vl layer(n,INF);
		BFS(g,tap,layer);
		if(layer[sink]==INF) break;
		vi temp=g.head;
		res+=DFS(g,tap,sink,layer,INF);
		g.head=move(temp);
	}
	return res;
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
		rep(i,n) cin>>a[i];

		Graph g(n+2);
		int tap=n,sink=tap+1;
		rep(i,n){
			g.AddEdge(tap,i,max(-a[i],0));
			g.AddEdge(i,sink,max(a[i],0));
			int x=i+1;
			for(int y=x+x;y<=n;y+=x)
				g.AddEdge(x-1,y-1,INF);
		}

		ll res=0;
		rep(i,n) res+=max(a[i],0);
		cout<<res-Dinic(g,tap,sink)<<endl;
	}
}
