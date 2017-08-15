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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct Edge{
	int src,dst;
	ll weight;
	Edge(){}
	Edge(int s,int d,ll w):src(s),dst(d),weight(w){}
};
typedef vector<vector<Edge>> Graph;
bool operator<(const Edge& a,const Edge& b){return a.weight<b.weight;}
bool operator>(const Edge& a,const Edge& b){return a.weight>b.weight;}

void Dijkstra(const Graph& g,int v,vl& dist)
{
	priority_queue<Edge,vector<Edge>,greater<Edge>> pq;
	pq.emplace(-1,v,0);
	while(pq.size()){
		Edge cur=pq.top(); pq.pop();
		if(dist[cur.dst]!=INF) continue;
		dist[cur.dst]=cur.weight;
		for(Edge e:g[cur.dst])
			pq.emplace(e.src,e.dst,cur.weight+e.weight);
	}
}

struct LongMansionDiv1{
	long long minimalTime(vector <int> t, int sX, int sY, int eX, int eY){
		int n=t.size();
		Graph g(2*n);
		rep(i,n-1){
			g[i].emplace_back(i,i+1,t[i+1]);
			g[i+1].emplace_back(i+1,i,t[i]);
			g[n+i].emplace_back(n+i,n+i+1,t[i+1]);
			g[n+i+1].emplace_back(n+i+1,n+i,t[i]);
		}
		rep(i,n){
			g[i].emplace_back(i,n+i,(ll)t[i]*abs(sY-eY));
			g[n+i].emplace_back(n+i,i,(ll)t[i]*abs(sY-eY));
		}
		vl dist(2*n,INF);
		Dijkstra(g,sX,dist);
		return t[sX]+dist[n+eX];
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
			int t[]                   = {5, 3, 10};
			int sX                    = 2;
			int sY                    = 0;
			int eX                    = 2;
			int eY                    = 2;
			long long expected__      = 29;
			std::clock_t start__      = std::clock();
			long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int t[]                   = {5, 3, 10};
			int sX                    = 0;
			int sY                    = 2;
			int eX                    = 0;
			int eY                    = 0;
			long long expected__      = 15;
			std::clock_t start__      = std::clock();
			long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int t[]                   = {137, 200, 184, 243, 252, 113, 162};
			int sX                    = 0;
			int sY                    = 2;
			int eX                    = 4;
			int eY                    = 2;
			long long expected__      = 1016;
			std::clock_t start__      = std::clock();
			long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int t[]                   = {995, 996, 1000, 997, 999, 1000, 997, 996, 1000, 996, 1000, 997, 999, 996, 1000, 998, 999, 995, 995, 998, 995, 998, 995, 997, 998, 996, 998, 996, 997, 1000, 998, 997, 995, 1000, 996, 997, 1000, 997, 997, 999, 998, 995, 999, 999, 1000, 1000, 998, 997, 995, 999};
			int sX                    = 18;
			int sY                    = 433156521;
			int eX                    = 28;
			int eY                    = 138238863;
			long long expected__      = 293443080673LL;
			std::clock_t start__      = std::clock();
			long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int t[]                   = {1};
			int sX                    = 0;
			int sY                    = 0;
			int eX                    = 0;
			int eY                    = 0;
			long long expected__      = 1;
			std::clock_t start__      = std::clock();
			long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		//case 5: {
		//   int t[]                   = ;
		//   int sX                    = ;
		//   int sY                    = ;
		//   int eX                    = ;
		//   int eY                    = ;
		//   long long expected__      = ;
		//   std::clock_t start__      = std::clock();
		//   long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 6: {
		//   int t[]                   = ;
		//   int sX                    = ;
		//   int sY                    = ;
		//   int eX                    = ;
		//   int eY                    = ;
		//   long long expected__      = ;
		//   std::clock_t start__      = std::clock();
		//   long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   int t[]                   = ;
		//   int sX                    = ;
		//   int sY                    = ;
		//   int eX                    = ;
		//   int eY                    = ;
		//   long long expected__      = ;
		//   std::clock_t start__      = std::clock();
		//   long long received__      = LongMansionDiv1().minimalTime(vector <int>(t, t + (sizeof t / sizeof t[0])), sX, sY, eX, eY);
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
