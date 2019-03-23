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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,q;cin>>n>>q&&n|q;){
		vl a(n);
		rep(i,n) cin>>a[i];

		vl sum(n+1),sume(n+1),sumo(n+1);
		rep(i,n)
			sum[i+1]=sum[i]+a[i];
		rep(i,n){
			sume[i+1]=sume[i];
			sumo[i+1]=sumo[i];
			if(i%2==0)
				sume[i+1]+=a[i];
			else
				sumo[i+1]+=a[i];
		}

		rep(_,q){
			ll x; cin>>x;
			ll lo=0,hi=1e9;
			while(lo<hi){
				ll mi=(lo+hi)/2;
				int l=lower_bound(all(a),x-mi)-begin(a);
				int r=lower_bound(all(a),x+mi)-begin(a);
				if(r-l>n-r)
					hi=mi;
				else
					lo=mi+1;
			}
			// 青木くんが取る区間: [al,ar)
			int al=lower_bound(all(a),x-(lo-1))-begin(a);
			int ar=lower_bound(all(a),x+(lo-1))-begin(a);
			// 高橋くんが取る区間: [tl,n)
			int tl=n-(ar-al);
			while(ar<tl){
				tl--;
				if(al==0&&ar==tl)
					break;
				if(al>0&&(ar==tl||abs(x-a[al-1])<=abs(x-a[ar])))
					al--;
				else
					ar++;
			}

			ll res=sum[n]-sum[tl];
			if(al%2==0)
				res+=sumo[al];
			else
				res+=sume[al];
			cout<<res<<endl;
		}
	}
}
