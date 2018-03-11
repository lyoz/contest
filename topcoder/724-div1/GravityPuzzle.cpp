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

template<uint M>
struct modint{
	uint val;
	modint(uint x=0):val((x%M+M)%M){}
	modint pow(uint r)const{
		ll a=val,x=1;
		for(;r;r>>=1){
			if(r&1)
				(x*=a)%=M;
			(a*=a)%=M;
		}
		return x;
	}
	modint inv()const{
		ll x=1;
		for(ll a=val,b=M,u=0;b;){
			ll t=a/b;
			swap(a-=b*t,b);
			swap(x-=u*t,u);
		}
		return (x+M)%M;
	}
	modint& operator=(const modint& x)&{val=x.val; return *this;}
	modint& operator+=(const modint& x)&{if((val+=x.val)>=M) val-=M; return *this;}
	modint& operator-=(const modint& x)&{if((val+=M-x.val)>=M) val-=M; return *this;}
	modint& operator*=(const modint& x)&{val=(ll)val*x.val%M; return *this;}
	modint& operator/=(const modint& x)&{val=(ll)val*x.inv().val%M; return *this;}
	explicit operator uint()const{return val;}
};

template<uint M> bool operator==(const modint<M>& a,const modint<M>& b){return a.val==b.val;}
template<uint M> bool operator!=(const modint<M>& a,const modint<M>& b){return a.val!=b.val;}
template<uint M> modint<M> operator+(modint<M> a,const modint<M>& b){a+=b; return a;}
template<uint M> modint<M> operator-(modint<M> a,const modint<M>& b){a-=b; return a;}
template<uint M> modint<M> operator*(modint<M> a,const modint<M>& b){a*=b; return a;}
template<uint M> modint<M> operator/(modint<M> a,const modint<M>& b){a/=b; return a;}
template<uint M> ostream& operator<<(ostream& os,const modint<M>& x){return os<<x.val;}

using mint=modint<MOD>;

mint ncr(int n,int r)
{
	static vector<mint> fact;
	if(fact.empty()){
		fact.resize(51);
		fact[0]=1;
		repi(i,1,fact.size()) fact[i]=mint(i)*fact[i-1];
	}
	return fact[n]/fact[n-r]/fact[r];
}

struct GravityPuzzle{
	int count(vector <string> board){
		int h=board.size(),w=board[0].size();

		bool u=1,d=1,l=1,r=1;  // 傾けても変化しないならtrue
		rep(i,h-1) rep(j,w) u&=board[i][j]=='#'||board[i+1][j]=='.';
		rep(i,h-1) rep(j,w) d&=board[i+1][j]=='#'||board[i][j]=='.';
		rep(i,h) rep(j,w-1) l&=board[i][j]=='#'||board[i][j+1]=='.';
		rep(i,h) rep(j,w-1) r&=board[i][j+1]=='#'||board[i][j]=='.';

		if(!u&&!d&&!l&&!r) return 1;

		vi rcnt(h),ccnt(w);
		rep(i,h) rep(j,w){
			rcnt[i]+=board[i][j]=='#';
			ccnt[j]+=board[i][j]=='#';
		}

		mint res=1;
		if(!u&&!d)
			rep(i,h) res*=ncr(w,rcnt[i]);
		else if(!l&&!r)
			rep(i,w) res*=ncr(h,ccnt[i]);
		else{
			map<int,int> f,g;
			rep(i,h) f[rcnt[i]]++;
			rep(i,w) g[ccnt[i]]++;
			mint a=1,b=1;
			{
				int t=0;
				for(auto p:f)
					a*=ncr(t+=p.second,p.second);
				t=0;
				for(auto p:g)
					b*=ncr(t+=p.second,p.second);
			}
			mint rres=1,cres=1;
			rep(i,h) rres*=ncr(w,rcnt[i]);
			rep(i,w) cres*=ncr(h,ccnt[i]);
			res=rres*a+cres*b-a*b;
		}
		return res.val;
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
			string board[]            = {"#...",
 "....",
 "...."};
			int expected__            = 12;
			std::clock_t start__      = std::clock();
			int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {".#."};
			int expected__            = 1;
			std::clock_t start__      = std::clock();
			int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"#.",
 "##"};
			int expected__            = 4;
			std::clock_t start__      = std::clock();
			int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {".##",
 "..#",
 "..."};
			int expected__            = 72;
			std::clock_t start__      = std::clock();
			int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {".##########.",
 "............",
 "............",
 "............",
 "............",
 "............",
 "............",
 "............",
 "............",
 "............"};
			int expected__            = 999999937;
			std::clock_t start__      = std::clock();
			int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"."};
			int expected__            = 1;
			std::clock_t start__      = std::clock();
			int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		case 6: {
		   string board[]            = {"##........", "###.......", "####......", "######....", "######....", "########..", "########..", "##########", "##########"};
		   int expected__            = 767661144;
		   std::clock_t start__      = std::clock();
		   int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
		   string board[]            = {
				 "####",
				 "##..",
				 "....",
			 };
		   int expected__            = 486;
		   std::clock_t start__      = std::clock();
		   int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
		   return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		//case 8: {
		//   string board[]            = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = GravityPuzzle().count(vector <string>(board, board + (sizeof board / sizeof board[0])));
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