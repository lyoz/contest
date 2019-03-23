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

vi f(vl xs,vl ys,int a,ll d)
{
	map<ll,map<ll,int>> xy, yx;
	rep(i,xs.size()){
		ll x=xs[i],y=ys[i];
		xy[x][y]=i;
		yx[y][x]=i;
	}

	vi res(1,a);
	xy[xs[a]].erase(ys[a]);
	yx[ys[a]].erase(xs[a]);
	rep(k,res.size()){
		int u=res[k];
		ll x=xs[u],y=ys[u];
		for(ll x0:{x-d,x+d})
			if(xy.count(x0)){
				auto& c=xy[x0];
				for(auto i=c.lower_bound(y-d),j=c.upper_bound(y+d);i!=j;c.erase(i++)){
					int v=i->second;
					res.push_back(v);
					yx[ys[v]].erase(xs[v]);
				}
			}
		for(ll y0:{y-d,y+d})
			if(yx.count(y0)){
				auto& c=yx[y0];
				for(auto i=c.lower_bound(x-d),j=c.upper_bound(x+d);i!=j;c.erase(i++)){
					int v=i->second;
					res.push_back(v);
					xy[xs[v]].erase(ys[v]);
				}
			}
	}
	return res;
}

ll g(vl xs,vl ys,vi vs,ll d)
{
	vector<tuple<ll,ll>> xy,yx;
	rep(i,xs.size()){
		xy.emplace_back(xs[i],ys[i]);
		yx.emplace_back(ys[i],xs[i]);
	}
	sort(all(xy)); sort(all(yx));

	ll res=0;
	for(int v:vs){
		int x=xs[v],y=ys[v];
		for(ll x0:{x-d,x+d}){
			auto i=lower_bound(all(xy),mt(x0,y-d));
			auto j=upper_bound(all(xy),mt(x0,y+d));
			res+=j-i;
		}
		for(ll y0:{y-d,y+d}){
			auto i=upper_bound(all(yx),mt(y0,x-d));
			auto j=lower_bound(all(yx),mt(y0,x+d));
			res+=j-i;
		}
	}
	return res;
}

int main()
{
	for(int n,a,b;cin>>n>>a>>b&&n|a|b;){
		vl xs(n),ys(n);
		rep(i,n){
			int x,y; cin>>x>>y;
			tie(xs[i],ys[i])=mt(x+y,-x+y);
		}
		a--,b--;
		ll d=max(abs(xs[a]-xs[b]),abs(ys[a]-ys[b]));

		vi vs=f(xs,ys,a,d);
		cout<<g(xs,ys,vs,d)/2<<endl;
	}
}
