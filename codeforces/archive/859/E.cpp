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

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

ll dfs(const vi& cur,const vi& wish,const vvi& toleft,int u,vi& vis)
{
	vis[u]=1;
	ll res=1;
	for(int v:toleft[u])
		res+=dfs(cur,wish,toleft,cur[v],vis);
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi cur(n),wish(n);
		rep(i,n){
			cin>>cur[i]>>wish[i];
			cur[i]--,wish[i]--;
		}

		vi used(2*n);
		rep(i,n) used[cur[i]]=1;

		vvi toleft(2*n);
		rep(i,n)
			toleft[wish[i]].push_back(i);

		vi vis(2*n);
		ll res=1;
		rep(i,2*n) if(!used[i]){
			ll x=dfs(cur,wish,toleft,i,vis);
			(res*=x)%=MOD;
		}

		vi toleft2(2*n,-1);
		rep(i,n)
			toleft2[cur[i]]=i;

		int cycle=0;
		rep(i,2*n) if(!vis[i]){
			assert(toleft2[i]!=-1);
			vi path;
			for(int u=i;;u=wish[toleft2[u]]){
				if(vis[u]){
					if(count(all(path),u)&&path.back()!=u)
						cycle++;
					break;
				}
				vis[u]=1;
				path.push_back(u);
			}
		}

		(res*=ModPow(2,cycle,MOD))%=MOD;
		cout<<res<<endl;
	}
}
