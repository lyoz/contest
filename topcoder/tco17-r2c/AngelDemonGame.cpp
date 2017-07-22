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

struct Edge{
	int src,dst,cost,cap,flow;
	Edge(){}
	Edge(int s,int d,int co,int ca=0,int f=0):src(s),dst(d),cost(co),cap(ca),flow(f){}
};
struct Graph{
	vector<Edge> es;
	vi head,next;
	Graph(){}
	Graph(int n):head(n,-1){}
	// コスト:-co,容量:0の逆辺も追加する
	void AddEdge(int u,int v,int co,int ca){
		es.emplace_back(u,v,co,ca); next.push_back(head[u]); head[u]=es.size()-1;
		es.emplace_back(v,u,-co,0); next.push_back(head[v]); head[v]=es.size()-1;
	}
};

int MinCostFlow(Graph& g,int tap,int sink,int flow)
{
	int n=g.head.size();
	
	int res=0;
	vi pots(n);
	while(flow){
		vi cost(n,INF),prev(n,-1);
		priority_queue<pii,vector<pii>,greater<pii>> pq;
		cost[tap]=0;
		pq.emplace(0,tap);
		while(pq.size()){
			int c,v; tie(c,v)=pq.top(); pq.pop();
			if(c>cost[v]) continue;
			for(int i=g.head[v];i!=-1;i=g.next[i]){
				Edge e=g.es[i];
				if(e.cap-e.flow==0) continue;
				if(cost[e.dst]>cost[e.src]+e.cost+pots[e.src]-pots[e.dst]){
					cost[e.dst]=cost[e.src]+e.cost+pots[e.src]-pots[e.dst];
					prev[e.dst]=i;
					pq.emplace(cost[e.dst],e.dst);
				}
			}
		}
		
		if(cost[sink]==INF) return -1;
		rep(i,n) pots[i]+=cost[i];
		
		int augment=flow;
		for(int v=sink;v!=tap;v=g.es[prev[v]].src){
			Edge e=g.es[prev[v]];
			augment=min(augment,e.cap-e.flow);
		}
		for(int v=sink;v!=tap;v=g.es[prev[v]].src){
			int i=prev[v];
			g.es[i].flow+=augment;
			g.es[i^1].flow-=augment;
		}
		flow-=augment;
		res+=augment*pots[sink];
	}
	
	return res;
}

struct AngelDemonGame{
	string winner(vector <string> G, int A, int D){
		int n=G.size();
		if(D>=n-1)
			return "Demon";

		Graph g(n);
		rep(i,n) rep(j,n)
			g.AddEdge(i,j,G[i][j]=='N',1);
		int cost=MinCostFlow(g,0,n-1,D+1);

		if(cost!=-1&&cost<=A)
			return "Angel";

		return "Unknown";
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
			string G[]                = {"NYNY",
 "YNYY",
 "NYNN",
 "YYNN"};
			int A                     = 2;
			int D                     = 2;
			string expected__         = "Angel";
			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string G[]                = {"NYNY",
 "YNYY",
 "NYNN",
 "YYNN"};
			int A                     = 6;
			int D                     = 6;
			string expected__         = "Demon";
			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string G[]                = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"};
			int A                     = 2;
			int D                     = 2;
			string expected__         = "Unknown";
			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string G[]                = {"NYNNNY",
 "YNNYNN",
 "NNNNYN",
 "NYNNNN",
 "NNYNNN",
 "YNNNNN"};
			int A                     = 4;
			int D                     = 4;
			string expected__         = "Unknown";
			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string G[]                = {"NYNNNY",
 "YNNYNN",
 "NNNNYN",
 "NYNNNN",
 "NNYNNN",
 "YNNNNN"};
			int A                     = 8;
			int D                     = 4;
			string expected__         = "Angel";
			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string G[]                = {"NYNNNY",
 "YNNYNN",
 "NNNNYN",
 "NYNNNN",
 "NNYNNN",
 "YNNNNN"};
			int A                     = 4;
			int D                     = 8;
			string expected__         = "Demon";
			std::clock_t start__      = std::clock();
			string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

		//case 6: {
		//   string G[]                = ;
		//   int A                     = ;
		//   int D                     = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 7: {
		//   string G[]                = ;
		//   int A                     = ;
		//   int D                     = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
		//   return verify_case(casenum__, expected__, received__, clock()-start__);
		//}
		//case 8: {
		//   string G[]                = ;
		//   int A                     = ;
		//   int D                     = ;
		//   string expected__         = ;
		//   std::clock_t start__      = std::clock();
		//   string received__         = AngelDemonGame().winner(vector <string>(G, G + (sizeof G / sizeof G[0])), A, D);
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
