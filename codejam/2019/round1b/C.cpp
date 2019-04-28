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

void solve_small()
{
	int n,k; cin>>n>>k;
	vi cs(n),ds(n);
	rep(i,n) cin>>cs[i];
	rep(i,n) cin>>ds[i];

	int res=0;
	rep(l,n) repi(r,l,n){
		int cmax=*max_element(begin(cs)+l,begin(cs)+r+1);
		int dmax=*max_element(begin(ds)+l,begin(ds)+r+1);
		res+=abs(cmax-dmax)<=k;
	}
	cout<<res<<endl;
}

struct SegmentTree{
	using T=int;
	const T data_unit=-INF;
	T Merge(T a,T b){
		return max(a,b);
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
	T RangeQuery(int a,int b,int i,int l,int r){
		if(b<=l||r<=a) return data_unit;
		if(a<=l&&r<=b) return data[i];
		return Merge(RangeQuery(a,b,i*2,l,(l+r)/2),RangeQuery(a,b,i*2+1,(l+r)/2,r));
	}
	T RangeQuery(int a,int b){return RangeQuery(a,b,1,0,size);}
};

ll calc(int n,int k,const vi& cs,const vi& ds)
{
	SegmentTree st1(cs);
	SegmentTree st2(ds);
	ll res=0;
	rep(i,n){
		int l,r;
		{
			int lo=0,hi=i;
			while(lo<hi){
				int mi=(lo+hi)/2;
				if(st1.RangeQuery(mi,i)<cs[i] && st2.RangeQuery(mi,i)<cs[i]-k)
					hi=mi;
				else
					lo=mi+1;
			}
			l=lo;
		}
		{
			int lo=i,hi=n;
			while(lo<hi){
				int mi=(lo+hi)/2;
				if(st1.RangeQuery(i,mi+1)<=cs[i] && st2.RangeQuery(i,mi+1)<cs[i]-k)
					lo=mi+1;
				else
					hi=mi;
			}
			r=lo;
		}
		res+=ll(i-l+1)*(r-i);
	}
	return res;
}

void solve()
{
	int n,k; cin>>n>>k;
	vi cs(n),ds(n);
	rep(i,n) cin>>cs[i];
	rep(i,n) cin>>ds[i];

	ll res=ll(n)*(n+1)/2;
	res-=calc(n,k,cs,ds);
	res-=calc(n,k,ds,cs);
	cout<<res<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}
