#include <bits/stdc++.h>
using namespace std;

#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl
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

template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	return os<<'('<<p.first<<','<<p.second<<')';
}

template<typename Tuple>
void print_tuple(ostream&,const Tuple&){}
template<typename Car,typename... Cdr,typename Tuple>
void print_tuple(ostream& os,const Tuple& t){
	print_tuple<Cdr...>(os,t);
	os<<(sizeof...(Cdr)?",":"")<<get<sizeof...(Cdr)>(t);
}
template<typename... Args>
ostream& operator<<(ostream& os,const tuple<Args...>& t){
	print_tuple<Args...>(os<<'(',t);
	return os<<')';
}

template<typename Ch,typename Tr,typename C>
basic_ostream<Ch,Tr>& operator<<(basic_ostream<Ch,Tr>& os,const C& c){
	os<<'[';
	for(auto i=begin(c);i!=end(c);++i)
		os<<(i==begin(c)?"":" ")<<*i;
	return os<<']';
}

constexpr double INF=1e100;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

double dist(int x0,int y0,int r0,int x1,int y1,int r1)
{
	return max(sqrt(pow(x0-x1,2)+pow(y0-y1,2))-(r0+r1),0.);
}

int main()
{
	for(int x0,y0,x1,y1;cin>>x0>>y0>>x1>>y1;){
		int n; cin>>n;
		vi xs(n+2),ys(n+2),rs(n+2);
		rep(i,n) cin>>xs[i]>>ys[i]>>rs[i];
		xs[n]=x0; ys[n]=y0; rs[n]=0;
		xs[n+1]=x1; ys[n+1]=y1; rs[n+1]=0;

		vvd g(n+2,vd(n+2));
		rep(i,n+2) rep(j,n+2) g[i][j]=dist(xs[i],ys[i],rs[i],xs[j],ys[j],rs[j]);

		vd ds(n+2,INF); ds[n]=0;
		vi vis(n+2);
		rep(_,n+2){
			int i=-1;
			rep(j,n+2) if(!vis[j]) if(i==-1 || ds[i]>ds[j]) i=j;
			vis[i]=1;
			rep(j,n+2)
				ds[j]=min(ds[j],ds[i]+g[i][j]);
		}
		printf("%.9f\n",ds[n+1]);
	}
}
