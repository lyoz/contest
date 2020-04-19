#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cerr<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cerr<<endl;}while(0)
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

constexpr int XMIN=-1e9,XMAX=1e9;
constexpr int YMIN=-1e9,YMAX=1e9;

const string CENTER="CENTER";
const string HIT="HIT";
const string MISS="MISS";
const string WRONG="WRONG";

string query(int x,int y)
{
	cout<<x<<' '<<y<<endl;
	string res; cin>>res;
	return res;
}

void solve_set1()
{
	for(int y=-5;y<=5;y++){
		for(int x=-5;x<=5;x++){
			string res=query(x,y);
			if(res==CENTER)
				return;
		}
	}
}

void solve(int,int)
{
	//solve_set1();
	int xhit=-1,yhit=-1;
	{
		vi xs={0,-500000000,500000000,-500000000,500000000};
		vi ys={0,-500000000,-500000000,500000000,500000000};
		rep(i,5){
			string res=query(xs[i],ys[i]);
			if(res==CENTER)
				return;
			if(res==HIT){
				xhit=xs[i],yhit=ys[i];
				break;
			}
		}
	}

	int xans;
	{
		int lo=XMIN,hi=xhit;
		while(lo<hi){
			int mi=lo+(hi-lo)/2;
			string res=query(mi,yhit);
			if(res==CENTER)
				return;
			else if(res==HIT)
				hi=mi;
			else
				lo=mi+1;
		}
		int l=lo;
		lo=xhit,hi=XMAX+1;
		while(lo<hi){
			int mi=lo+(hi-lo)/2;
			string res=query(mi,yhit);
			if(res==CENTER)
				return;
			else if(res==MISS)
				hi=mi;
			else
				lo=mi+1;
		}
		int r=lo-1;
		xans=(l+r)/2;
	}
	int yans;
	{
		int lo=YMIN,hi=yhit;
		while(lo<hi){
			int mi=lo+(hi-lo)/2;
			string res=query(xans,mi);
			if(res==CENTER)
				return;
			else if(res==HIT)
				hi=mi;
			else
				lo=mi+1;
		}
		int b=lo;
		lo=yhit,hi=YMAX+1;
		while(lo<hi){
			int mi=lo+(hi-lo)/2;
			string res=query(xans,mi);
			if(res==CENTER)
				return;
			else if(res==MISS)
				hi=mi;
			else
				lo=mi+1;
		}
		int t=hi-1;
		yans=(b+t)/2;
	}
	
	assert(query(xans,yans)==CENTER);
}

int main()
{
	int tc; cin>>tc;
	int rmin,rmax; cin>>rmin>>rmax;
	rep(i,tc)
		solve(rmin,rmax);
}
