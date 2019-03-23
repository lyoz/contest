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
	for(int n;cin>>n && n;){
		vi a(n),b(n);
		rep(i,n) cin>>a[i];
		rep(i,n) cin>>b[i];

		vi amin(n),amax(n);
		amin[0]=amax[0]=a[0];
		repi(i,1,n){
			if(a[i-1]<a[i])
				amin[i]=amax[i]=a[i];
			else{
				amin[i]=1;
				amax[i]=amax[i-1];
			}
		}
		vi bmin(n),bmax(n);
		bmin[n-1]=bmax[n-1]=b[n-1];
		per(i,n-1){
			if(b[i]>b[i+1])
				bmin[i]=bmax[i]=b[i];
			else{
				bmin[i]=1;
				bmax[i]=bmax[i+1];
			}
		}

		ll res=1;
		rep(i,n){
			int mn=max(amin[i],bmin[i]),mx=min(amax[i],bmax[i]);
			if(mn>mx){
				res=0;
				break;
			}
			(res*=mx-mn+1)%=MOD;
		}

		cout<<res<<endl;
	}
}
