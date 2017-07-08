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

struct DengklekGaneshAndChains{
	string getBestChains(vector <string> chains, vector <int> lengths){
		for(string& s:chains){
			string t;
			rep(i,s.size())
				t=max(t,s.substr(i)+s.substr(0,i));
			s=t;
		}
		sort(all(chains),greater<string>());

		int n=chains.size();
		vi used(n);
		string res;
		for(int len:lengths){
			int i=-1;
			per(j,n){
				if(used[j])
					continue;
				if(i==-1||chains[i].substr(0,len)<chains[j].substr(0,len))
					i=j;
			}
			res+=chains[i].substr(0,len);
			used[i]=1;
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
			string chains[]           = {"topc", "oder", "open", "twob"};
			int lengths[]             = {2, 1, 3};
			string expected__         = "wotrod";
			std::clock_t start__      = std::clock();
			string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string chains[]           = {"ssh", "she", "see", "sea"};
			int lengths[]             = {2, 3, 2, 3};
			string expected__         = "ssshesesee";
			std::clock_t start__      = std::clock();
			string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string chains[]           = {"wri", "ter", "who", "are", "you"};
			int lengths[]             = {3};
			string expected__         = "you";
			std::clock_t start__      = std::clock();
			string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string chains[]           = {"harus", "imfyo"};
			int lengths[]             = {5, 5};
			string expected__         = "yoimfushar";
			std::clock_t start__      = std::clock();
			string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 4: {
		   string chains[]           = {"ba","bb"};
		   int lengths[]             = {1,2};
		   string expected__         = "bbb";
		   std::clock_t start__      = std::clock();
		   string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 5: {
		//   string chains[]           = ;
		//   int lengths[]             = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 6: {
		//   string chains[]           = ;
		//   int lengths[]             = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = DengklekGaneshAndChains().getBestChains(vector <string>(chains, chains + (sizeof chains / sizeof chains[0])), vector <int>(lengths, lengths + (sizeof lengths / sizeof lengths[0])));
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
