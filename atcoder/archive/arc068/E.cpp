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

struct FenwickTree{
	vector<ll> data;
	FenwickTree(int n):data(n+1){}
	void AddRange(int i,int x){
		for(;i;i-=i&-i)
			data[i]+=x;
	}
	void AddRange(int i,int j,int x){
		AddRange(i,-x);
		AddRange(j,x);
	}
	int Get(int i){
		ll res=0;
		for(i++;i<data.size();i+=i&-i)
			res+=data[i];
		return res;
	}
};

int main()
{
	for(int n,m;cin>>n>>m&&n|m;){
		vi ls(n),rs(n);
		rep(i,n) cin>>ls[i]>>rs[i];

		map<int,vi> f;
		rep(i,n) f[rs[i]-ls[i]+1].push_back(i);

		vi sum(m+1);
		rep(i,m+1) sum[i]=f[i].size();
	 	per(i,m) sum[i]+=sum[i+1];

		FenwickTree ft(m+1);
		repi(d,1,m+1){
			int res=sum[d];
			for(int i=d;i<=m;i+=d)
				res+=ft.Get(i);
			cout<<res<<endl;
			for(int i:f[d])
				ft.AddRange(ls[i],rs[i]+1,1);
		}
	}
}
