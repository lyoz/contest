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
	using T=int;
	const T data_unit=0;
	T Merge(T a,T b){
		if(b==data_unit) return a;
		if(a==data_unit) return b;
		return __gcd(a,b);
	}
	T Apply(T x,T){
		return x;
	}
	int NextPow2(int n){
		n--;
		for(int i=1;i<32;i*=2) n|=n>>i;
		return n+1;
	}

	int size;
	vector<T> data;
	SegmentTree(int n):size(NextPow2(n)),data(2*size,data_unit){}
	SegmentTree(const vector<T>& a):size(NextPow2(a.size())),data(2*size,data_unit){
		copy(all(a),begin(data)+size);
		peri(i,1,size) data[i]=Merge(data[i*2],data[i*2+1]);
	}
	void PointUpdate(int i,T x){
		data[size+i]=Apply(x,data[size+i]);
		for(i+=size;i/=2;) data[i]=Merge(data[i*2],data[i*2+1]);
	}
	// (区間全体のgcd, gcdをxにするために少なくとも変更しなければならない要素の個数)
	tuple<T,int> RangeQuery(int a,int b,T x,int i,int l,int r){
		if(b<=l||r<=a) return {data_unit,0};
		if(a<=l&&r<=b){
			if(data[i]==x) return {data[i],0};
			if(data[i]%x==0) return {data[i],1};
			if(r-l==1) return {data[i],1};
			assert(data[i*2]%x||data[i*2+1]%x);
			int cnt=1;
			if(data[i*2]%x&&data[i*2+1]%x)
				cnt=2;
			else if(data[i*2]%x)
				cnt=get<1>(RangeQuery(a,b,x,i*2,l,(l+r)/2));
			else if(data[i*2+1]%x)
				cnt=get<1>(RangeQuery(a,b,x,i*2+1,(l+r)/2,r));
			return {data[i],cnt};
		}
		auto u=RangeQuery(a,b,x,i*2,l,(l+r)/2);
		auto v=RangeQuery(a,b,x,i*2+1,(l+r)/2,r);
		int cnt=1;
		if(get<0>(u)%x&&get<0>(v)%x) cnt=2;
		else if(get<0>(u)%x) cnt=get<1>(u);
		else if(get<0>(v)%x) cnt=get<1>(v);
		return {Merge(get<0>(u),get<0>(v)),cnt};
	}
	tuple<T,int> RangeQuery(int a,int b,T x){return RangeQuery(a,b,x,1,0,size);}
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

		SegmentTree st(a);
		int q; cin>>q;
		rep(_,q){
			int t; cin>>t;
			if(t==1){
				int l,r,x; cin>>l>>r>>x; l--;
				cout<<(get<1>(st.RangeQuery(l,r,x))<=1?"YES":"NO")<<endl;
			}
			else if(t==2){
				int l,y; cin>>l>>y; l--;
				st.PointUpdate(l,y);
			}
		}
	}
}
