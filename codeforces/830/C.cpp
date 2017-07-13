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

// a/dの商が切り替わる最小のdたち
// n=100なら1,2,3,...,34,51,101を返す
vi divisors(int n)
{
	vi res={1};
	for(int r=n;r>0;){
		ll d=n/r+1;
		res.push_back(d);
		r=n/d;
	}
	return res;
}

int main()
{
	for(ll n,k;cin>>n>>k&&n|k;){
		vl a(n);
		rep(i,n) cin>>a[i];

		// Σ((a[i]以上である最大のdの倍数)-a[i]) ≦ k
		// (左辺) = Σ((a[i]+d-1)/d*d - a[i])
		//        = Σ((a[i]-1)/d*d + d - a[i])
		//        = d*n + d*Σ((a[i]-1)/d) - Σa[i]
		//        = d*(n+Σ((a[i]-1)/d)) - Σa[i]

		vl ds;
		for(ll x:a){
			auto tmp=divisors(x-1);
			ds.insert(end(ds),all(tmp));
		}
		sort(all(ds));
		ds.erase(unique(all(ds)),end(ds));

		ll asum=accumulate(all(a),0ll);

		ll res=0;
		rep(i,ds.size()){
			ll dmin=ds[i],adsum=0;
			for(ll x:a)
				adsum+=(x-1)/dmin;

			// d*(n+adsum)-asum <= k
			// d <= (k+asum)/(n+adsum)
			ll d=(k+asum)/(n+adsum);
			if(d<dmin)
				continue;
			if(i+1<ds.size())
				d=min(d,ds[i+1]-1);

			res=max(res,d);
		}

		cout<<res<<endl;
	}
}
