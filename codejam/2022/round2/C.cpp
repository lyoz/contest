#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vvvl=vector<vvl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vvvd=vector<vvd>;
using vs=vector<string>;
using vvs=vector<vs>;

template<typename T,typename U>bool chmin(T& a,const U& b){return a>b?(a=b,1):0;}
template<typename T,typename U>bool chmax(T& a,const U& b){return a<b?(a=b,1):0;}

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

constexpr ll INF=LLONG_MAX;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;
const string POSSIBLE="POSSIBLE";
const string IMPOSSIBLE="IMPOSSIBLE";

ll dist(ll ax,ll ay,ll bx,ll by)
{
	return (ax-bx)*(ax-bx)+(ay-by)*(ay-by);
}

void solve_set1()
{
	int n; cin>>n;
	vi cxs(n),cys(n),sxs(n),sys(n);
	rep(i,n) cin>>cxs[i]>>cys[i];
	int bx,by; cin>>bx>>by;
	rep(i,n) cin>>sxs[i]>>sys[i];

	map<tuple<int,int>,tuple<int,int>> last; 
	last[{0,0}]={-1,-1};
	queue<tuple<int,int>> q; // child,sweet
	q.emplace(0,0);
	while(q.size()){
		auto [curc,curs]=q.front(); q.pop();
		[&]{
			rep(i,n) if(!(curc>>i&1)){
				int cx=cxs[i],cy=cys[i];
				ll bd=dist(cx,cy,bx,by);
				ll nearest=INF;
				rep(j,n) if(!(curs>>j&1))
					chmin(nearest,dist(cx,cy,sxs[j],sys[j]));
				if(nearest>bd)
					return;
				rep(j,n) if(!(curs>>j&1)){
					ll d=dist(cx,cy,sxs[j],sys[j]);
					if(d==nearest){
						if(!last.count({curc|1<<i,curs|1<<j})){
							last[{curc|1<<i,curs|1<<j}]={i,j};
							q.emplace(curc|1<<i,curs|1<<j);
						}
					}
				}
			}
		}();
	}
	if(!last.count({(1<<n)-1,(1<<n)-1})){
		cout<<IMPOSSIBLE<<endl;
		return;
	}
	cout<<POSSIBLE<<endl;
	deque<tuple<int,int>> res;
	ll cnt=0;
	for(int c=(1<<n)-1,s=(1<<n)-1;c;){
		auto [ci,si]=last[{c,s}];
		res.emplace_front(ci,si);
		c^=1<<ci; s^=1<<si;
		cnt++;
		if(cnt==10) break;
	}
	for(auto [ci,si]:res)
		cout<<ci+1<<' '<<si+2<<endl;
}

void solve()
{
	solve_set1();
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(_,tc){
		cout<<"Case #"<<_+1<<": ";
		solve();
	}
}
