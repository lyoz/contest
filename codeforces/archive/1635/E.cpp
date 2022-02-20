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

bool Visit(const vvi& g,int v,vi& color,vi& order)
{
	if(color[v]==1)
		return false;
	if(color[v]==2)
		return true;
	color[v]=1;
	rep(i,g[v].size())
		if(!Visit(g,g[v][i],color,order))
			return false;
	color[v]=2;
	order.push_back(v);
	return true;
}

bool TopologicalSort(const vvi& g,vi& order)
{
	int size=g.size();
	order.clear();
	vi colors(size);
	rep(i,size){
		if(!Visit(g,i,colors,order)){
			order.clear();
			return false;
		}
	}
	reverse(all(order));
	return true;
}

void solve(vvi g)
{
	int n=g.size()/2;
	UnionFind uf(2*n);
	rep(u,2*n) for(int v:g[u])
		uf.Unite(u,v);
	rep(i,n) if(uf.Find(i)==uf.Find(n+i)){
		cout<<"NO"<<endl;
		return;
	}

	vi order;
	if(!TopologicalSort(g,order)){
		cout<<"NO"<<endl;
		return;
	}

	int opposite=order[0]<n?order[0]+n:order[0]-n;
	vector<tuple<char,int>> res(n);
	rep(i,order.size()){
		int u=order[i];
		if(uf.Find(u)==uf.Find(opposite))
			continue;
		if(u<n){
			res[u]={'L',i};
			uf.Unite(u+n,opposite);
		}
		else{
			res[u-n]={'R',i};
			uf.Unite(u-n,opposite);
		}
	}

	cout<<"YES"<<endl;
	for(auto [d,x]:res)
		cout<<d<<' '<<x<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vvi g(2*n);
		rep(i,m){
			int t,u,v; cin>>t>>u>>v; u--,v--;
			if(t==1){
				g[u].push_back(n+v);
				g[v].push_back(n+u);
			}
			else{
				g[n+u].push_back(v);
				g[n+v].push_back(u);
			}
		}
		solve(g);
	}
}
