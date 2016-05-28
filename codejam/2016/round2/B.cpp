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
	void input();
	string solve_small();
	string solve();
	int n,k;
	vd ps;
};

void Solver::input()
{
	cin>>n>>k;
	ps.resize(n);
	rep(i,n) cin>>ps[i];
}

string Solver::solve_small()
{
	double res=0;
	for(int s=(1<<k)-1;!(s&1<<n);){
		vd qs;
		rep(i,n) if(s>>i&1) qs.push_back(ps[i]);
		
		vd dp(1,1);
		rep(i,k){
			vd dp2(dp.size()+1);
			rep(j,dp.size()){
				dp2[j]+=dp[j]*(1-qs[i]);
				dp2[j+1]+=dp[j]*qs[i];
			}
			swap(dp,dp2);
		}
		res=max(res,dp[k/2]);
		
		int lo=s&-s,lz=(s+lo)&~s;
		s=(s|lz)&~(lz-1);
		s|=(lz/lo/2-1);
	}
	char buf[80]; sprintf(buf,"%.9f",res);
	return buf;
}

vd calc(vd ps)
{
	vd dp(1,1);
	rep(i,ps.size()){
		vd dp2(dp.size()+1);
		rep(j,dp.size()){
			dp2[j]+=dp[j]*(1-ps[i]);
			dp2[j+1]+=dp[j]*ps[i];
		}
		swap(dp,dp2);
	}
	return dp;
}

string Solver::solve()
{
	sort(all(ps));
	double res=0;
	rep(i,k+1){
		vd qs;
		rep(j,i) qs.push_back(ps[j]);
		rep(j,k-i) qs.push_back(ps[n-1-j]);
		vd dp=calc(qs);
		res=max(res,dp[k/2]);
	}
	char buf[80]; sprintf(buf,"%.9f",res);
	return buf;
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
