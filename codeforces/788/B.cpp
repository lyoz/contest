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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for(int n,m;cin>>n>>m&&n|m;){
		vector<tuple<int,int>> es;
		rep(i,m){
			int u,v; cin>>u>>v; u--,v--;
			es.emplace_back(u,v);
		}

		UnionFind uf(n);
		for(auto e:es){
			int u,v; tie(u,v)=e;
			uf.Unite(u,v);
		}

		bool con=true;
		for(auto e:es){
			int u,v; tie(u,v)=e;
			con&=uf.Find(u)==uf.Find(get<0>(es[0]));
		}
		if(!con){
			cout<<0<<endl;
			continue;
		}

		int loop=0;
		vi ds(n);
		for(auto e:es){
			int u,v; tie(u,v)=e;
			if(u==v)
				loop++;
			else
				ds[u]++,ds[v]++;
		}

		ll res=0;
		rep(i,n)
			res+=(ll)ds[i]*(ds[i]-1)/2;
		res+=(ll)loop*(m-loop);
		res+=(ll)loop*(loop-1)/2;

		cout<<res<<endl;
	}
}
