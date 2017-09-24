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

int NextPow2(int x)
{
	x--;
	for(int i=1;i<32;i*=2) x|=x>>i;
	return x+1;
}

namespace minimum{
const int I=INF;
int F(int a,int b){return min(a,b);}

struct SegmentTree{
	int size;
	vi data;
	SegmentTree(int n):size(NextPow2(n)),data(size*2,I){}
	SegmentTree(const vi& a):size(NextPow2(a.size())),data(size*2,I){
		copy(all(a),begin(data)+size);
		peri(i,1,size) data[i]=F(data[i*2],data[i*2+1]);
	}
	int Get(int i){
		return data[size+i];
	}
	void Update(int i,int x){
		data[size+i]=x;
		for(i+=size;i/=2;) data[i]=F(data[i*2],data[i*2+1]);
	}
	int Query(int a,int b,int i,int l,int r){
		if(b<=l || r<=a) return I;
		if(a<=l && r<=b) return data[i];
		return F(Query(a,b,i*2,l,(l+r)/2),Query(a,b,i*2+1,(l+r)/2,r));
	}
	int Query(int a,int b){
		return Query(a,b,1,0,size);
	}
};
}

namespace maximum{
const int I=-INF;
int F(int a,int b){return max(a,b);}

struct SegmentTree{
	int size;
	vi data;
	SegmentTree(int n):size(NextPow2(n)),data(size*2,I){}
	SegmentTree(const vi& a):size(NextPow2(a.size())),data(size*2,I){
		copy(all(a),begin(data)+size);
		peri(i,1,size) data[i]=F(data[i*2],data[i*2+1]);
	}
	int Get(int i){
		return data[size+i];
	}
	void Update(int i,int x){
		data[size+i]=x;
		for(i+=size;i/=2;) data[i]=F(data[i*2],data[i*2+1]);
	}
	int Query(int a,int b,int i,int l,int r){
		if(b<=l || r<=a) return I;
		if(a<=l && r<=b) return data[i];
		return F(Query(a,b,i*2,l,(l+r)/2),Query(a,b,i*2+1,(l+r)/2,r));
	}
	int Query(int a,int b){
		return Query(a,b,1,0,size);
	}
};
}


int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,p,q,r;cin>>n>>p>>q>>r&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];

		minimum::SegmentTree stmin(a);
		maximum::SegmentTree stmax(a);

		ll res=LLONG_MIN;
		rep(i,n){
			ll sum=(ll)q*a[i];
			sum+=(ll)p*(p<0?stmin.Query(0,i+1):stmax.Query(0,i+1));
			sum+=(ll)r*(r<0?stmin.Query(i,n):stmax.Query(i,n));
			res=max(res,sum);
		}
		cout<<res<<endl;
	}
}
