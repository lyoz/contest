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

struct ScoresSequence{
	int count(vector <int> s){
		int n=s.size();
		sort(all(s));

		vi sum(n);
		partial_sum(all(s),begin(sum));
		int prev=0,res=0;
		rep(i,n)
			if(sum[i]==i*(i+1)/2){
				res+=(i+1)*(i+1-prev);
				prev=i+1;
			}
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
			int s[]                   = {2, 0, 1};
			int expected__            = 6;
			std::clock_t start__      = std::clock();
			int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int s[]                   = {1, 0, 2};
			int expected__            = 6;
			std::clock_t start__      = std::clock();
			int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int s[]                   = {1, 1, 1};
			int expected__            = 9;
			std::clock_t start__      = std::clock();
			int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int s[]                   = {0, 2, 8, 4, 3, 9, 1, 5, 7, 6};
			int expected__            = 55;
			std::clock_t start__      = std::clock();
			int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int s[]                   = {22,20,14,13,17,15,12,18,23,15,21,26,33,5,19,9,37,0,25,28,4,12,35,32,25,7,31,6,2,29,10,33,36,27,39,28,40,3,8,38,3};
			int expected__            = 1422;
			std::clock_t start__      = std::clock();
			int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 5: {
		   int s[]                   = {34, 74, 4, 36, 49, 94, 51, 20, 73, 23, 73, 11, 71, 61, 60, 83, 29, 3, 57, 84, 94, 62, 94, 61, 93, 62, 3, 3, 80, 94, 21, 76, 10, 16, 3, 84, 94, 73, 10, 28, 34, 49, 97, 27, 58, 40, 4, 63, 62, 94, 50, 41, 33, 42, 20, 22, 64, 70, 40, 14, 48, 62, 72, 15, 48, 20, 57, 50, 39, 12, 25, 35, 46, 28, 35, 41, 21, 69, 29, 12, 49, 83, 15, 6, 83, 83, 85, 86, 74, 92, 50, 82, 94, 49, 30, 10, 94, 64, 2, 80};
		   int expected__            = 5477;
		   std::clock_t start__      = std::clock();
		   int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 6: {
		//   int s[]                   = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   int s[]                   = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = ScoresSequence().count(vector <int>(s, s + (sizeof s / sizeof s[0])));
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
