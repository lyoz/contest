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
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vl vs(n);
		rep(i,n) cin>>vs[i];
		vi xs(m),ys(m);
		rep(i,m) cin>>xs[i]>>ys[i],xs[i]--,ys[i]--;

		UnionFind uf(m+n);
		rep(i,m){
			uf.Unite(i,m+xs[i]);
			uf.Unite(i,m+ys[i]);
		}

		map<int,vi> ccs;
		rep(i,m+n) ccs[uf.Find(i)].push_back(i);

		ll res=0;
		for(auto p:ccs){
			int kcnt=0,bcnt=0;
			ll mn=LLONG_MAX,sum=0;
			for(int x:p.second){
				if(x<m)
					kcnt++;
				else{
					mn=min(mn,vs[x-m]);
					sum+=vs[x-m];
					bcnt++;
				}
			}
			if(kcnt<bcnt){
				assert(kcnt==bcnt-1);
				res+=sum-mn;
			}
			else
				res+=sum;
		}
		cout<<res<<endl;
	}
}
