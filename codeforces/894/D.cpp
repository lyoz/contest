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

	for(ll n,m;cin>>n>>m&&n|m;){
		vector<ll> ls(n-1);
		rep(i,n-1) cin>>ls[i];

		// root:0
		// 頂点iの子は2*i+1と2*i+2, 頂点iの親はfloor((i-1)/2)

		vector<vector<tuple<int,int>>> ds(n);  // (dist,index)
		per(i,n){
			auto merge_children=[&](int c1,int c2){
				vector<tuple<int,int>> a,b;
				if(c1<n)
					for(auto t:ds[c1])
						a.emplace_back(ls[c1-1]+get<0>(t),get<1>(t));
				if(c2<n)
					for(auto t:ds[c2])
						b.emplace_back(ls[c2-1]+get<0>(t),get<1>(t));
				vector<tuple<int,int>> res;
				merge(all(a),all(b),back_inserter(res));
				return res;
			};
			auto children=merge_children(2*i+1,2*i+2);
			ds[i].emplace_back(0,i);
			ds[i].insert(end(ds[i]),all(children));
		}

		vector<vector<ll>> ss(n);
		rep(i,n){
			ss[i].push_back(0);
			for(auto t:ds[i]) ss[i].push_back(ss[i].back()+get<0>(t));
		}

		rep(_,m){
			ll a,h; cin>>a>>h; a--;
			ll res=0;
			for(int p=-1;h>0;){
				res+=h;
				for(int c:{a*2+1,a*2+2}) if(c<n&&c!=p){
					int lo=0,hi=ds[c].size();
					while(lo<hi){
						int mi=(lo+hi)/2;
						if(get<0>(ds[c][mi])+ls[c-1]>h)
							hi=mi;
						else
							lo=mi+1;
					}
					res+=lo*(h-ls[c-1])-ss[c][lo];
				}
				if(a==0) break;
				tie(p,a,h)=mt(a,(a-1)/2,h-ls[a-1]);
			}
			cout<<res<<endl;
		}
	}
}
