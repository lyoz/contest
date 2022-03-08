#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

void solve(int n,int m,vi a,vi es,vi ts,vi ps)
{
	vvi trains(n);
	rep(i,m)
		trains[es[i]].push_back(i);

	vvl dp(n,vl(200,INF));
	rep(i,n)
		dp[i][0]=0;

	ll elapsed=0;
	vi order;
	rep(i,n){
		vvl last(trains[i].size()+1,vl(200,-1));
		rep(j,trains[i].size()){
			last[j+1]=last[j];
			int ti=trains[i][j];
			int t=ts[ti],p=ps[ti];
			per(k,100){
				if(dp[i][k]==INF)
					continue;
				if(dp[i][k+p]>dp[i][k]+t){
					dp[i][k+p]=dp[i][k]+t;
					last[j+1][k+p]=j;
				}
			}
		}
		int mi=min_element(100+all(dp[i]))-begin(dp[i]);
		elapsed+=dp[i][mi];
		if(elapsed>a[i]){
			cout<<-1<<endl;
			return;
		}
		vi o;
		for(int j=trains[i].size(),p=mi;p;){
			int li=last[j][p];
			int ti=trains[i][li];
			o.push_back(ti);
			j=li;
			p-=ps[ti];
		}
		order.insert(end(order),rbegin(o),rend(o));
	}
	cout<<order.size()<<endl;
	rep(i,order.size())
		cout<<order[i]+1<<"\n "[i+1<order.size()];
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
		int n,m; cin>>n>>m;
		vi a(n),es(m),ts(m),ps(m);
		rep(i,n) cin>>a[i];
		rep(i,m) cin>>es[i]>>ts[i]>>ps[i],es[i]--;

		solve(n,m,a,es,ts,ps);
	}
}
