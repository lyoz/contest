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

int query(int x1,int y1,int x2,int y2)
{
	cout<<"? "<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
	int res; cin>>res;
	return res;
}

void answer(int x1,int y1,int x2,int y2)
{
	cout<<"! "<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
}

int main()
{
	int n; cin>>n;
	vi xcands,ycands;
	for(int x=1;x<=n;x++){
		int res=query(x,1,x,n);
		if(res&1)
			xcands.push_back(x);
		if(xcands.size()==1&&x==n-1)
			xcands.push_back(n);
		if(xcands.size()==2)
			break;
	}
	for(int y=1;y<=n;y++){
		int res=query(1,y,n,y);
		if(res&1)
			ycands.push_back(y);
		if(ycands.size()==1&&y==n-1)
			ycands.push_back(n);
		if(ycands.size()==2)
			break;
	}

	if(xcands.size()){
		ycands.clear();
		for(int x:xcands){
			int lo=1,hi=n;
			while(lo<hi){
				int mi=(lo+hi)/2;
				int res=query(x,lo,x,mi);
				if(res&1)
					hi=mi;
				else
					lo=mi+1;
			}
			ycands.push_back(lo);
		}
	}
	else if(ycands.size()){
		xcands.clear();
		for(int y:ycands){
			int lo=1,hi=n;
			while(lo<hi){
				int mi=(lo+hi)/2;
				int res=query(lo,y,mi,y);
				if(res&1)
					hi=mi;
				else
					lo=mi+1;
			}
			xcands.push_back(lo);
		}
	}
	else{
		assert(0);
	}
	answer(xcands[0],ycands[0],xcands[1],ycands[1]);
}
