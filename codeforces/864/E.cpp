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

template<typename T,typename Compare>
auto make_priority_queue(const Compare& comp)
{
	return priority_queue<T,vector<T>,Compare>(comp);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi ts(n),ds(n),ps(n),is(n);
		rep(i,n) cin>>ts[i]>>ds[i]>>ps[i],is[i]=i;
		{
			vector<tuple<int,int,int,int>> a;
			rep(i,n) a.emplace_back(ts[i],ds[i],ps[i],is[i]);
			sort(all(a),[](auto x,auto y){return get<1>(x)<get<1>(y);});
			rep(i,n) tie(ts[i],ds[i],ps[i],is[i])=a[i];
		}

		int m=*max_element(all(ds));
		vvi dp(n+1,vi(m)),prev(n+1,vi(m,-1));
		rep(i,n){
			dp[i+1]=dp[i],prev[i+1]=prev[i];
			for(int j=0;j+ts[i]<ds[i];j++){
				if(dp[i+1][j+ts[i]]<dp[i][j]+ps[i]){
					dp[i+1][j+ts[i]]=dp[i][j]+ps[i];
					prev[i+1][j+ts[i]]=i;
				}
			}
		}

		vi path;
		for(int t=max_element(all(dp[n]))-begin(dp[n]),v=prev[n][t];v!=-1;){
			path.push_back(v);
			tie(t,v)=mt(t-ts[v],prev[v][t-ts[v]]);
		}
		reverse(all(path));

		cout<<*max_element(all(dp[n]))<<endl;
		cout<<path.size()<<endl;
		rep(i,path.size()) cout<<is[path[i]]+1<<"\n "[i+1<path.size()];
	}
}
