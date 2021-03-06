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
	for(int n,m;cin>>n>>m && n|m;){
		vi us(m),vs(m);
		rep(i,m){
			cin>>us[i]>>vs[i];
			us[i]--,vs[i]--;
		}
		int q; cin>>q;
		vi xs(q),ys(q),zs(q);
		rep(i,q){
			cin>>xs[i]>>ys[i]>>zs[i];
			xs[i]--,ys[i]--;
		}

		vi ls(q),rs(q,m);
		while(ls<rs){
			vi ms(q);
			rep(i,q) ms[i]=(ls[i]+rs[i])/2;
			vi is(q); iota(all(is),0);
			sort(all(is),[&](int a,int b){return ms[a]<ms[b];});
			UnionFind uf(n);
			int j=0;
			for(int i:is){
				for(;j<=ms[i];j++) uf.Unite(us[j],vs[j]);
				int size=uf.Find(xs[i])==uf.Find(ys[i])?uf.Size(xs[i]):uf.Size(xs[i])+uf.Size(ys[i]);
				if(size>=zs[i])
					rs[i]=ms[i];
				else
					ls[i]=ms[i]+1;
			}
		}
		rep(i,q) cout<<ls[i]+1<<endl;
	}
}
