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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vector<deque<int>> ts(n);
		rep(i,n){
			int k; cin>>k; ts[i].resize(k);
			rep(j,k) cin>>ts[i][j];
		}
		int m; cin>>m;
		vi a(m);
		rep(i,m) cin>>a[i];

		set<tuple<int,int>> set1; // 最前列
		set<tuple<int,int>> set2; // 2番目まで
		rep(i,n){
			set1.emplace(ts[i][0],i);
			set2.emplace(ts[i][0],i);
			if(ts[i].size()>=2)
				set2.emplace(ts[i][1],i);
		}

		vi res(m);
		rep(i,m){
			if(a[i]==1){
				int x,j; tie(x,j)=*--set1.end();
				res[i]=x;
				set1.erase(mt(x,j));
				set2.erase(mt(x,j));
				ts[j].pop_front();
				if(ts[j].size()>=1)
					set1.emplace(ts[j][0],j);
				if(ts[j].size()>=2)
					set2.emplace(ts[j][1],j);
			}
			if(a[i]==2){
				int x,j; tie(x,j)=*--set2.end();
				res[i]=x;
				if(ts[j][0]==x){ // 最前列の商品をとった
					set1.erase(mt(x,j));
					set2.erase(mt(x,j));
					ts[j].pop_front();
					if(ts[j].size()>=1)
						set1.emplace(ts[j][0],j);
					if(ts[j].size()>=2)
						set2.emplace(ts[j][1],j);
				}
				else{ // 手前から2番目の商品をとった
					set2.erase(mt(x,j));
					assert(x==ts[j][1]);
					{
						int t=ts[j].front();
						ts[j].pop_front();
						ts[j].pop_front();
						ts[j].push_front(t);
					}
					if(ts[j].size()>=2)
						set2.emplace(ts[j][1],j);
				}
			}
		}

		rep(i,m) cout<<res[i]<<endl;
	}
}
