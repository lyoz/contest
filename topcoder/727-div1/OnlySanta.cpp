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

struct OnlySanta{
	string solve(string S){
		int ni=S.find_last_of('N');
		if(ni==-1)
			S="SAN"+S;
		else{
			int ai=S.find_last_of('A',ni);
			if(ai==-1)
				S="SA"+S;
			else
				S=S.substr(0,ai)+"S"+S.substr(ai);
		}
		return S+"TA";
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
			string S                  = "STANA";
			string expected__         = "STANTA";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S                  = "STN";
			string expected__         = "SANTNA";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S                  = "RATSNOOOA";
			string expected__         = "DEARATSNOOOSANTA";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S                  = "SXAYNTA";
			string expected__         = "OOOOSOXAYNTOOOOAOOO";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S                  = "SNTA";
			string expected__         = "SANTA";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S                  = "ASNTA";
			string expected__         = "SASNTAS";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string S                  = "NIELATA";
			string expected__         = "SANIELATAJA";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			string S                  = "X";
			string expected__         = "SSAAXNNTTAA";
			std::clock_t start__      = std::clock();
			string received__         = OnlySanta().solve(S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 8: {
		   string S                  = "ATAN";
		   string expected__         = "ATSANTA";
		   std::clock_t start__      = std::clock();
		   string received__         = OnlySanta().solve(S);
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 9: {
		//   string S                  = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = OnlySanta().solve(S);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 10: {
		//   string S                  = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = OnlySanta().solve(S);
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
