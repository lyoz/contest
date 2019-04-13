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
	#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	#endif

	for(int n;cin>>n&&n;){
		vvi g(n);
		rep(_,n-1){
			int u,v; cin>>u>>v; u--,v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		vi leaf(n);
		repi(i,1,n) leaf[i]=g[i].size()==1;

		vi ds(n);
		vd ps(n);
		queue<tuple<int,int,int,double>> q;
		q.emplace(-1,0,0,1);
		while(q.size()){
			int p,u,d; double x; tie(p,u,d,x)=q.front(); q.pop();
			int m=0;
			ds[u]=d,ps[u]=x;
			for(int v:g[u]) if(v!=p) m++;
			for(int v:g[u]) if(v!=p) q.emplace(u,v,d+1,x/m);
		}

		double res=0;
		rep(i,n) if(leaf[i])
			res+=ds[i]*ps[i];
		printf("%.9f\n",res);
	}
}
