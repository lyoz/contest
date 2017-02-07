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
	for(int n,m,q;cin>>n>>m>>q&&n|m|q;){
		map<string,int> f;
		rep(i,n){
			string s; cin>>s;
			f.emplace(s,f.size());
		}

		UnionFind uf(2*n);
		rep(i,m){
			int t; string a,b; cin>>t>>a>>b;
			int u=f[a],v=f[b];
			if(t==1){
				if(uf.Find(u)==uf.Find(v+n))
					cout<<"NO"<<endl;
				else{
					cout<<"YES"<<endl;
					uf.Unite(u,v);
					uf.Unite(u+n,v+n);
				}
			}
			else{
				if(uf.Find(u)==uf.Find(v))
					cout<<"NO"<<endl;
				else{
					cout<<"YES"<<endl;
					uf.Unite(u,v+n);
					uf.Unite(u+n,v);
				}
			}
		}
		rep(i,q){
			string a,b; cin>>a>>b;
			int u=f[a],v=f[b];
			if(uf.Find(u)==uf.Find(v))
				cout<<1<<endl;
			else if(uf.Find(u)==uf.Find(v+n))
				cout<<2<<endl;
			else
				cout<<3<<endl;
		}
	}
}
