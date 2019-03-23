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
	vi parent,size;
	vl sum;
	map<tuple<int,int>,tuple<int,int,int>> logs;
	UnionFind(const vi& xs):parent(xs.size(),-1),size(xs.size(),1),sum(all(xs)){}
	int Find(int i){
		return parent[i]==-1?i:Find(parent[i]);
	}
	bool Unite(int a,int b){
		int ra=Find(a),rb=Find(b);
		if(ra==rb)
			return false;
		if(size[ra]<size[rb])
			swap(ra,rb);
		logs[mt(a,b)]=mt(ra,rb,parent[ra]);
		parent[rb]=ra;
		size[ra]+=size[rb];
		sum[ra]+=sum[rb];
		return true;
	}
	void Rollback(int a,int b){
		int ra,rb,pa; tie(ra,rb,pa)=logs[mt(a,b)];
		parent[rb]=pa;
		size[ra]-=size[rb];
		sum[ra]-=sum[rb];
	}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vi xs(n);
		rep(i,n) cin>>xs[i];
		vi us(m),vs(m),ws(m);
		vector<tuple<int,int,int>> es(m);
		rep(i,m){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			es[i]=mt(u,v,w);
		}
		sort(all(es),[](auto a,auto b){return get<2>(a)<get<2>(b);});

		UnionFind uf(xs);

		vi used(m);
		rep(i,m){
			int u,v,w; tie(u,v,w)=es[i];
			used[i]=uf.Unite(u,v);
		}

		int res=0;
		per(i,m){
			int u,v,w; tie(u,v,w)=es[i];
			int ra=uf.Find(u),rb=uf.Find(v);
			assert(ra==rb);
			if(uf.sum[ra]>=w)
				continue;
			res++;
			if(!used[i])
				continue;
			if(uf.sum[ra]<w)
				uf.Rollback(u,v);
		}
		cout<<res<<endl;
	}
}
