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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(ll X,K;cin>>X>>K&&X|K;){
		vl rs(K+1);
		rep(i,K) cin>>rs[i+1];

		vl as(K+1),bs(K+1),xs(K+1),ys(K+1);
		as[0]=xs[0]=0;
		bs[0]=ys[0]=X;

		rep(i,K){
			ll e=rs[i+1]-rs[i];
			if(i%2==0){  // 減る
				xs[i+1]=max(xs[i]-e,0LL);
				ys[i+1]=max(ys[i]-e,0LL);
				if(0<=xs[i]-e){
					as[i+1]=as[i];
				}
				else{
					ll tmp=e-xs[i];
					as[i+1]=min(as[i]+tmp,bs[i]);
				}
				bs[i+1]=bs[i];
			}
			else{  // 増える
				xs[i+1]=min(xs[i]+e,X);
				ys[i+1]=min(ys[i]+e,X);
				if(ys[i]+e<=X){
					bs[i+1]=bs[i];
				}
				else{
					ll tmp=ys[i]+e-X;
					bs[i+1]=max(bs[i]-tmp,as[i]);
				}
				as[i+1]=as[i];
			}
		}

		int Q; cin>>Q;
		rep(_,Q){
			ll t,c; cin>>t>>c;
			int i=upper_bound(all(rs),t)-begin(rs)-1;

			ll e=t-rs[i];
			ll res=-1;
			if(i%2==0){
				if(c<=as[i])
					res=max(xs[i]-e,0LL);
				else if(c<=bs[i])
					res=max(xs[i]+(c-as[i])-e,0LL);
				else
					res=max(ys[i]-e,0LL);
			}
			else{
				if(c<=as[i])
					res=min(xs[i]+e,X);
				else if(c<=bs[i])
					res=min(ys[i]-(bs[i]-c)+e,X);
				else
					res=min(ys[i]+e,X);
			}
			cout<<res<<endl;
		}
	}
}
