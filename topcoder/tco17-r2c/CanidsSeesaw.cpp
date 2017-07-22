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

struct CanidsSeesaw{
	int calc(const vi& wolf,const vi& fox,const vi& is){
		int wsum=0,fsum=0,res=0;
		rep(i,wolf.size()){
			wsum+=wolf[i];
			fsum+=fox[is[i]];
			res+=wsum<fsum;
		}
		return res;
	}
	vector <int> construct(vector <int> wolf, vector <int> fox, int k){
		int n=wolf.size();
		vi is(n); iota(all(is),0);
		sort(all(is),[&](int i,int j){return fox[i]<fox[j];});
		if(calc(wolf,fox,is)==k)
			return is;
		rep(i,n) peri(j,i+1,n)
			if(fox[is[j-1]]<fox[is[j]]){
				swap(is[j-1],is[j]);
				if(calc(wolf,fox,is)==k)
					return is;
			}
		return vi();
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
			int wolf[]                = {3,1};
			int fox[]                 = {4,2};
			int k                     = 1;
			int expected__[]          = {1, 0 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int wolf[]                = {1,3};
			int fox[]                 = {4,2};
			int k                     = 1;
			int expected__[]          = { };
			std::clock_t start__      = std::clock();
			vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int wolf[]                = {10,10,10,10,10,10,10,10,10,10};
			int fox[]                 = {1,100,1,100,1,100,1,100,1,100};
			int k                     = 7;
			int expected__[]          = {0, 2, 4, 1, 6, 3, 5, 7, 9, 8 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int wolf[]                = {10,10,10,10,10,10,10,10,10,10};
			int fox[]                 = {1,100,1,100,1,100,1,100,1,100};
			int k                     = 4;
			int expected__[]          = { };
			std::clock_t start__      = std::clock();
			vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int wolf[]                = {2};
			int fox[]                 = {1};
			int k                     = 0;
			int expected__[]          = {0 };
			std::clock_t start__      = std::clock();
			vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

		//case 5: {
		//   int wolf[]                = ;
		//   int fox[]                 = ;
		//   int k                     = ;
		//   int expected__[]          = ;
		//   std::clock_t start__      = std::clock();
		//   vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
		//   return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		//}
		//case 6: {
		//   int wolf[]                = ;
		//   int fox[]                 = ;
		//   int k                     = ;
		//   int expected__[]          = ;
		//   std::clock_t start__      = std::clock();
		//   vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
		//   return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		//}
		//case 7: {
		//   int wolf[]                = ;
		//   int fox[]                 = ;
		//   int k                     = ;
		//   int expected__[]          = ;
		//   std::clock_t start__      = std::clock();
		//   vector <int> received__   = CanidsSeesaw().construct(vector <int>(wolf, wolf + (sizeof wolf / sizeof wolf[0])), vector <int>(fox, fox + (sizeof fox / sizeof fox[0])), k);
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
