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

struct FiveRooks{
	vector <int> find(vector <string> board){
		vi is(8),js(8);
		iota(all(is),0);
		iota(all(js),0);
		do{
			do{
				bool ok=true;
				rep(k,5) ok&=board[is[k]][js[k]]=='R';
				if(ok){
					vi res;
					rep(k,5){
						res.push_back(is[k]);
						res.push_back(js[k]);
					}
					return res;
				}
				reverse(5+all(js));
			}while(next_permutation(all(js)));
			reverse(5+all(is));
		}while(next_permutation(all(is)));
		assert(0);
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
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, std::clock_t elapsed) { 
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
			string board[]            = {
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"R.......",
"........",
"........",
"........"
};
			int expected__[]          = {0, 7, 1, 3, 2, 4, 3, 6, 4, 0 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string board[]            = {
"R.R.R.R.",
".R.R.R.R",
"R.R.R.R.",
".R.RRR.R",
"R.R.R.R.",
".R.R.R.R",
"R.R.R.R.",
".R.R.R.R"
};
			int expected__[]          = {0, 0, 1, 7, 2, 6, 3, 5, 4, 4 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string board[]            = {
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR",
"RRRRRRRR"
};
			int expected__[]          = {0, 7, 1, 3, 2, 4, 3, 6, 4, 0 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string board[]            = {
".RRRRRR.",
"RRRRRRRR",
"....RRRR",
"...RRRR.",
"..RRRR..",
".RRRR...",
"RRRR....",
"RRR....."
}
;
			int expected__[]          = {1, 7, 2, 6, 3, 5, 4, 4, 5, 3 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string board[]            = {
".RRRRRR.",
"RRRRRRRR",
"....RRRR",
"...RRRR.",
"..RRRR..",
".RRRR...",
"RRRRRRRR",
".RRRRRR."
};
			int expected__[]          = {1, 7, 2, 6, 3, 5, 4, 4, 5, 3 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			string board[]            = 
{
".RRRRRR.",
"RRRRRRRR",
".RRRR...",
"..RRRR..",
"...RRRR.",
"....RRRR",
"RRRRRRRR",
".RRRRRR."
};
			int expected__[]          = {1, 7, 3, 5, 4, 4, 6, 2, 7, 1 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

		case 6: {
		   string board[]            = {
				 "........",
				 "........",
				 "........",
				 ".......R",
				 "......R.",
				 ".....R..",
				 "....R...",
				 "...R....",
			 };
		   int expected__[]          = {7,7,6,6,5,5,4,4,3,3};
		   std::clock_t start__      = std::clock();
		   vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
		   return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		//case 7: {
		//   string board[]            = ;
		//   int expected__[]          = ;
		//   std::clock_t start__      = std::clock();
		//   vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
		//   return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		//}
		//case 8: {
		//   string board[]            = ;
		//   int expected__[]          = ;
		//   std::clock_t start__      = std::clock();
		//   vector <int> received__   = FiveRooks().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
		//   return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
