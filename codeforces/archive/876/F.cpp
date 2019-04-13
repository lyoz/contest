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

ll solve(vi a)
{
	constexpr int B=32;
	int n=a.size();

	vvi b(B);
	rep(i,B){
		b[i].push_back(-1);
		rep(j,n) if(a[j]>>i&1)
			b[i].push_back(j);
		b[i].push_back(n);
	}

	vi is(n); iota(all(is),0);
	sort(all(is),[&](int i,int j){return a[i]>a[j];});

	set<int> s={-1,n};

	ll res=0;
	for(int i:is){
		int l,r;
		{
			auto it=s.lower_bound(i);
			r=*it; l=*--it;
		}
		int l2=l,r2=r;
		rep(j,B) if(!(a[i]>>j&1)){
			auto it=lower_bound(all(b[j]),i);
			r2=min(r2,*it);
			l2=max(l2,*--it);
		}
		res+=ll(i-l)*(r-i)-ll(i-l2)*(r2-i);
		s.insert(i);
	}
	return res;
}

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
		cout<<solve(a)<<endl;
	}
}
