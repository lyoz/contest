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
		vi a(2*n);
		rep(i,2*n) cin>>a[i];

		{
			vector<tuple<int,int>> ts;
			rep(i,n)
				ts.emplace_back(a[i],a[i+n]);
			const auto [x,y]=*min_element(all(ts));
			if(x>=y){
				cout<<x<<' '<<y<<endl;
				continue;
			}
		}

		vi is;
		rep(i,n){
			while(is.size()&&a[is.back()]>a[i])
				is.pop_back();
			is.push_back(i);
		}

		vi res={is[0]};
		repi(i,1,is.size()){
			if(a[is[i]]==a[is[0]])
				res.push_back(is[i]);
		}

		int x=a[is[0]+n];

		repi(i,res.size(),is.size())
			if(res.back()<=is[i]&&a[is[i]]<x)
				res.push_back(is[i]);

		bool asc=false;
		repi(i,1,res.size())
			if(a[res[i-1]+n]!=a[res[i]+n]){
				asc=a[res[i-1]+n]<a[res[i]+n];
				break;
			}
		if(asc)
			repi(i,res.size(),is.size())
				if(res.back()<=is[i]&&a[is[i]]==x)
					res.push_back(is[i]);

		rep(i,res.size())
			cout<<a[res[i]]<<' ';
		rep(i,res.size())
			cout<<a[res[i]+n]<<"\n "[i+1<res.size()];
	}
}
