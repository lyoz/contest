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

struct FenwickTree{
	vector<ll> data;
	FenwickTree(int size):data(size+1){}
	void Add(int i,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i]+=x;
	}
	ll Sum(int i){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i];
		return res;
	}
};

struct FenwickTree2D{
	vector<FenwickTree> data;
	FenwickTree2D(int size):data(size+1,size){}
	void Add(int i,int j,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i].Add(j,x);
	}
	ll Sum(int i,int j){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i].Sum(j);
		return res;
	}
};

struct FenwickTree3D{
	vector<FenwickTree2D> data;
	FenwickTree3D(int size):data(size+1,size){}
	void Add(int i,int j,int k,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i].Add(j,k,x);
	}
	ll Sum(int i,int j,int k){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i].Sum(j,k);
		return res;
	}
};

struct FenwickTree4D{
	vector<FenwickTree3D> data;
	FenwickTree4D(int size):data(size+1,size){}
	void Add(int i,int j,int k,int l,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i].Add(j,k,l,x);
	}
	ll Sum(int i,int j,int k,int l){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i].Sum(j,k,l);
		return res;
	}
};

struct FenwickTree5D{
	vector<FenwickTree4D> data;
	FenwickTree5D(int size):data(size+1,size){}
	void Add(int i,int j,int k,int l,int m,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i].Add(j,k,l,m,x);
	}
	ll Sum(int i,int j,int k,int l,int m){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i].Sum(j,k,l,m);
		return res;
	}
};

struct FenwickTree6D{
	vector<FenwickTree5D> data;
	FenwickTree6D(int size):data(size+1,size){}
	void Add(int i,int j,int k,int l,int m,int n,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i].Add(j,k,l,m,n,x);
	}
	ll Sum(int i,int j,int k,int l,int m,int n){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i].Sum(j,k,l,m,n);
		return res;
	}
};

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

		FenwickTree6D ft(10);
		ll res=0;

		rep(i,n){
			vi d(6);
			int x=a[i];
			rep(j,6){
				d[j]=x%10;
				x/=10;
			}
			res+=ft.Sum(10-d[0],10-d[1],10-d[2],10-d[3],10-d[4],10-d[5]);
			ft.Add(d[0],d[1],d[2],d[3],d[4],d[5],1);
		}
		cout<<res<<endl;
	}
}
