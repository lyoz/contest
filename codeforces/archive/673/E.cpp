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
	for(int n,m;cin>>n>>m&&n|m;){
		vi ts(n);
		rep(i,n) cin>>ts[i];
		
		vd sum(n+1),rev(n+1),pre(n+1);
		rep(i,n){
			sum[i+1]=sum[i]+ts[i];
			rev[i+1]=rev[i]+1./ts[i];
			pre[i+1]=pre[i]+sum[i+1]/ts[i];
		}
		
		vvd dp(m+1,vd(n+1,INFINITY));
		dp[0][0]=0;
		
		rep(i,m){
			deque<int> ks={i};
			repi(j,i+1,n+1){
				while(ks.size()>=2){
					int k1=ks[ks.size()-2],k2=ks[ks.size()-1],k3=j;
					double a1=-sum[k1],b1=dp[i][k1]-pre[k1]+sum[k1]*rev[k1];
					double a2=-sum[k2],b2=dp[i][k2]-pre[k2]+sum[k2]*rev[k2];
					double a3=-sum[k3],b3=dp[i][k3]-pre[k3]+sum[k3]*rev[k3];
					if((a1-a2)*(b1-b3)>(b1-b2)*(a1-a3)) ks.pop_back();
					else break;
				}
				ks.push_back(j);
				
				auto f=[&](int k){
					return -sum[k]*rev[j]+dp[i][k]-pre[k]+sum[k]*rev[k];
				};
				
				for(;ks.size()>=2 && f(ks[0])>f(ks[1]);)
					ks.pop_front();
				dp[i+1][j]=pre[j]+f(ks[0]);
			}
		}
		printf("%.9f\n",dp[m][n]);
	}
}
