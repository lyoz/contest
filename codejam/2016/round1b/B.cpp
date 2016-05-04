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

//constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Solver{
	void input();
	string solve();
	string a,b;
};

void Solver::input()
{
	a.reserve(1); cin>>a;
	b.reserve(1); cin>>b;
}

constexpr ll INF=1ll<<61;
const tuple<ll,string,string> TINF=make_tuple(INF,"","");

auto calc(string a,string b,int i)
{
	int n=a.size();
	rep(j,i+1) if(a[i]>b[i]) return TINF;
	repi(j,i+1,n) if(a[j]=='?') a[j]='9';
	repi(j,i+1,n) if(b[j]=='?') b[j]='0';
	if(a>b) return TINF;
	return mt(stoll(b)-stoll(a),a,b);
}

auto calc(string a,string b)
{
	int n=a.size();
	auto res=TINF;
	rep(i,n){
		if(a[i]=='?' && b[i]=='?'){
			a[i]='0',b[i]='1';
			res=min(res,calc(a,b,i));
			a[i]=b[i]='0';
		}
		else if(a[i]=='?'){
			a[i]=max<char>(b[i]-1,'0');
			res=min(res,calc(a,b,i));
			a[i]=b[i];
		}
		else if(b[i]=='?'){
			b[i]=min<char>(a[i]+1,'9');
			res=min(res,calc(a,b,i));
			b[i]=a[i];
		}
		else{
			res=min(res,calc(a,b,i));
		}
		res=min(res,calc(a,b,i));
	}
	return res;
}

string Solver::solve()
{
	auto res1=calc(a,b),res2=calc(b,a);
	swap(get<1>(res2),get<2>(res2));
	auto res=min(res1,res2);
	return get<1>(res)+" "+get<2>(res);
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
