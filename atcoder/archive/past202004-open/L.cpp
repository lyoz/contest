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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct SegmentTree{
	using T=ll;
	const T data_unit=INF;
	T Merge(T a,T b){
		return min(a,b);
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
	vector<T> data,index;
	SegmentTree(int n):size(NextPow2(n)),data(2*size,data_unit),index(2*size,-1){
		iota(begin(index)+size,begin(index)+size+n,0);
		peri(i,1,size) index[i]=index[i*2];
	}
	SegmentTree(const vector<T>& a):size(NextPow2(a.size())),data(2*size,data_unit),index(2*size,-1){
		copy(all(a),begin(data)+size);
		peri(i,1,size) data[i]=Merge(data[i*2],data[i*2+1]);
		iota(begin(index)+size,begin(index)+size+a.size(),0);
		peri(i,1,size) index[i]=Merge(data[i*2],data[i*2+1])==data[i*2]?index[i*2]:index[i*2+1];
	}
	void PointUpdate(int i,T x){
		data[size+i]=Apply(x,data[size+i]);
		for(i+=size;i/=2;){
			data[i]=Merge(data[i*2],data[i*2+1]);
			index[i]=data[i]==data[i*2]?index[i*2]:index[i*2+1];
		}
	}
	T Get(int i){
		return i==-1?data_unit:data[size+i];
	}
	int RangeQueryIndex(int a,int b,int i,int l,int r){
		if(b<=l||r<=a) return -1;
		if(a<=l&&r<=b) return index[i];
		int u=RangeQueryIndex(a,b,i*2,l,(l+r)/2),v=RangeQueryIndex(a,b,i*2+1,(l+r)/2,r);
		return Merge(Get(u),Get(v))==Get(u)?u:v;
	}
	int RangeQueryIndex(int a,int b){return RangeQueryIndex(a,b,1,0,size);}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(ll n,m,d;cin>>n>>m>>d&&n|m|d;){
		vi a(n);
		rep(i,n) cin>>a[i];

		if(d*(m-1)+1>n){
			cout<<-1<<endl;
			continue;
		}

		SegmentTree st(n);
		rep(i,n) st.PointUpdate(i,a[i]);

		vl res;
		for(int i=0,j=0;j<m;i+=d,j++){
			// 次の文字として d*(m-j-1)+1<=n-i を満たすような argmin_i s[i] を選ぶ
			i=st.RangeQueryIndex(i,n-(d*(m-j-1)+1)+1);
			res.push_back(a[i]);
		}

		rep(i,m) cout<<res[i]<<"\n "[i+1<m];
	}
}
