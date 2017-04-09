#include <bits/stdc++.h>
#include <omp.h>
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

struct Solver{
	ll n,k;
	void input();
	string solve();
};

void Solver::input()
{
	cin>>n>>k;
}

string solve_small_2(ll n,ll k)
{
	priority_queue<ll> pq;
	pq.push(n);
	ll mn,mx;
	rep(_,k){
		ll x=pq.top(); pq.pop();
		mn=(x-1)/2,mx=x-1-mn;
		pq.push(mn);
		pq.push(mx);
	}
	return to_string(mx)+' '+to_string(mn);
}

string solve_large(ll n,ll k)
{
	map<ll,ll> f;
	f.emplace(n,1);
	for(;;){
		auto it=--end(f);
		ll w,c; tie(w,c)=*it;
		f.erase(it);
		ll mn=(w-1)/2,mx=w/2;
		if(c>=k)
			return to_string(mx)+' '+to_string(mn);
		k-=c;
		f[mn]+=c;
		f[mx]+=c;
	}
}

string Solver::solve()
{
	//return solve_small_2(n,k);
	return solve_large(n,k);
}

int main()
{
	int T; cin>>T;
	vector<Solver> solvers(T);
	rep(i,T) solvers[i].input();
	
	vector<string> results(T);
	#ifndef _OPENMP
	fputs("------- run with single thread -------\n",stderr);
	#else
	fprintf(stderr,"------- run with %d threads -------\n",omp_get_max_threads());
	#pragma omp parallel for schedule(dynamic)
	#endif
	rep(i,T){
		results[i]=solvers[i].solve();
		fprintf(stderr,"#%d finish\n",i+1);
	}
	
	rep(i,T) printf("Case #%d: %s\n",i+1,results[i].c_str());
}
