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
	int m,n;
	vi b1,e1,b2,e2;
	void input();
	string solve();
};

void Solver::input()
{
	cin>>m>>n;
	b1.resize(m);
	e1.resize(m);
	b2.resize(n);
	e2.resize(n);
	rep(i,m) cin>>b1[i]>>e1[i];
	rep(i,n) cin>>b2[i]>>e2[i];
}

template<typename T>
void chmin(T& a,const T& b)
{
	a=min(a,b);
}

string Solver::solve()
{
	{
		int mn=INF;
		rep(i,m) mn=min(mn,b1[i]);
		rep(i,n) mn=min(mn,b2[i]);
		rep(i,m) b1[i]-=mn,e1[i]-=mn;
		rep(i,n) b2[i]-=mn,e2[i]-=mn;
	}

	vi flg(24*60,-1);
	rep(i,b1.size()) repi(j,b1[i],e1[i]) flg[j]=0;
	rep(i,b2.size()) repi(j,b2[i],e2[i]) flg[j]=1;

	// [cameron or jamie][time][time for cameron] = minimum number of exchanges
	vector<vvi> dp(2,vvi(24*60+1,vi(24*60+1,INF)));
	dp[0][0][0]=dp[1][0][0]=0;
	rep(i,24*60){
		rep(j,24*60){
			rep(k,2){
				if(dp[k][i][j]==INF) continue;
				rep(l,2){
					if(flg[i]!=-1&&flg[i]!=l) continue;
					chmin(dp[l][i+1][j+(l==0)],dp[k][i][j]+(k!=l));
				}
			}
		}
	}

	return to_string(min(
		dp[0][24*60][24*60/2]+(flg[0]!=0),
		dp[1][24*60][24*60/2]+(flg[0]!=1)
  ));
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
