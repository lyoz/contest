#include <bits/stdc++.h>
using namespace std;

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

// BEGIN CUT HERE
#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
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
// END CUT HERE

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Edge{
	int src,dst;
	Edge(){}
	Edge(int s,int d):src(s),dst(d){}
};
using Graph=vector<vector<Edge>>;

void DFS(const Graph& g,int v,vi& vis,vi& order)
{
	if(vis[v]) return;
	vis[v]=1;
	for(auto e:g[v]) DFS(g,e.dst,vis,order);
	order.push_back(v);
}

vvi SCC(const Graph& g)
{
	int n=g.size();
	vi vis(n),order;
	rep(i,n) DFS(g,i,vis,order);
	Graph t(n);
	rep(i,n) for(auto e:g[i])
		t[e.dst].emplace_back(e.dst,e.src);
	fill(all(vis),0);
	vvi res;
	per(i,n) if(!vis[order[i]]){
		res.resize(res.size()+1);
		DFS(t,order[i],vis,res.back());
	}
	return res;
}

void add_clause(Graph& g,int u,int v)
{
	int m=g.size()/2;
	int nu=u<m?u+m:u-m,nv=v<m?v+m:v-m;
	g[nu].emplace_back(nu,v);
	g[nv].emplace_back(nv,u);
}

bool TwoSat(int n,vector<tuple<int,int>>& cs)
{
	Graph g(2*n);
	for(auto c:cs){
		int u,v; tie(u,v)=c;
		int nu=u<n?u+n:u-n,nv=v<n?v+n:v-n;
		g[nu].emplace_back(nu,v);
		g[nv].emplace_back(nv,u);
	}
	auto scc=SCC(g);
	vi rs(2*n);
	rep(i,scc.size()) for(int v:scc[i]) rs[v]=i;
	rep(i,n) if(rs[i]==rs[n+i]) return false;
	return true;
}

struct OrAndSum{
	string isPossible(vector<long long> pairOr, vector<long long> pairSum){
		int n=pairOr.size();
		vector<ll> pairAnd(n);
		rep(i,n) pairAnd[i]=pairSum[i]-pairOr[i];

		vector<tuple<int,int>> cs;
		int m=60*(n+1);
		rep(i,n) rep(j,60){
			int u=i*60+j,v=(i+1)*60+j;
			int a=pairAnd[i]>>j&1,o=pairOr[i]>>j&1;
			if(a==1&&o==0)
				return "Impossible";
			if(a==0&&o==0){
				cs.emplace_back(m+u,m+u);
				cs.emplace_back(m+v,m+v);
			}
			if(a==0&&o==1){
				cs.emplace_back(u,v);
				cs.emplace_back(m+u,m+v);
			}
			if(a==1&&o==1){
				cs.emplace_back(u,u);
				cs.emplace_back(v,v);
			}
		}
		return TwoSat(m,cs)?"Possible":"Impossible";
	}
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			long long pairOr[]        = {7};
			long long pairSum[]       = {11};
			string expected__         = "Possible";
			std::clock_t start__      = std::clock();
			string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long pairOr[]        = {11};
			long long pairSum[]       = {7};
			string expected__         = "Impossible";
			std::clock_t start__      = std::clock();
			string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long pairOr[]        = {3, 3, 7, 5, 7};
			long long pairSum[]       = {3, 5, 7, 9, 11};
			string expected__         = "Possible";
			std::clock_t start__      = std::clock();
			string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long pairOr[]        = {1, 100, 1000};
			long long pairSum[]       = {100, 1000, 10000};
			string expected__         = "Impossible";
			std::clock_t start__      = std::clock();
			string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long pairOr[]        = {261208776456074191LL, 261208776456074191LL, 261208776456074191LL};
			long long pairSum[]       = {333333333333333333LL, 333333333333333333LL, 333333333333333333LL};
			string expected__         = "Possible";
			std::clock_t start__      = std::clock();
			string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long pairOr[]        = {0};
			long long pairSum[]       = {0};
			string expected__         = "Possible";
			std::clock_t start__      = std::clock();
			string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 6: {
		   long long pairOr[]        = {0,0,0,1};
		   long long pairSum[]       = {0,0,0,2};
		   string expected__         = "Impossible";
		   std::clock_t start__      = std::clock();
		   string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 7: {
		//   long long pairOr[]        = ;
		//   long long pairSum[]       = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 8: {
		//   long long pairOr[]        = ;
		//   long long pairSum[]       = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = OrAndSum().isPossible(vector<long long>(pairOr, pairOr + (sizeof pairOr / sizeof pairOr[0])), vector<long long>(pairSum, pairSum + (sizeof pairSum / sizeof pairSum[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		default:
			return -1;
		}
	}
}

#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
