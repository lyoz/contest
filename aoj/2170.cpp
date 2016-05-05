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
	int find(int v){
		return data[v]<0?v:find(data[v]);
	}
	bool unite(int u,int v){
		int ru=find(u),rv=find(v);
		if(ru==rv) return false;
		data[ru]+=data[rv];
		data[rv]=ru;
		return true;
	}
};

int main()
{
	for(int n,m;cin>>n>>m && n|m;){
		vi ps(n);
		repi(i,1,n) cin>>ps[i],ps[i]--;
		vector<tuple<char,int>> qs;
		rep(i,m){
			char c; cin>>c;
			int v; cin>>v; v--;
			qs.emplace_back(c,v);
		}
		
		vi marked(n);
		marked[0]=1;
		for(auto q:qs)
			if(get<0>(q)=='M')
				marked[get<1>(q)]++;
		
		UnionFind uf(n);
		rep(i,n) if(!marked[i])
			uf.unite(ps[i],i);
		
		ll res=0;
		per(i,m){
			char t; int v; tie(t,v)=qs[i];
			if(t=='M' && --marked[v]==0)
				uf.unite(ps[v],v);
			if(t=='Q')
				res+=uf.find(v)+1;
		}
		cout<<res<<endl;
	}
}
