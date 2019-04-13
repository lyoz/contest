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
	const T data_unit=-1;
	T Merge(T a,T b){
		return max(a,b);
	}
	T Apply(T x,T d){
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
		return data[size+i];
	}
	int RangeQueryIndex(int a,int b,int i,int l,int r){
		if(b<=l||r<=a) return -1;
		if(a<=l&&r<=b) return index[i];
		int u=RangeQueryIndex(a,b,i*2,l,(l+r)/2),v=RangeQueryIndex(a,b,i*2+1,(l+r)/2,r);
		return v==-1||Merge(Get(u),Get(v))==Get(u)?u:v;
	}
	int RangeQueryIndex(int a,int b){return RangeQueryIndex(a,b,1,0,size);}
};

int solve_naive(vi a)
{
	int n=a.size();
	int res=-1,mx=-1;
	rep(i,n){
		int cnt=0;
		rep(j,n) if(j!=i){
			bool ok=true;
			rep(k,j) if(k!=i) ok&=a[k]<a[j];
			if(ok) cnt++;
		}
		if(mx<cnt||mx==cnt&&a[res]>a[i]){
			mx=cnt;
			res=i;
		}
	}
	return a[res];
}

int solve(vi a)
{
	int n=a.size();
	SegmentTree st(a);
	vi b(n);
	rep(i,n){
		int j=st.RangeQueryIndex(0,i+1);
		if(j==i)  // i番目はrecordなので消すと1減る
			b[i]--;
		else{
			int x=a[j];
			st.PointUpdate(j,-1);
			if(st.RangeQueryIndex(0,i+1)==i)  // j番目を消すとi番目がrecordになる
				b[j]++;
			st.PointUpdate(j,x);
		}
	}
	int mx=-INF,res=-1;
	rep(i,n) if(mx<b[i]||mx==b[i]&&res>a[i]){
		mx=b[i];
		res=a[i];
	}
	return res;
}

void test()
{
	mt19937 r;
	rep(tc,100){
		dump(tc);
		vi a(100); iota(all(a),1);
		shuffle(all(a),r);
		int ans=solve_naive(a);
		int res=solve(a);
		if(res!=ans){
			dump(a,ans,res);
			break;
		}
	}
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	//test();

	for(int n;cin>>n&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];
		cout<<solve(a)<<endl;
	}
}
