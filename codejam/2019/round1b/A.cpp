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

void solve()
{
	int n,q; cin>>n>>q;
	vi xs(n),ys(n);
	string ds;
	rep(i,n){
		char d; cin>>xs[i]>>ys[i]>>d;
		ds+=d;
	}

	int h,w;

	vi xs2={0,q};
	rep(i,n) for(int x=max(xs[i]-1,0);x<=min(xs[i]+1,q);x++)
		xs2.push_back(x);
	sort(all(xs2));
	xs2.erase(unique(all(xs2)),end(xs2));
	rep(i,n) xs[i]=lower_bound(all(xs2),xs[i])-begin(xs2);
	w=lower_bound(all(xs2),q)-begin(xs2);

	vi ys2={0,q};
	rep(i,n) for(int y=max(ys[i]-1,0);y<=min(ys[i]+1,q);y++)
		ys2.push_back(y);
	sort(all(ys2));
	ys2.erase(unique(all(ys2)),end(ys2));
	rep(i,n) ys[i]=lower_bound(all(ys2),ys[i])-begin(ys2);
	h=lower_bound(all(ys2),q)-begin(ys2);

	vvi grid(h+2,vi(w+2));
	rep(i,n){
		int x=xs[i],y=ys[i];
		if(ds[i]=='W')
			grid[0][0]++,grid[0][x]--,grid[h+1][0]--,grid[h+1][x]++;
		else if(ds[i]=='E')
			grid[0][x+1]++,grid[0][w+1]--,grid[h+1][x+1]--,grid[h+1][w+1]++;
		else if(ds[i]=='S')
			grid[0][0]++,grid[0][w+1]--,grid[y][0]--,grid[y][w+1]++;
		else if(ds[i]=='N')
			grid[y+1][0]++,grid[y+1][w+1]--,grid[h+1][0]--,grid[h+1][w+1]++;
	}
	rep(i,h+2) rep(j,w+1)
		grid[i][j+1]+=grid[i][j];
	rep(i,h+1) rep(j,w+2)
		grid[i+1][j]+=grid[i][j];

	int mx=-INF;
	tuple<int,int> res;
	rep(j,w+1) rep(i,h+1) {
		if(mx<grid[i][j]){
			mx=grid[i][j];
			res=mt(xs2[j],ys2[i]);
		}
	}
	cout<<get<0>(res)<<' '<<get<1>(res)<<endl;
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
