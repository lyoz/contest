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

struct SegmentTree{
	using T=array<int,101>;
	int size;
	vector<T> lazy;
	SegmentTree(int n):size(NextPow2(n)),lazy(2*size){
		repi(i,1,2*size) iota(all(lazy[i]),0);
	}
	int NextPow2(int n){
		n--;
		for(int i=1;i<32;i*=2) n|=n>>i;
		return n+1;
	}
	void RangeUpdate(int a,int b,int x,int y,int i,int l,int r){
		if(b<=l||r<=a)
			return;
		if(a<=l&&r<=b){
			for(auto& t:lazy[i]) if(t==x) t=y;
			return;
		}
		Propagate(i);
		RangeUpdate(a,b,x,y,i*2,l,(l+r)/2);
		RangeUpdate(a,b,x,y,i*2+1,(l+r)/2,r);
	}
	void Propagate(int i){
		for(auto& t:lazy[2*i]) t=lazy[i][t];
		for(auto& t:lazy[2*i+1]) t=lazy[i][t];
		iota(all(lazy[i]),0);
	}
	T Get(int i){return lazy[size+i];}
	void RangeUpdate(int a,int b,int x,int y){RangeUpdate(a,b,x,y,1,0,size);}
	void Propagate(){repi(i,1,size) Propagate(i);}
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

		SegmentTree st(n);
		int q; cin>>q;
		rep(_,q){
			int l,r,x,y; cin>>l>>r>>x>>y; l--;
			st.RangeUpdate(l,r,x,y);
		}
		st.Propagate();
		rep(i,n)
			cout<<st.Get(i)[a[i]]<<"\n "[i+1<n];
	}
}
