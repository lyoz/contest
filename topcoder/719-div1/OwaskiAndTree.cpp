#include <bits/stdc++.h>
using namespace std;

#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple

using uint=unsigned int;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vs=vector<string>;

// BEGIN CUT HERE
#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl
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
// END CUT HERE

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct OwaskiAndTree{
	int dfs(const vvi& t,const vi& pleasure,int phase,int u,vvi& memo){
		if(memo[phase][u]!=-1) return memo[phase][u];
		int sum=phase==0?0:pleasure[u];
		for(int v:t[u])
			sum+=dfs(t,pleasure,phase,v,memo);
		int res=phase==0?dfs(t,pleasure,1,u,memo):0;
		return memo[phase][u]=max(res,sum);
	}
	int maximalScore(vector <int> parent, vector <int> pleasure){
		int n=pleasure.size();
		vvi t(n);
		rep(i,n-1)
			t[parent[i]].push_back(i+1);
		vvi memo(2,vi(n,-1));
		int res=dfs(t,pleasure,0,0,memo);
		return res;
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
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int parent[]              = {0, 1, 2, 3, 4, 5, 6, 7, 8};
			int pleasure[]            = {1, 1, -1, -1, -1, -1, 1, 1, 1, 1};
			int expected__            = 4;
			std::clock_t start__      = std::clock();
			int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int parent[]              = {0, 0, 1, 2};
			int pleasure[]            = {2, 3, 4, -1, -1};
			int expected__            = 9;
			std::clock_t start__      = std::clock();
			int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int parent[]              = {0, 0, 1, 1, 2, 2, 5, 5};
			int pleasure[]            = {1, 2, -3, -7, 3, 2, 7, -1, 3};
			int expected__            = 17;
			std::clock_t start__      = std::clock();
			int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int parent[]              = {0, 1, 1, 1, 0, 3, 1, 3, 4, 4, 3, 6, 8, 0, 12, 12, 11, 7, 7};
			int pleasure[]            = {-154011, 249645, 387572, 292156, -798388, 560085, -261135, -812756, 191481, -165204, 81513, -448791, 608073, 354614, -455750, 325999, 227225, -696501, 904692, -297238};
			int expected__            = 3672275;
			std::clock_t start__      = std::clock();
			int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int parent[]              = {};
			int pleasure[]            = {-1};
			int expected__            = 0;
			std::clock_t start__      = std::clock();
			int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 5: {
		   int parent[]              = {0,1,2,3};
		   int pleasure[]            = {1,1,-1,1,1};
		   int expected__            = 3;
		   std::clock_t start__      = std::clock();
		   int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 6: {
		//   int parent[]              = ;
		//   int pleasure[]            = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   int parent[]              = ;
		//   int pleasure[]            = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = OwaskiAndTree().maximalScore(vector <int>(parent, parent + (sizeof parent / sizeof parent[0])), vector <int>(pleasure, pleasure + (sizeof pleasure / sizeof pleasure[0])));
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
