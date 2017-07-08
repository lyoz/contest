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

struct UnionFind{
	vi data;
	UnionFind(int n):data(n,-1){}
	int Find(int i){
		return data[i]<0?i:(data[i]=Find(data[i]));
	}
	bool Unite(int a,int b){
		a=Find(a),b=Find(b);
		if(a==b) return false;
		if(-data[a]<-data[b]) swap(a,b);
		data[a]+=data[b];
		data[b]=a;
		return true;
	}
	int Size(int i){
		return -data[Find(i)];
	}
};

struct DengklekGaneshAndTree{
	int getCount(string labels, vector <int> parents){
		int n=parents.size()+1;
		vvi g(n);
		UnionFind uf(n);
		rep(i,n-1){
			int u=parents[i],v=i+1;
			g[u].push_back(v);
			if(labels[u]==labels[v])
				uf.Unite(u,v);
		}

		map<int,pair<int,int>> f;
		queue<tuple<int,int>> q;
		q.emplace(0,0);
		while(q.size()){
			int u,d; tie(u,d)=q.front(); q.pop();
			int r=uf.Find(u);
			if(!f.count(r)) f[r]={INF,-INF};
			auto& p=f[r];
			p.first=min(p.first,d);
			p.second=max(p.second,d+1);
			for(int v:g[u])
				q.emplace(v,d+1);
		}

		vector<pair<int,int>> ps;
		for(auto p:f) ps.push_back(p.second);
		sort(all(ps));

		int m=ps.size(),h=0;
		for(auto p:ps) h=max(h,p.second);

		vvi dp(m+1,vi(h+1));
		dp[0][0]=1;
		rep(i,m) repi(j,ps[i].first,h+1){
			(dp[i+1][j]+=dp[i][j])%=MOD;
			(dp[i+1][max(j,ps[i].second)]+=dp[i][j])%=MOD;
		}

		return dp[m][h];
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
			string labels             = "seems";
			int parents[]             = {0, 1, 0, 3};
			int expected__            = 5;
			std::clock_t start__      = std::clock();
			int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string labels             = "like";
			int parents[]             = {0, 0, 0};
			int expected__            = 7;
			std::clock_t start__      = std::clock();
			int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string labels             = "a";
			int parents[]             = {};
			int expected__            = 1;
			std::clock_t start__      = std::clock();
			int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string labels             = "coincidence";
			int parents[]             = {0, 1, 2, 0, 2, 1, 4, 7, 7, 6};
			int expected__            = 218;
			std::clock_t start__      = std::clock();
			int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string labels             = "topcoderopenroundtwobgoodluckhavefun";
			int parents[]             = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
			int expected__            = 147418098;
			std::clock_t start__      = std::clock();
			int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		//case 5: {
		//   string labels             = ;
		//   int parents[]             = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 6: {
		//   string labels             = ;
		//   int parents[]             = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   string labels             = ;
		//   int parents[]             = ;
		//   int expected__            = ;
		//   std::clock_t start__      = std::clock();
		//   int received__            = DengklekGaneshAndTree().getCount(labels, vector <int>(parents, parents + (sizeof parents / sizeof parents[0])));
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
