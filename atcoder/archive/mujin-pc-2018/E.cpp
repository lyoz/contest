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

	for(int h,w,n;cin>>h>>w>>n&&h|w|n;){
		vvi ds(4);
		{
			string s; cin>>s;
			rep(i,n){
				if(s[i]=='U') ds[0].push_back(i);
				if(s[i]=='D') ds[1].push_back(i);
				if(s[i]=='L') ds[2].push_back(i);
				if(s[i]=='R') ds[3].push_back(i);
			}
		}
		vs grid(h);
		rep(i,h) cin>>grid[i];

		tuple<int,int> src,dst;
		rep(i,h) rep(j,w){
			if(grid[i][j]=='S'){
				src=mt(i,j);
				grid[i][j]='.';
			}
			if(grid[i][j]=='G'){
				dst=mt(i,j);
				grid[i][j]='.';
			}
		}

		vi di={-1,1,0,0},dj={0,0,-1,1};

		auto pq=make_priority_queue<tuple<int,int,ll>>([](auto a,auto b){
			return get<2>(a)>get<2>(b);
		});
		pq.emplace(get<0>(src),get<1>(src),0);

		vvl dp(h,vl(w,INF));
		while(pq.size()){
			int ci,cj; ll ct; tie(ci,cj,ct)=pq.top(); pq.pop();
			if(dp[ci][cj]<ct)
				continue;
			dp[ci][cj]=ct;
			rep(k,4) if(ds[k].size()){
				int ni=ci+di[k],nj=cj+dj[k];
				if(ni<0||h<=ni||nj<0||w<=nj||grid[ni][nj]=='#')
					continue;
				ll nt=ct/n*n;
				auto it=lower_bound(all(ds[k]),ct%n);
				if(it!=end(ds[k]))
					nt+=*it;
				else
					nt+=n+ds[k][0];
				nt++;
				pq.emplace(ni,nj,nt);
			}
		}

		ll res=dp[get<0>(dst)][get<1>(dst)];
		cout<<(res==INF?-1:res)<<endl;
	}
}
