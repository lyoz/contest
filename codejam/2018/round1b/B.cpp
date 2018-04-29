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

constexpr int ANY=1e9+1;

tuple<int,int> calc1(const vi& xs,const vi& ys,int first,int mid,int last)
{
	int i,j,x=xs[mid],y=ANY;
	for(j=mid;j<last;j++)
		if(xs[j]!=x)
			break;
	if(j<last){
		y=ys[j];
		for(j=mid;j<last;j++)
			if(xs[j]!=x&&ys[j]!=y)
				break;
	}
	for(i=mid;i>=first;i--)
		if(xs[i]!=x){
			if(y==ANY)
				y=ys[i];
			if(y!=ys[i])
				break;
		}
	i++;
	return {i,j};
}

tuple<int,int> calc2(const vi& xs,const vi& ys,int first,int mid,int last)
{
	int i,j,x=xs[mid],y=ANY;
	for(i=mid;i>=first;i--)
		if(xs[i]!=x)
			break;
	if(i>=first){
		y=ys[i];
		for(;i>=first;i--)
			if(xs[i]!=x&&ys[i]!=y)
				break;
	}
	i++;
	for(j=mid;j<last;j++)
		if(xs[j]!=x){
			if(y==ANY)
				y=ys[j];
			if(y!=ys[j])
				break;
		}
	return {i,j};
}

void update(map<int,int>& f,tuple<int,int> t)
{
	f[get<0>(t)]+=get<1>(t);
}

tuple<int,int> dfs(vi& ls,vi& rs,int first,int last)
{
	if(last-first==0)
		return {0,1};
	if(last-first==1)
		return {last-first,1};

	int mid=(first+last)/2;
	map<int,int> res;

	set<tuple<int,int>> ranges;
	rep(_,2){
		const vi& xs=_%2==0?ls:rs;
		const vi& ys=_%2==0?rs:ls;
		ranges.insert(calc1(xs,ys,first,mid,last));
		ranges.insert(calc2(xs,ys,first,mid,last));
	}
	for(auto range:ranges)
		res[get<1>(range)-get<0>(range)]++;

	update(res,dfs(ls,rs,first,mid));
	update(res,dfs(ls,rs,mid+1,last));
	return *res.rbegin();
}

void solve()
{
	int s; cin>>s;
	vi ls(s),rs(s);
	rep(i,s){
		int d,a,b; cin>>d>>a>>b;
		ls[i]=d-b,rs[i]=d+a;
	}

	auto res=dfs(ls,rs,0,s);
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
