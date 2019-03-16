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
using pll=pair<ll,ll>;

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
	for(int x,y,z;cin>>x>>y>>z&&x|y|z;){
		int n=x+y+z;
		vl as(n),bs(n),cs(n);
		rep(i,n) cin>>as[i]>>bs[i]>>cs[i];

		vector<tuple<ll,ll,ll>> ts(n);
		rep(i,n) ts[i]=mt(as[i],bs[i],cs[i]);

		sort(all(ts),[](auto a,auto b){return get<0>(a)-get<1>(a)<get<0>(b)-get<1>(b);});

		vl max1(n+1);
		{
			auto get_diff=[](auto t){return get<1>(t)-get<2>(t);};
			vl csum(n+1),dsum(n+1);
			rep(i,n){
				csum[i+1]=csum[i]+get<2>(ts[i]);
				dsum[i+1]=dsum[i]+get_diff(ts[i]);
			}
			priority_queue<ll,vector<ll>,greater<ll>> pq;
			ll tmp=0;
			rep(i,y+z+1){
				max1[i]=dsum[i]-tmp;
				pq.emplace(get_diff(ts[i]));
				if(pq.size()>y){
					tmp+=pq.top();
					pq.pop();
				}
			}
			repi(i,y,y+z+1)
				max1[i]+=csum[i];
		}

		vl max2(n+1);
		{
			auto get_diff=[](auto t){return get<0>(t)-get<2>(t);};
			vl csum(n+1),dsum(n+1);
			per(i,n){
				csum[i]=csum[i+1]+get<2>(ts[i]);
				dsum[i]=dsum[i+1]+get_diff(ts[i]);
			}
			priority_queue<ll,vector<ll>,greater<ll>> pq;
			ll tmp=0;
			peri(i,y,n){
				pq.emplace(get_diff(ts[i]));
				if(pq.size()>x){
					tmp+=pq.top();
					pq.pop();
				}
				max2[i]=dsum[i]-tmp;
			}
			repi(i,y,y+z+1)
				max2[i]+=csum[i];
		}

		ll res=0;
		repi(i,y,y+z+1)
			res=max(res,max1[i]+max2[i]);
		cout<<res<<endl;
	}
}
