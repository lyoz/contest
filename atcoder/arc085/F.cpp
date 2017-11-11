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

int NextPow2(int x)
{
	x--;
	for(int i=1;i<32;i*=2) x|=x>>i;
	return x+1;
}

const int I=INF;
int F(int a,int b){return min(a,b);}

struct SegmentTree{
	int size;
	vi data;
	SegmentTree(int n):size(NextPow2(n)),data(size*2,I){}
	SegmentTree(const vi& a):size(NextPow2(a.size())),data(size*2,I){
		copy(all(a),begin(data)+size);
	}
	void Update(int a,int b,int x,int i,int l,int r){
		if(b<=l || r<=a) return;
		if(a<=l && r<=b){
			data[i]=F(data[i],x);
			return;
		}
		Update(a,b,x,i*2+0,l,(l+r)/2);
		Update(a,b,x,i*2+1,(l+r)/2,r);
	}
	void Update(int a,int b,int x){
		Update(a,b,x,1,0,size);
	}
	int Query(int i){
		int res=I;
		for(i+=size;i;i/=2) res=F(res,data[i]);
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
		vi b(n);
		rep(i,n) cin>>b[i];
		vector<tuple<int,int,int>> qs;
		rep(i,n) qs.emplace_back(i,i+1,0);
		int q; cin>>q;
		rep(i,q){
			int l,r; cin>>l>>r; l--;
			qs.emplace_back(l,r,1);
		}

		sort(all(qs),[](auto x,auto y){
			return mt(get<1>(x),get<2>(x))<mt(get<1>(y),get<2>(y));
		});

		SegmentTree st(n+1);
		st.Update(0,1,count(all(b),0));
		rep(i,qs.size()){
			int l,r,t; tie(l,r,t)=qs[i];
			int x=st.Query(l);
			if(t==0)
				st.Update(r,r+1,x+(b[l]==0?-1:1));
			else
				st.Update(l+1,r+1,x);
		}
		cout<<st.Query(n)<<endl;
	}
}
