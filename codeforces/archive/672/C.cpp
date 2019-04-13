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

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int main()
{
	for(double ax,ay,bx,by,rx,ry;cin>>ax>>ay>>bx>>by>>rx>>ry;){
		int n; cin>>n;
		vd xs(n),ys(n),ds(n);
		rep(i,n) cin>>xs[i]>>ys[i];
		
		ax-=rx,ay-=ry;
		bx-=rx,by-=ry;
		rep(i,n) xs[i]-=rx,ys[i]-=ry;
		
		rep(i,n) ds[i]=sqrt(xs[i]*xs[i]+ys[i]*ys[i]);
		vector<tuple<double,int>> ads{mt(0,-1)},bds{mt(0,-1)};
		rep(i,n){
			double ad=sqrt(pow(ax-xs[i],2)+pow(ay-ys[i],2));
			ads.emplace_back(ad-ds[i],i);
			double bd=sqrt(pow(bx-xs[i],2)+pow(by-ys[i],2));
			bds.emplace_back(bd-ds[i],i);
		}
		sort(all(ads)); sort(all(bds));
		
		double res=INFINITY;
		rep(i,min<int>(ads.size(),3)) rep(j,min<int>(bds.size(),3)){
			double ad,bd; int ai,bi; tie(ad,ai)=ads[i]; tie(bd,bi)=bds[j];
			if(ai==bi) continue;
			res=min(res,ad+bd);
		}
		printf("%.9f\n",res+2*accumulate(all(ds),0.));
	}
}
