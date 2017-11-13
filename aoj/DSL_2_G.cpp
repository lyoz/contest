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
	using T=ll;
	const T data_unit=0;  // queryの単位元
	const T lazy_unit=0;  // updateの単位元
	T Merge(T a,T b){
		return a+b;
	}
	T Compose(T a,T b){
		return a+b;
	}
	T Resolve(T l,T d){
		return l+d;
	}
	int NextPow2(int n){
		n--;
		for(int i=1;i<32;i*=2) n|=n>>i;
		return n+1;
	}

	int size;
	vector<T> data,lazy;
	SegmentTree(int n):size(NextPow2(n)),data(2*size,data_unit),lazy(2*size,lazy_unit){}
	void RangeUpdate(int a,int b,T x,int i,int l,int r){
		if(b<=l||r<=a)
			return;
		if(a<=l&&r<=b){
			Apply(x,i);
			return;
		}
		Propagate(i);
		RangeUpdate(a,b,x,i*2,l,(l+r)/2);
		RangeUpdate(a,b,x,i*2+1,(l+r)/2,r);
		data[i]=Merge(data[i*2],data[i*2+1]);
	}
	T RangeQuery(int a,int b,int i,int l,int r){
		if(b<=l||r<=a) return data_unit;
		if(a<=l&&r<=b) return data[i];
		Propagate(i);
		return Merge(RangeQuery(a,b,i*2,l,(l+r)/2),RangeQuery(a,b,i*2+1,(l+r)/2,r));
	}
	void Propagate(int i){
		Apply(lazy[i],2*i);
		Apply(lazy[i],2*i+1);
		lazy[i]=lazy_unit;
	}
	void Apply(T x,int i){
		int len=size>>(31-__builtin_clz(i));
		data[i]=Resolve(x*len,data[i]);
		lazy[i]=Compose(x,lazy[i]);
	}

	void RangeUpdate(int a,int b,T x){return RangeUpdate(a,b,x,1,0,size);}
	T RangeQuery(int a,int b){return RangeQuery(a,b,1,0,size);}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,q;cin>>n>>q&&n|q;){
		SegmentTree st(n);
		rep(_,q){
			int t,l,r; cin>>t>>l>>r; l--;
			if(t==0){  // update
				int x; cin>>x;
				st.RangeUpdate(l,r,x);
			}
			else{  // query
				cout<<st.RangeQuery(l,r)<<endl;
			}
		}
	}
}
