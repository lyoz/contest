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

	int tc; cin>>tc;
	rep(_,tc){
		int n,d; cin>>n>>d;
		vi a(n+1);
		rep(i,n) cin>>a[i+1];

		map<int,int> rests;
		rep(i,n){
			int r=a[i+1]-a[i]-1;
			rests[r]++;
		}

		ll res=0;
		rep(i,n-1){
			int l=a[i+1]-a[i]-1,r=a[i+2]-a[i+1]-1;
			int x=a[i+2]-a[i]-1;
			if(--rests[l]==0)
				rests.erase(l);
			if(--rests[r]==0)
				rests.erase(r);
			rests[x]++;

			if(a[n]<d)
				chmax(res,min(begin(rests)->first,d-a[n]-1));

			int y=prev(end(rests))->first;
			assert(y>=1);
			if(--rests[y]==0)
				rests.erase(y);
			int l2=(y-1)/2,r2=y-1-l2;
			rests[l2]++;
			rests[r2]++;

			chmax(res,begin(rests)->first);

			for(int t:{l,r,y})
				rests[t]++;
			for(int t:{x,l2,r2})
				if(--rests[t]==0)
					rests.erase(t);
		}
		{
			int l=a[n]-a[n-1]-1;
			int x=d-a[n-1]-1;
			if(--rests[l]==0)
				rests.erase(l);
			rests[x]++;
			chmax(res,begin(rests)->first);
		}
		cout<<res<<endl;
	}
}
