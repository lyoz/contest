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

void solve_set1(vi ps,vi ns)
{
	vi cs;
	rep(i,ps.size())
		rep(j,ns[i])
			cs.push_back(ps[i]);
	int n=cs.size();

	int res=0;
	rep(s,1<<n){
		vi a,b;
		rep(i,n){
			if(s>>i&1)
				a.push_back(cs[i]);
			else
				b.push_back(cs[i]);
		}
		bool ok=true;
		int sum=accumulate(all(a),0),score=sum;
		for(int x:b){
			if(sum%x){
				ok=false;
				break;
			}
			sum/=x;
		}
		ok&=sum==1;
		if(ok)
			chmax(res,score);
	}
	cout<<res<<endl;
}

int set2_res=0;

void dfs(const vi& ps,const vi& ns,int i,vi& use,ll sum,ll pro)
{
	if(sum<pro)
		return;
	if(sum==pro){
		chmax(set2_res,sum);
		return;
	}
	if(i==ps.size())
		return;
	if(use[i]<ns[i]){
		use[i]++;
		dfs(ps,ns,i,use,sum-ps[i],pro*ps[i]);
		use[i]--;
	}
	dfs(ps,ns,i+1,use,sum,pro);
}

void solve_set2(vi ps,vi ns)
{
	set2_res=0;

	int sum=0;
	rep(i,ps.size())
		sum+=ps[i]*ns[i];

	vi use(ps.size()); // 積をとるほうの山で使う枚数
	dfs(ps,ns,0,use,sum,1);

	cout<<set2_res<<endl;
}

void solve()
{
	int m; cin>>m;
	vi ps(m),ns(m);
	rep(i,m) cin>>ps[i]>>ns[i];

	ll sum=accumulate(all(ns),0ll);
	if(sum<=100){ //  set1, set2
		solve_set2(ps,ns);
	}
	else{
		cout<<"X"<<endl;
	}
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
