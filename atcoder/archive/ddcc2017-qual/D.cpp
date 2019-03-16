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

bool is_vertical_symmetry(const vs& a)
{
	vs b=a;
	reverse(all(b));
	return a==b;
}

bool is_horizontal_symmetry(const vs& a)
{
	vs b=a;
	rep(i,b.size()) reverse(all(b[i]));
	return a==b;
}

int solve(int h,int w,int vscore,int hscore,vs grid)
{
	int cnt1=0,cnt2=0,cnt3=0,res=0;

	// 左右対称にする
	{
		vector<tuple<int,int>> ps1,ps2;
		rep(i,h) rep(j,w){
			if(grid[i][j]=='S'&&grid[i][w-1-j]=='.'){
				if(grid[h-1-i][j]=='S')
					ps1.emplace_back(i,j);
				else
					ps2.emplace_back(i,j);
			}
		}
		for(auto p:ps2){
			int i,j; tie(i,j)=p;
			grid[i][j]='.';
		}
		cnt1+=ps2.size();

		bool flg=is_vertical_symmetry(grid);
		if(flg&&ps2.size()) res+=vscore;

		for(auto p:ps1){
			int i,j; tie(i,j)=p;
			grid[i][j]='.';
		}
		cnt1+=ps1.size();
		if(flg) res+=vscore*(ps1.size()/2);
	}
	if(cnt1) res+=hscore;

	// 上下対称にする
	{
		vector<tuple<int,int>> ps;
		rep(i,h) rep(j,w){
			if(grid[i][j]=='S'&&grid[h-1-i][j]=='.')
				ps.emplace_back(i,j);
		}
		for(auto p:ps){
			int i,j; tie(i,j)=p;
			grid[i][j]='.';
		}
		res+=hscore*(ps.size()/2);
		cnt2+=ps.size();
	}
	if(cnt2) res+=vscore;

	// 4つずつ'S'を消す
	rep(i,h) rep(j,w) cnt3+=grid[i][j]=='S';
	for(;cnt3;cnt3-=4)
		res+=max(vscore,hscore)+vscore+hscore;

	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w;cin>>h>>w&&h|w;){
		int vscore,hscore; cin>>vscore>>hscore;
		vs grid(h);
		rep(i,h) cin>>grid[i];

		int res=solve(h,w,vscore,hscore,grid);
		vs grid2(w,string(h,'#'));
		rep(i,h) rep(j,w) grid2[j][i]=grid[i][j];
		res=max(res,solve(w,h,hscore,vscore,grid2));
		cout<<res<<endl;
	}
}
