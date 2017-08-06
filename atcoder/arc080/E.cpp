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

vector<tuple<int,int>> solve_naive(vi a)
{
	int n=a.size();
	vector<tuple<int,int>> res;
	if(n>0){
		int i1=0;
		for(int i=2;i<n;i+=2)
			if(a[i]<a[i1])
				i1=i;
		int i2=i1+1;
		for(int i=i2+2;i<n;i+=2)
			if(a[i]<a[i2])
				i2=i;
		for(auto t:solve_naive(vi(begin(a),begin(a)+i1)))
			res.push_back(t);
		for(auto t:solve_naive(vi(begin(a)+i1+1,begin(a)+i2)))
			res.push_back(t);
		for(auto t:solve_naive(vi(begin(a)+i2+1,end(a))))
			res.push_back(t);
		sort(all(res));
		res.emplace(begin(res),a[i1],a[i2]);
	}
	return res;
}

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

template<typename T>
struct functor_traits:public functor_traits<decltype(&T::operator())>{};
template<typename C,typename Ret,typename... Args>
struct functor_traits<Ret(C::*)(Args...)const>{
	template<size_t I>
	using nth_argument_type=typename tuple_element<I,tuple<Args...>>::type;
	using first_argument_type=nth_argument_type<0>;
};
template<typename Compare,typename T=typename decay<typename functor_traits<Compare>::first_argument_type>::type>
priority_queue<T,vector<T>,Compare> make_priority_queue(Compare comp){
	return priority_queue<T,vector<T>,Compare>(comp);
}

auto f(SegmentTree& ste,SegmentTree& sto,int l,int r)
{
	int i,j;
	if(l%2==0){
		i=ste.QueryIndex(l,r);
		j=sto.QueryIndex(i,r);
	}
	else{
		i=sto.QueryIndex(l,r);
		j=ste.QueryIndex(i,r);
	}
	return mt(i,j,l,r);
}

vector<tuple<int,int>> solve(const vi& a)
{
	int n=a.size();
	SegmentTree ste(a),sto(a);
	rep(i,n){
		if(i%2==0)
			sto.Update(i,INF);
		else
			ste.Update(i,INF);
	}

	vector<tuple<int,int>> res;

	auto pq=make_priority_queue([&](tuple<int,int,int,int> x,tuple<int,int,int,int> y){
		int i1,j1,l1,r1; tie(i1,j1,l1,r1)=x;
		int i2,j2,l2,r2; tie(i2,j2,l2,r2)=y;
		return mt(a[i1],a[j1])>mt(a[i2],a[j2]);
	});

	int i0,j0; tie(i0,j0)=calc(ste,sto,0,n);
	pq.emplace(i0,j0,0,n);
	while(pq.size()){
		int i,j,l,r; tie(i,j,l,r)=pq.top(); pq.pop();
		res.emplace_back(a[i],a[j]);
		if(l<i){
			int ii,jj; tie(ii,jj)=calc(ste,sto,l,i);
			pq.emplace(ii,jj,l,i);
		}
		if(i+1<j){
			int ii,jj; tie(ii,jj)=calc(ste,sto,i+1,j);
			pq.emplace(ii,jj,i+1,j);
		}
		if(j+1<r){
			int ii,jj; tie(ii,jj)=calc(ste,sto,j+1,r);
			pq.emplace(ii,jj,j+1,r);
		}
	}
	return res;
}

int main()
{
	for(int n;cin>>n&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];

		auto res=solve(a);
		rep(i,n/2)
			cout<<get<0>(res[i])<<' '<<get<1>(res[i])<<"\n "[i+1<n/2];
	}
}
