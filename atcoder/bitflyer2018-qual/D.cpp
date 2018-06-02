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

	for(int h,w,sh,sw;cin>>h>>w>>sh>>sw&&h|w|sh|sw;){
		vs grid(sh);
		rep(i,sh) cin>>grid[i];

		vi is={0,h},js={0,w};
		rep(i,sh){
			rep(j,sw){
				if(grid[i][j]=='#'){
					is.push_back(i);
					is.push_back(i+h-sh+1);
					js.push_back(j);
					js.push_back(j+w-sw+1);
				}
			}
		}
		sort(all(is)); is.erase(unique(all(is)),end(is));
		sort(all(js)); js.erase(unique(all(js)),end(js));

		vvi sum(is.size(),vi(js.size()));
		rep(i,sh){
			rep(j,sw){
				if(grid[i][j]=='#'){
					int t=lower_bound(all(is),i)-begin(is);
					int b=lower_bound(all(is),i+h-sh+1)-begin(is);
					int l=lower_bound(all(js),j)-begin(js);
					int r=lower_bound(all(js),j+w-sw+1)-begin(js);
					sum[t][l]++; sum[t][r]--; sum[b][l]--; sum[b][r]++;
				}
			}
		}
		rep(i,is.size())
			rep(j,js.size()-1)
				sum[i][j+1]+=sum[i][j];
		rep(i,is.size()-1)
			rep(j,js.size())
				sum[i+1][j]+=sum[i][j];

		ll res=0;
		rep(i,is.size())
			rep(j,js.size())
				if(sum[i][j])
					res+=(ll)(is[i+1]-is[i])*(js[j+1]-js[j]);
		cout<<res<<endl;
	}
}
