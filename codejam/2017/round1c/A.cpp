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
	int n,k;
	vi rs,hs;
	void input();
	string solve();
};

void Solver::input()
{
	cin>>n>>k;
	rs.resize(n);
	hs.resize(n);
	rep(i,n) cin>>rs[i]>>hs[i];
}

string Solver::solve()
{
	vi is(n); iota(all(is),0);
	sort(all(is),[&](int i,int j){
		ll a=2ll*rs[i]*hs[i];
		ll b=2ll*rs[j]*hs[j];
		return a>b;
	});

	ll res=0;
	for(int i:is){
		ll sum=ll(rs[i])*rs[i];
		if(count(begin(is),begin(is)+k,i)){
			rep(j,k)
				sum+=2ll*rs[is[j]]*hs[is[j]];
		}
		else{
			sum+=2ll*rs[i]*hs[i];
			rep(j,k-1)
				sum+=2ll*rs[is[j]]*hs[is[j]];
		}
		res=max(res,sum);
	}
	char buf[80];
	sprintf(buf,"%.9f",res*acos(-1));
	return buf;
}

int main()
{
	int T; cin>>T;
	vector<Solver> solvers(T);
	rep(i,T) solvers[i].input();
	fputs("------- input() finish -------\n",stderr);
	fflush(stderr);
	
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
		fflush(stderr);
	}
	
	rep(i,T) printf("Case #%d: %s\n",i+1,results[i].c_str());
}
