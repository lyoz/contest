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

vvi get_psum(const vi& xs,const vi& ys,const vi& ss,int c,int t)
{
	vvi grid(100,vi(100));
	rep(i,xs.size())
		grid[ys[i]][xs[i]]+=(ss[i]+t)%(c+1);
	vvi psum(101,vi(101));
	rep(i,100) rep(j,100)
		psum[i+1][j+1]=grid[i][j];
	rep(i,101) rep(j,100)
		psum[i][j+1]+=psum[i][j];
	rep(i,100) rep(j,101)
		psum[i+1][j]+=psum[i][j];
	return psum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for(int n,q,c;cin>>n>>q>>c&&n|q|c;){
		vi xs(n),ys(n),ss(n);
		rep(i,n) cin>>xs[i]>>ys[i]>>ss[i],xs[i]--,ys[i]--;
		vector<vvi> psums(c+1);
		rep(i,c+1)
			psums[i]=get_psum(xs,ys,ss,c,i);
		rep(_,q){
			int t,x1,y1,x2,y2; cin>>t>>x1>>y1>>x2>>y2; x1--,y1--;
			auto& psum=psums[t%(c+1)];
			int res=psum[y2][x2]-psum[y2][x1]-psum[y1][x2]+psum[y1][x1];
			cout<<res<<endl;
		}
	}
}
