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
	for(int m,n,q;cin>>m>>n>>q;){
		vvi a(m,vi(n));
		vvi is(m,vi(n)),js(m,vi(n));
		rep(i,m) rep(j,n) is[i][j]=i,js[i][j]=j;
		rep(_,q){
			int t; cin>>t;
			if(t==1){
				int r; cin>>r; r--;
				rotate(begin(is[r]),1+all(is[r]));
				rotate(begin(js[r]),1+all(js[r]));
			}
			else if(t==2){
				int c; cin>>c; c--;
				vi x(m);
				rep(i,m) x[i]=is[(i+1)%m][c];
				rep(i,m) is[i][c]=x[i];
				rep(i,m) x[i]=js[(i+1)%m][c];
				rep(i,m) js[i][c]=x[i];
			}
			else if(t==3){
				int r,c,x; cin>>r>>c>>x; r--,c--;
				a[is[r][c]][js[r][c]]=x;
			}
		}
		rep(i,m) rep(j,n) cout<<a[i][j]<<(j<n-1?' ':'\n');
	}
}
