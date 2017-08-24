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

struct SumProduct{
	int modpow(int a,int r,int m){
		int x=1;
		for(;r;r>>=1){
			if(r&1) x=(ll)x*a%m;
			a=(ll)a*a%m;
		}
		return x;
	}
	int ncr(int n,int r){
		static ll memo[201][201]={};
		if(memo[n][r]) return memo[n][r];
		if(r==0||r==n) return memo[n][r]=1;
		return memo[n][r]=(ncr(n-1,r-1)+ncr(n-1,r))%MOD;
	}
	int calc(const vi& a,int m){
		vvl dp(11,vl(m+1));
		dp[0][0]=1;
		rep(i,10)
			rep(j,m+1)
				rep(k,min(j,a[i])+1)
					dp[i+1][j]=(dp[i+1][j]+dp[i][j-k]*ncr(m-(j-k),k))%MOD;
		return dp[10][m];
	}
	int findSum(vector <int> amount, int blank1, int blank2){
		ll res=0;
		rep(i,10) rep(j,10){
			amount[i]--; amount[j]--;
			if(amount[i]>=0&&amount[j]>=0){
				ll x=calc(amount,blank1+blank2-2);
				rep(k,blank1) rep(l,blank2){
					ll y=x*modpow(10,k,MOD)%MOD*modpow(10,l,MOD)%MOD*(i*j)%MOD;
					(res+=y)%=MOD;
				}
			}
			amount[i]++; amount[j]++;
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
			int amount[]              = {0,2,1,1,0,0,0,0,0,0};
			int blank1                = 2;
			int blank2                = 2;
			int expected__            = 4114;
			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int amount[]              = {1,6,0,0,0,0,0,0,0,0};
			int blank1                = 1;
			int blank2                = 2;
			int expected__            = 22;
			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int amount[]              = {1,2,3,4,5,6,7,8,9,10};
			int blank1                = 15;
			int blank2                = 3;
			int expected__            = 340242570;
			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int amount[]              = {3,14,15,92,65,35,89,79,32,38};
			int blank1                = 46;
			int blank2                = 26;
			int expected__            = 417461139;
			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int amount[]              = {100,100,100,100,100,100,100,100,100,100};
			int blank1                = 100;
			int blank2                = 100;
			int expected__            = 372980218;
			std::clock_t start__      = std::clock();
			int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		//case 5: {
		//   int amount[]              = ;
		//   int blank1                = ;
		//   int blank2                = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 6: {
		//   int amount[]              = ;
		//   int blank1                = ;
		//   int blank2                = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   int amount[]              = ;
		//   int blank1                = ;
		//   int blank2                = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = SumProduct().findSum(vector <int>(amount, amount + (sizeof amount / sizeof amount[0])), blank1, blank2);
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
