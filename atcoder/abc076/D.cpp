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

template<typename T,typename U>
bool chmax(T& a,const U& b){if(a<b) return a=b,true; else return false;}

double f(double a,double b,double h)
{
	return (a+b)/2*h;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi ts(n),vs(n);
		rep(i,n) cin>>ts[i];
		rep(i,n) cin>>vs[i];
		vvd dp(n+1,vd(201,-1));
		dp[0][0]=0;
		rep(i,n){
			// 0.5秒ずつ進める(奇数秒区間の中間で減速することがあるため．入力例4)
			for(double t=0;t<ts[i];t+=0.5){
				vd tmp(201,-1);
				for(double v=0;v<=vs[i];v+=0.5){
					if(dp[i][2*v]==-1) continue;
					if(0<v) chmax(tmp[2*v-1],dp[i][2*v]+f(v,v+0.5,0.5));
					chmax(tmp[2*v],dp[i][2*v]+f(v,v,0.5));
					if(v<vs[i]) chmax(tmp[2*v+1],dp[i][2*v]+f(v,v-0.5,0.5));
				}
				dp[i]=tmp;
			}
			dp[i+1]=dp[i];
		}
		printf("%f\n",dp[n][0]);
	}
}
