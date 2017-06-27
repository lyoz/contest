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

int LCS(const string& s1,const string& s2)
{
	vvi dp(2,vi(s2.size()+1));
	rep(i,s1.size()){
		rep(j,s2.size()){
			int ii=i+1,jj=j+1;
			if(s1[i]==s2[j])
				dp[ii&1][jj]=dp[(ii-1)&1][jj-1]+1;
			else
				dp[ii&1][jj]=max(dp[(ii-1)&1][jj-1],max(dp[(ii-1)&1][jj],dp[ii&1][jj-1]));
		}
	}
	return dp[s1.size()&1][s2.size()];
}

struct ConstructLCS{
	string construct(int ab, int bc, int ca){
		vi xs={ab,bc,ca};
		sort(all(xs));
		int x=xs[0],y=xs[1],z=xs[2];
		int n=y+z;
		vs res={
			string(n-x,'0')+string(x,'1'),
			string(n,'1'),
			string(y,'1')+string(n-y,'0'),
		};

		vi is={0,1,2};
		do{
			string a=res[is[0]],b=res[is[1]],c=res[is[2]];
			if(LCS(a,b)==ab&&LCS(b,c)==bc&&LCS(c,a)==ca)
				return a+" "+b+" "+c;
		}while(next_permutation(all(is)));

		return "#";
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
			int ab                    = 3;
			int bc                    = 4;
			int ca                    = 2;
			string expected__         = "101 1010101 1111";
			std::clock_t start__      = std::clock();
			string received__         = ConstructLCS().construct(ab, bc, ca);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int ab                    = 7;
			int bc                    = 4;
			int ca                    = 4;
			string expected__         = "10101010 1010101 1011";
			std::clock_t start__      = std::clock();
			string received__         = ConstructLCS().construct(ab, bc, ca);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int ab                    = 8;
			int bc                    = 7;
			int ca                    = 8;
			string expected__         = "110101001011 010101101 10101010";
			std::clock_t start__      = std::clock();
			string received__         = ConstructLCS().construct(ab, bc, ca);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int ab                    = 8;
			int bc                    = 6;
			int ca                    = 7;
			string expected__         = "110101010 10101010 1111010";
			std::clock_t start__      = std::clock();
			string received__         = ConstructLCS().construct(ab, bc, ca);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int ab                    = 15;
			int bc                    = 17;
			int ca                    = 19;
			string expected__         = "000100101101111011000 11110111010011101010 100100001010101001010101000011111";
			std::clock_t start__      = std::clock();
			string received__         = ConstructLCS().construct(ab, bc, ca);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int ab                    = 50;
			int bc                    = 50;
			int ca                    = 50;
			string expected__         = "11111111111111111111111111111111111111111111111111 11111111111111111111111111111111111111111111111111 11111111111111111111111111111111111111111111111111";
			std::clock_t start__      = std::clock();
			string received__         = ConstructLCS().construct(ab, bc, ca);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		//case 6: {
		//   int ab                    = ;
		//   int bc                    = ;
		//   int ca                    = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = ConstructLCS().construct(ab, bc, ca);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   int ab                    = ;
		//   int bc                    = ;
		//   int ca                    = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = ConstructLCS().construct(ab, bc, ca);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 8: {
		//   int ab                    = ;
		//   int bc                    = ;
		//   int ca                    = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = ConstructLCS().construct(ab, bc, ca);
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
