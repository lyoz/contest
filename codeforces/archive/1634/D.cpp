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

int query(int a,int b,int c)
{
	cout<<"? "<<a+1<<' '<<b+1<<' '<<c+1<<endl;
	int res; cin>>res;
	return res;
}

void answer(int a,int b)
{
	cout<<"! "<<a+1<<' '<<b+1<<endl;
}

int main()
{
	int tc; cin>>tc;
	rep(_,tc){
		int n; cin>>n;

		int mx1=-INF,mi1;
		// n-2回
		repi(i,2,n){
			int t=query(0,1,i);
			if(mx1<t){
				mx1=t;
				mi1=i;
			}
		}
		// n-3回
		int mx2=mx1,mi2=1;
		repi(i,2,n) if(i!=mi1){
			int t=query(0,mi1,i);
			if(mx2<t){
				mx2=t;
				mi2=i;
			}
		}
		// 1回
		int mx3=-INF,mi3;
		repi(i,1,n) if(i!=mi1&&i!=mi2){
			mx3=query(i,mi1,mi2);
			mi3=i;
			break;
		}
		if(mx3<mx2){
			// a[0]==0の可能性がある
			// 2回
			int x=query(0,mi3,mi1);
			int y=query(0,mi3,mi2);
			if(x>y)
				answer(0,mi1);
			else
				answer(0,mi2);
		}
		else{
			answer(mi1,mi2);
		}
	}
}
