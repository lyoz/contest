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
	int h,n;
	vs ss;
	void input();
	string solve();
};

void Solver::input()
{
	cin>>h>>n;
	ss.resize(n);
	rep(i,n) cin>>ss[i];
}

double calc(int x,int y,int h)
{
	if(h<=0) return 1;
	if(h>x*y) return 0;
	vd p(x*y+1);
	p[0]=1;
	rep(i,x){
		vd q(x*y+1);
		repi(j,1,y+1)
			repi(k,j,x*y+1)
				q[k]+=p[k-j]/y;
		p=move(q);
	}
	return accumulate(h+all(p),0.);
}

string Solver::solve()
{
	vector<double> ps;
	for(auto s:ss){
		int i=s.find('d');
		int j=s.find_first_of("-+");
		if(j==-1){
			int x=stoi(s.substr(0,i));
			int y=stoi(s.substr(i+1));
			ps.push_back(calc(x,y,h));
		}
		else{
			int x=stoi(s.substr(0,i));
			int y=stoi(s.substr(i+1,j-(i+1)));
			int z=stoi(s.substr(j));
			ps.push_back(calc(x,y,h-z));
		}
	}

	char res[20];
	sprintf(res,"%.9f",*max_element(all(ps)));
	return res;
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
