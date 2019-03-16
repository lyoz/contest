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

template<typename T>
struct functor_traits:public functor_traits<decltype(&T::operator())>{};
template<typename C,typename Ret,typename... Args>
struct functor_traits<Ret(C::*)(Args...)const>{
	template<size_t I>
	using nth_argument_type=typename tuple_element<I,tuple<Args...>>::type;
	using first_argument_type=nth_argument_type<0>;
};
template<typename Compare,typename T=typename decay<typename functor_traits<Compare>::first_argument_type>::type>
priority_queue<T,vector<T>,Compare> make_priority_queue(Compare comp){
	return priority_queue<T,vector<T>,Compare>(comp);
}

int get_dist(const vi& xs,const vi& ys,int u,int v)
{
	return min(abs(xs[u]-xs[v]),abs(ys[u]-ys[v]));
}

int main()
{
	for(int n;cin>>n&&n;){
		vi xs(n),ys(n);
		rep(i,n) cin>>xs[i]>>ys[i];

		vi xis(n),yis(n);
		iota(all(xis),0); sort(all(xis),[&](int i,int j){return mp(xs[i],i)<mp(xs[j],j);});
		iota(all(yis),0); sort(all(yis),[&](int i,int j){return mp(ys[i],i)<mp(ys[j],j);});

		vi xrs(n),yrs(n);
		rep(i,n){
			xrs[xis[i]]=i;
			yrs[yis[i]]=i;
		}

		auto pq=make_priority_queue(greater<tuple<int,int>>());
		pq.emplace(0,0);
		vi dist(n,-1);
		while(pq.size()){
			int d,u; tie(d,u)=pq.top(); pq.pop();
			if(dist[u]!=-1) continue;
			dist[u]=d;
			for(int i=xrs[u]-1;i<=xrs[u]+1;i+=2) if(0<=i&&i<n){
				int v=xis[i];
				pq.emplace(get_dist(xs,ys,u,v),v);
			}
			for(int i=yrs[u]-1;i<=yrs[u]+1;i+=2) if(0<=i&&i<n){
				int v=yis[i];
				pq.emplace(get_dist(xs,ys,u,v),v);
			}
		}
		cout<<accumulate(all(dist),0ll)<<endl;
	}
}
