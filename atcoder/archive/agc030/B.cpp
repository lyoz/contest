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

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

ll solve(int l,const vi& xs,int k,int i,int j,vector<vvl>& memo)
{
	if(memo[k][i][j]!=-1)
		return memo[k][i][j];
	if(i==0&&j==xs.size()-1)
		return memo[k][i][j]=0;
	ll& res=memo[k][i][j];
	if(k==0&&i>=1){
		chmax(res,solve(l,xs,0,i-1,j,memo)+(xs[i]-xs[i-1]));
		chmax(res,solve(l,xs,1,i-1,j,memo)+(l-xs[j])+xs[i]);
	}
	if(k==1&&j<=xs.size()-2){
		chmax(res,solve(l,xs,0,i,j+1,memo)+xs[i]+(l-xs[j]));
		chmax(res,solve(l,xs,1,i,j+1,memo)+(xs[j+1]-xs[j]));
	}
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int l,n;cin>>l>>n&&l|n;){
		vi xs(n);
		rep(i,n) cin>>xs[i];
		xs.insert(begin(xs),0);
		xs.push_back(l);
		n+=2;

		if(n>2002){
			cout<<"X"<<endl;
			continue;
		}

		vector<vvl> memo(2,vvl(n,vl(n,-1)));
		ll res=0;
		rep(i,n-1){
			chmax(res,solve(l,xs,0,i,i+1,memo));
			chmax(res,solve(l,xs,1,i,i+1,memo));
		}
		cout<<res<<endl;
	}
}
