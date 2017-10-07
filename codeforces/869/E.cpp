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

struct FenwickTree2D{
	vector<FenwickTree> data;
	FenwickTree2D(int h,int w):data(h+1,FenwickTree(w)){}
	void AddRange(int i,int j,int x){
		for(;i;i-=i&-i)
			data[i].AddRange(j,x);
	}
	void AddRange(int i,int j,int k,int l,int x){
		AddRange(k,l,x);
		AddRange(k,j,-x);
		AddRange(i,l,-x);
		AddRange(i,j,x);
	}
	ll Get(int i,int j){
		ll res=0;
		for(i++;i<data.size();i+=i&-i)
			res+=data[i].Get(j);
		return res;
	}
};

constexpr int HASH_COUNT=3;
constexpr int HASH_BASE[]={31415926,53589793,23846264};
constexpr int HASH_MOD[]={1000000007,1000000009,1000000021};
vi get_hash(int a,int b,int c,int d)
{
	vl res(HASH_COUNT);
	rep(i,HASH_COUNT)
		for(int x:{a,b,c,d})
			res[i]=(res[i]*HASH_BASE[i]+x)%HASH_MOD[i];
	return vi(all(res));
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w,q;cin>>h>>w>>q&&h|w|q;){
		vector<FenwickTree2D> fts(HASH_COUNT,FenwickTree2D(h,w));
		rep(_,q){
			int t,a,b,c,d; cin>>t>>a>>b>>c>>d;
			if(t==1){
				a--,b--;
				auto h=get_hash(a,b,c,d);
				rep(i,HASH_COUNT)
					fts[i].AddRange(a,b,c,d,h[i]);
			}
			else if(t==2){
				a--,b--;
				auto h=get_hash(a,b,c,d);
				rep(i,HASH_COUNT)
					fts[i].AddRange(a,b,c,d,-h[i]);
			}
			else if(t==3){
				a--,b--,c--,d--;
				vi x(HASH_COUNT),y=x;
				rep(i,HASH_COUNT){
					x[i]=fts[i].Get(a,b);
					y[i]=fts[i].Get(c,d);
				}
				cout<<(x==y?"Yes":"No")<<endl;
			}
		}
	}
}
