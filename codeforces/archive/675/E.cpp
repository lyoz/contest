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

int NextPow2(int x)
{
	x--;
	for(int i=1;i<32;i*=2) x|=x>>i;
	return x+1;
}
const int I=-INF;
int F(int a,int b){return max(a,b);}

struct SegmentTree{
	int size;
	vi data,index;
	SegmentTree(int n):size(NextPow2(n)),data(size,I),index(size*2){
		iota(size+all(index),0);
		peri(i,1,size) index[i]=index[i*2];
	}
	SegmentTree(const vi& a):size(NextPow2(a.size())),data(size,I),index(size*2){
		copy(all(a),begin(data));
		iota(size+all(index),0);
		peri(i,1,size){
			int u=index[i*2],v=index[i*2+1];
			index[i]=data[u]==F(data[u],data[v])?u:v;
		}
	}
	void Update(int i,int x){
		data[i]=x;
		for(i+=size;i/=2;){
			int u=index[i*2],v=index[i*2+1];
			index[i]=data[u]==F(data[u],data[v])?u:v;
		}
	}
	int QueryIndex(int a,int b,int i,int l,int r){
		if(b<=l || r<=a) return -1;
		if(a<=l && r<=b) return index[i];
		int u=QueryIndex(a,b,i*2,l,(l+r)/2),v=QueryIndex(a,b,i*2+1,(l+r)/2,r);
		if(u==-1 || v==-1) return u!=-1?u:v;
		return data[u]==F(data[u],data[v])?u:v;
	}
	int QueryIndex(int a,int b){
		return QueryIndex(a,b,1,0,size);
	}
};

int main()
{
	for(int n;cin>>n && n;){
		vi a(n); a[n-1]=n-1;
		rep(i,n-1) cin>>a[i],a[i]--;
		
		SegmentTree st(a);
		vl dp(n);
		per(i,n-1){
			int j=st.QueryIndex(i+1,a[i]+1);
			dp[i]=dp[j]+n+j-a[i]-i-1;
		}
		cout<<accumulate(all(dp),0ll)<<endl;
	}
}
