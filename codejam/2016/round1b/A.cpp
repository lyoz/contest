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

struct Solver{
	void input();
	string solve();
	string s;
};


void Solver::input()
{
	s.reserve(1);
	cin>>s;
}

//'G':8,"EIGHT"
//'U':4,"FOUR"
//'W':2,"TWO"
//'X':6,"SIX"
//'Z':0,"ZERO"

//'F':5,"FIVE"
//'O':1,"ONE"
//'R':3,"THREE"
//'S':7,"SEVEN"

//'E':9,"NINE"

vector<char> cs={'G','U','W','X','Z','F','O','R','S','E'};
vi ns={8,4,2,6,0,5,1,3,7,9};
vs ss={"EIGHT","FOUR","TWO","SIX","ZERO","FIVE","ONE","THREE","SEVEN","NINE"};
	
string Solver::solve()
{
	map<char,int> f;
	for(char c:s) f[c]++;
	
	map<int,int> g;
	rep(i,10){
		int cnt=f[cs[i]];
		if(cnt==0) continue;
		g[ns[i]]=cnt;
		for(char c:ss[i])
			f[c]-=cnt;
	}
	
	string res;
	for(auto p:g) res+=string(p.second,'0'+p.first);
	return res;
}

int main()
{
	int T; cin>>T;
	vector<Solver> solvers(T);
	rep(i,T) solvers[i].input();
	
	vector<string> results(T);
	#pragma omp parallel for schedule(dynamic)
	rep(i,T){
		results[i]=solvers[i].solve();
		fprintf(stderr,"#%d finish\n",i+1);
	}
	
	rep(i,T) printf("Case #%d: %s\n",i+1,results[i].c_str());
}
