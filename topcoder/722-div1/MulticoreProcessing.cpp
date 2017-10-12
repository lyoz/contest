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

struct MulticoreProcessing{
	long double calc(ll jobLength,ll corePenalty,ll speed,ll core){
		return 1.l*jobLength/(core*speed)+(core-1)*corePenalty;
	}
	long long fastestTime(long long jobLength, int corePenalty, vector <int> speed, vector <int> cores){
		ll res=LLONG_MAX;
		rep(i,speed.size()){
			ll c0=1,c3=cores[i];
			while(c3-c0>=3){
				ll c1=(2*c0+c3)/3;
				ll c2=(c0+2*c3)/3;
				if(calc(jobLength,corePenalty,speed[i],c1)>calc(jobLength,corePenalty,speed[i],c2))
					c0=c1;
				else
					c3=c2;
			}
			for(ll c=c0;c<=c3;c++)
				res=min<ll>(res,ceil(calc(jobLength,corePenalty,speed[i],c)));
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
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
			long long jobLength       = 2000;
			int corePenalty           = 5;
			int speed[]               = {40,20};
			int cores[]               = {2,4};
			long long expected__      = 30;
			std::clock_t start__      = std::clock();
			long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long jobLength       = 2000;
			int corePenalty           = 5;
			int speed[]               = {10,20};
			int cores[]               = {2,4};
			long long expected__      = 40;
			std::clock_t start__      = std::clock();
			long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long jobLength       = 1000;
			int corePenalty           = 0;
			int speed[]               = {10};
			int cores[]               = {3};
			long long expected__      = 34;
			std::clock_t start__      = std::clock();
			long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long jobLength       = 10000;
			int corePenalty           = 5;
			int speed[]               = {39,37,44};
			int cores[]               = {8,16,6};
			long long expected__      = 63;
			std::clock_t start__      = std::clock();
			long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 4: {
		   long long jobLength       = 10000000000;
		   int corePenalty           = 1;
		   int speed[]               = {1};
		   int cores[]               = {1000000000};
		   long long expected__      = 199999;
		   std::clock_t start__      = std::clock();
		   long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
		   long long jobLength       = 430675856537057621;
		   int corePenalty           = 754291586;
		   int speed[]               = {1};
		   int cores[]               = {5};
		   long long expected__      = 86135174324577869;
		   std::clock_t start__      = std::clock();
		   long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 6: {
		//   long long jobLength       = ;
		//   int corePenalty           = ;
		//   int speed[]               = ;
		//   int cores[]               = ;
		//   long long expected__      = ;
		//   std::clock_t start__      = std::clock();
		//   long long received__      = MulticoreProcessing().fastestTime(jobLength, corePenalty, vector <int>(speed, speed + (sizeof speed / sizeof speed[0])), vector <int>(cores, cores + (sizeof cores / sizeof cores[0])));
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
