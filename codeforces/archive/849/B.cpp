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

struct Point{
	ll x,y;
	Point(){}
	Point(ll x,ll y):x(x),y(y){}
	Point& operator+=(Point p){x+=p.x,y+=p.y; return *this;}
	Point& operator-=(Point p){x-=p.x,y-=p.y; return *this;}
};
Point operator+(Point a,Point b){return a+=b;}
Point operator-(Point a,Point b){return a-=b;}
bool operator==(Point a,Point b){return a.x==b.x&&a.y==b.y;}
bool operator!=(Point a,Point b){return !(a==b);}

ostream& operator<<(ostream& os,const Point& p){
	return os<<'('<<p.x<<','<<p.y<<')';
}
ll Cross(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}

// p[0], ..., p[n-1] on line
bool online(vector<Point> ps)
{
	int n=ps.size();
	rep(i,n-2){
		Point p=ps[i],q=ps[i+1],r=ps[i+2];
		if(Cross(q-p,r-p))
			return false;
	}
	return true;
}

// p[k] on line1
// otherwise on line2
bool online1(vector<Point> ps,int k)
{
	int n=ps.size();
	vector<Point> ps2;
	rep(i,n) if(i!=k) ps2.push_back(ps[i]);
	return online(ps2);
}

// line1: p[0],p[k]を結ぶ直線
// line2: line1上にないpたちを結ぶ直線
bool online2(vector<Point> ps,int k)
{
	int n=ps.size();
	vector<Point> ps1,ps2;
	rep(i,n){
		if(i==0||i==k)
			ps1.push_back(ps[i]);
		else{
			if(Cross(ps[k]-ps[0],ps[i]-ps[0])==0)
				ps1.push_back(ps[i]);
			else
				ps2.push_back(ps[i]);
		}
	}
	if(online(ps2)){
		if(ps2.size()>=2&&Cross(ps1[1]-ps1[0],ps2[1]-ps2[0]))
			return false;
		return true;
	}
	return false;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vector<Point> ps(n);
		rep(i,n){
			ps[i].x=i;
			cin>>ps[i].y;
		}
		bool res=false;
		if(online(ps)){
		}
		else{
			rep(i,n)
				res|=online1(ps,i);
			repi(i,1,n)
				res|=online2(ps,i);
		}
		cout<<(res?"Yes":"No")<<endl;
	}
}
