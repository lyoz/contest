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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct ConvexHullTrick{
	deque<ll> as,bs;
	// 傾きaは単調非増加でなければならない
	void AddLine(ll a,ll b){
		while(as.size()>=2){
			ll a1=as[as.size()-2],b1=bs[bs.size()-2];
			ll a2=as[as.size()-1],b2=bs[bs.size()-1];
			if((a1-a2)*(b1-b)<(a1-a)*(b1-b2)) break;
			as.pop_back(); bs.pop_back();
		}
		as.push_back(a); bs.push_back(b);
	}
	// 最小のax+bを返す
	ll Find(ll x){
		int lo=0,hi=as.size()-1;
		while(lo<hi){
			int mi=(lo+hi)/2;
			if(F(mi,x)<=F(mi+1,x))
				hi=mi;
			else
				lo=mi+1;
		}
		return F(lo,x);
	}
	// 最小のax+bを返す
	// xが単調非減少ならFindの代わりにこちらを呼ぶ
	ll First(ll x){
		while(as.size()>=2){
			if(F(0,x)<F(1,x))
				break;
			as.pop_front(); bs.pop_front();
		}
		return F(0,x);
	}
	ll F(int i,ll x){
		return as[i]*x+bs[i];
	}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m,p;cin>>n>>m>>p&&n|m|p;){
		vl us(m);
		{
			vl xs(n);
			repi(i,1,n) cin>>xs[i],xs[i]+=xs[i-1];
			rep(i,m){
				ll h,t; cin>>h>>t; h--;
				us[i]=t-xs[h];
			}
			sort(all(us));
		}

		vl sums(m+1);
		rep(i,m) sums[i+1]=sums[i]+us[i];

		vvl dp(p+1,vl(m+1,INF));
		dp[0][0]=0;
		rep(i,p){
			dp[i+1][0]=0;
			ConvexHullTrick cht;
			rep(j,m){
				if(dp[i][j]!=INF)
					cht.AddLine(-j,dp[i][j]+sums[j]);
				//dp[i+1][j+1]=(j+1)*us[j]-sums[j+1]+cht.Find(us[j]);
				dp[i+1][j+1]=(j+1)*us[j]-sums[j+1]+cht.First(us[j]);
			}
		}

		cout<<dp[p][m]<<endl;
	}
}
