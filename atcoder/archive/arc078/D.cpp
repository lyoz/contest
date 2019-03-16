#include <bits/stdc++.h>
using namespace std;

#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl
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

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int main()
{
	for(int n;cin>>n&&n;){
		vvi g(n);
		rep(i,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}

		// between 0 and n-1
		vi path;
		{
			vi prev(n,-1);
			queue<int> q;
			q.push(0);
			while(q.size()){
				int u=q.front(); q.pop();
				for(int v:g[u]){
					if(prev[v]==-1){
						prev[v]=u;
						q.push(v);
					}
				}
			}
			for(int v=n-1;;v=prev[v]){
				path.push_back(v);
				if(v==0) break;
			}
			reverse(all(path));
		}

		queue<int> bq,wq;
		rep(i,path.size()){
			bq.push(path[i]);
			wq.push(path[path.size()-1-i]);
		}

		vi vis(n,-1);
		string res;
		for(int player=0;;player^=1){  // 0: Fennec, 1: Snuke
			bool played=false;

			queue<int>& q=player==0?bq:wq;
			while(!played&&q.size()){
				int u=q.front(); q.pop();
				if(vis[u]!=-1) continue;
				vis[u]=player;
				for(int v:g[u])
					q.push(v);
				played=true;
			}

			if(!played){
				res=player==0?"Snuke":"Fennec";
				break;
			}
		}
		cout<<res<<endl;
	}
}
