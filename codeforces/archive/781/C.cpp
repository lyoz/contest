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

void dfs(const vvi& g,int p,int u,vi& path)
{
	path.push_back(u);
	for(auto v:g[u]) if(v!=p){
		dfs(g,u,v,path);
		path.push_back(u);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for(int n,m,k;cin>>n>>m>>k&&n|m|k;){
		UnionFind uf(n);
		vvi g(n);
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			if(uf.Unite(u,v)){
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}

		if(n==1){
			rep(i,k)
				cout<<"1 1"<<endl;
			continue;
		}

		vi path;
		dfs(g,-1,0,path);
		path.push_back(path[1]);
		assert(path.size()==2*n);

		vi rs(k+1);
		rep(i,k)
			rs[i+1]=rs[i]+(2*n+i)/k;

		rep(i,k){
			cout<<rs[i+1]-rs[i];
			repi(j,rs[i],rs[i+1])
				cout<<' '<<path[j]+1;
			cout<<endl;
		}
	}
}
