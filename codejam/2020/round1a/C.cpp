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

vector<tuple<int,int>> get_neighbors(const vector<set<int>>& js, const vector<set<int>>& is,int i,int j)
{
	vector<tuple<int,int>> res;
	// upper
	auto it=is[j].lower_bound(i);
	if(it!=begin(is[j]))
		res.emplace_back(*--it,j);
	// lower
	it=is[j].upper_bound(i);
	if(it!=end(is[j]))
		res.emplace_back(*it,j);
	// left
	it=js[i].lower_bound(j);
	if(it!=begin(js[i]))
		res.emplace_back(i,*--it);
	// right
	it=js[i].upper_bound(j);
	if(it!=end(js[i]))
		res.emplace_back(i,*it);
	return res;
}

void solve()
{
	int h,w; cin>>h>>w;
	vvi grid(h,vi(w));
	rep(i,h) rep(j,w) cin>>grid[i][j];

	ll sum=0;
	vector<set<int>> js(h),is(w);
	set<tuple<int,int>> s;
	rep(i,h) rep(j,w){
		sum+=grid[i][j];
		js[i].insert(j);
		is[j].insert(i);
		s.emplace(i,j);
	}

	ll res=0;
	for(;;){
		res+=sum;
		set<tuple<int,int>> elims;
		for(auto t:s){
			int ci,cj; tie(ci,cj)=t;
			vector<tuple<int,int>> ns=get_neighbors(js,is,ci,cj);

			int nsum=0;
			for(auto t:ns){
				int ni,nj; tie(ni,nj)=t;
				nsum+=grid[ni][nj];
			}
			if(grid[ci][cj]*ns.size()<nsum)
				elims.emplace(ci,cj);
		}
		if(elims.empty())
			break;
		s.clear();

		for(auto t:elims){
			int ci,cj; tie(ci,cj)=t;
			sum-=grid[ci][cj];
			js[ci].erase(cj);
			is[cj].erase(ci);
		}
		for(auto t:elims){
			int ci,cj; tie(ci,cj)=t;
			for(auto u:get_neighbors(js,is,ci,cj))
				s.insert(u);
		}
	}

	cout<<res<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}
