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
constexpr double PI=acos(-1);

int Signum(double x){
	return x<-EPS?-1:x>EPS?1:0;
}

struct Point{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	Point& operator+=(Point p){x+=p.x,y+=p.y; return *this;}
	Point& operator-=(Point p){x-=p.x,y-=p.y; return *this;}
	Point& operator*=(double c){x*=c,y*=c; return *this;}
	Point& operator/=(double c){x/=c,y/=c; return *this;}
};
Point operator+(Point a,Point b){return a+=b;}
Point operator-(Point a,Point b){return a-=b;}
Point operator*(Point a,double c){return a*=c;}
Point operator*(double c,Point a){return a*=c;}
Point operator/(Point a,double c){return a/=c;}
bool operator==(Point a,Point b){return abs(a.x-b.x)<EPS && abs(a.y-b.y)<EPS;}
bool operator!=(Point a,Point b){return !(a==b);}
ostream& operator<<(ostream& os,const Point& p){return os<<'('<<p.x<<','<<p.y<<')';}

struct LessX{
	bool operator()(Point a,Point b){
		return abs(a.x-b.x)>EPS?a.x<b.x-EPS:a.y<b.y-EPS;
	}
};

double Abs(Point p){
	return sqrt(p.x*p.x+p.y*p.y);
}
double Abs2(Point p){
	return p.x*p.x+p.y*p.y;
}
double Arg(Point p){
	return atan2(p.y,p.x);
}
double Dot(Point a,Point b){
	return a.x*b.x+a.y*b.y;
}
double Cross(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}
Point Rot(Point p,double t){
	return Point(cos(t)*p.x-sin(t)*p.y,sin(t)*p.x+cos(t)*p.y);
}

struct Line{
	Point pos,dir;
	Line(){}
	Line(Point p,Point d):pos(p),dir(d){}
	Line(double x,double y,double u,double v):pos(x,y),dir(u,v){}
};

int CCW(Point a,Point b,Point c){
	b-=a,c-=a;
	if(int sign=Signum(Cross(b,c)))
		return sign; // 1:ccw,-1:cw
	if(Dot(b,c)<-EPS)
		return -2;   // c-a-b
	if(Abs2(b)<Abs2(c)-EPS)
		return 2;    // a-b-c
	return 0;        // a-c-b (inclusive)
}

vector<Point> ConvexHull(vector<Point> ps){
	if(ps.size()==1) return ps;
	sort(all(ps),LessX());
	vector<Point> res;
	rep(_,2){
		int n=0;
		vector<Point> half(ps.size());
		rep(i,ps.size()){
			while(n>=2 && CCW(half[n-2],half[n-1],ps[i])!=1)
				n--;
			half[n++]=ps[i];
		}
		res.insert(res.end(),half.begin(),half.begin()+n-1);
		reverse(all(ps));
	}
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
		vector<Point> ps(n);
		for(auto& p:ps) cin>>p.x>>p.y;
		vector<Point> qs=ConvexHull(ps);

		vd res(n);
		if(qs.size()==2){
			for(auto q:qs)
				rep(i,n) if(ps[i]==q)
					res[i]=0.5;
		}
		else{
			rep(i,qs.size()){
				Point p=qs[(i-1+qs.size())%qs.size()],q=qs[i],r=qs[(i+1)%qs.size()];
				double arg=(Arg(r-q)-Arg(q-p))/(2*PI);
				if(arg<0) arg++;
				if(1<arg) arg--;
				rep(j,n) if(ps[j]==qs[i])
					res[j]=arg;
			}
		}

		rep(i,n)
			printf("%.9f\n",res[i]);
	}
}
