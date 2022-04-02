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

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	constexpr int di[]={-1,1,-1,1};
	constexpr int dj[]={-1,1,1,-1};

	for(int n;cin>>n&&n;){
		int ai,aj,bi,bj; cin>>ai>>aj>>bi>>bj; ai--,aj--,bi--,bj--;
		vs grid(n);
		rep(i,n) cin>>grid[i];

		vvi vis1(n,vi(n,INF));
		vvi vis2(n,vi(n,INF));
		queue<tuple<int,int>> q;
		vis1[ai][aj]=vis2[ai][aj]=0;
		q.emplace(ai,aj);
		while(q.size()){
			auto [ci,cj]=q.front(); q.pop();
			int cc=min(vis1[ci][cj],vis2[ci][cj]);
			rep(k,2){
				repi(i,1,n){
					int ni=ci+i*di[k],nj=cj+i*dj[k];
					if(ni<0||n<=ni||nj<0||n<=nj||grid[ni][nj]=='#')
						break;
					if(vis1[ni][nj]!=INF)
						break;
					vis1[ni][nj]=cc+1;
					q.emplace(ni,nj);
				}
			}
			repi(k,2,4){
				repi(i,1,n){
					int ni=ci+i*di[k],nj=cj+i*dj[k];
					if(ni<0||n<=ni||nj<0||n<=nj||grid[ni][nj]=='#')
						break;
					if(vis2[ni][nj]!=INF)
						break;
					vis2[ni][nj]=cc+1;
					q.emplace(ni,nj);
				}
			}
		}
		int res=min(vis1[bi][bj],vis2[bi][bj]);
		cout<<(res!=INF?res:-1)<<endl;
	}
}
