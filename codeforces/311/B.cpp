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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int main()
{
	for(int n,m,p;cin>>n>>m>>p&&n|m|p;){
		vl us(m);
		{
			vi xs(n);
			repi(i,1,n) cin>>xs[i],xs[i]+=xs[i-1];
			rep(i,m){
				int h,t; cin>>h>>t; h--;
				us[i]=t-xs[h];
			}
			sort(all(us));
		}
		vl sums(m+1);
		rep(i,m) sums[i+1]=sums[i]+us[i];
		
		vvl dp(p+1,vl(m+1,INF)); dp[0][0]=0;
		rep(i,p){
			dp[i+1][0]=0;
			deque<int> ks;
			rep(j,m){
				while(ks.size()>=2){
					int k1=ks[ks.size()-2],k2=ks[ks.size()-1],k3=j;
					ll a1=-k1,b1=dp[i][k1]+sums[k1];
					ll a2=-k2,b2=dp[i][k2]+sums[k2];
					ll a3=-k3,b3=dp[i][k3]+sums[k3];
					if((a1-a2)*(b1-b3)<(a1-a3)*(b1-b2)) break;
					ks.pop_back();
				}
				ks.push_back(j);
				auto f=[&](int j,int k){return -us[j]*k+dp[i][k]+sums[k];};
				while(ks.size()>=2){
					if(f(j,ks[0])<=f(j,ks[1])) break;
					ks.pop_front();
				}
				dp[i+1][j+1]=us[j]*(j+1)-sums[j+1]+f(j,ks[0]);
			}
		}
		cout<<dp[p][m]<<endl;
	}
}
