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

using Pairs=vector<tuple<int,int>>;

void dfs(const vi& hash,int i,vi& used,Pairs& ps,vector<Pairs>& cands)
{
	int n=hash.size();
	if(i==n){
		cands.push_back(ps);
		return;
	}
	if(used[i]){
		dfs(hash,i+1,used,ps,cands);
		return;
	}
	used[i]=1;
	repi(j,i+1,n) if(!used[j]&&hash[i]==hash[j]){
		used[j]=1,ps.emplace_back(i,j);
		dfs(hash,i+1,used,ps,cands);
		used[j]=0,ps.pop_back();
	}
	used[i]=0;
}

string getcol(const vs& grid,int j,bool rev=false)
{
	string res;
	rep(i,grid.size()) res+=grid[i][j];
	if(rev) reverse(all(res));
	return res;
}

bool dfs2(const vs& grid,int i,vi& used,bool center)
{
	int w=grid[0].size();
	if(i==w)
		return true;
	if(used[i])
		return dfs2(grid,i+1,used,center);
	if(w&1&&!center){
		string col=getcol(grid,i);
		if(getcol(grid,i)==getcol(grid,i,true)){
			used[i]=1;
			if(dfs2(grid,i+1,used,true))
				return true;
			used[i]=0;
		}
	}
	used[i]=1;
	repi(j,i+1,w) if(!used[j]){
		if(getcol(grid,i)==getcol(grid,j,true)){
			used[j]=1;
			if(dfs2(grid,i+1,used,center))
				return true;
			used[j]=0;
		}
	}
	used[i]=0;
	return false;
}

bool solve2(vs grid)
{
	int h=grid.size(),w=grid[0].size();
	assert(h%2==0);

	vi rhash(h);
	rep(i,h){
		vi r(w);
		rep(j,w) r[j]=grid[i][j]-'a';
		sort(all(r));
		rep(j,w) ((rhash[i])*=26)+=r[j];
	}

	vector<vector<tuple<int,int>>> rcands;
	{
		vi rused(h);
		Pairs rps;
		dfs(rhash,0,rused,rps,rcands);
	}

	for(auto rcand:rcands){
		vs t,b;
		for(auto p:rcand){
			t.push_back(grid[get<0>(p)]);
			b.push_back(grid[get<1>(p)]);
		}
		t.insert(end(t),rbegin(b),rend(b));
		vi cused(w);
		if(dfs2(t,0,cused,false))
			return true;
	}
	return false;
}

bool solve(vs grid)
{
	int h=grid.size();
	if(h%2==0)
		return solve2(grid);

	rep(i,h){
		grid.push_back(grid[i]);
		if(solve2(grid))
			return true;
		grid.pop_back();
	}
	return false;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w;cin>>h>>w&&h|w;){
		vs grid(h);
		rep(i,h) cin>>grid[i];

		cout<<(solve(grid)?"YES":"NO")<<endl;
	}
}
