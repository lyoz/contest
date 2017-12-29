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

bool ok(const vs& grid,const vi& os,const vi& di,const vi& dj)
{
	int h=grid.size(),w=grid[0].size();
	int i0=-1,j0=-1;
	rep(i,h) rep(j,w) if(grid[i][j]=='S') i0=i,j0=j;
	for(int i=i0,j=j0,k=0;;k++){
		if(i<0||h<=i||j<0||w<=j||grid[i][j]=='#') return false;
		if(grid[i][j]=='E') return true;
		if(k==os.size()) break;
		i+=di[os[k]];
		j+=dj[os[k]];
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
		vi os;
		{
			string s; cin>>s;
			for(char c:s) os.push_back(c-'0');
		}

		int res=0;
		vi p={0,1,2,3};
		do{
			vi di(4),dj(4);
			rep(i,4){
				di[i]="\xff\x1\0\0"[p[i]];
				dj[i]="\0\0\xff\x1"[p[i]];
			}
			res+=ok(grid,os,di,dj);
		}while(next_permutation(all(p)));
		cout<<res<<endl;
	}
}
