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

void test()
{
	mt19937_64 engine((random_device())());
	auto rand=[&](ll a,ll b){
		uniform_int_distribution<ll> dist(a,b);
		return dist(engine);
	};

	const int U=2;
	const ll MMAX=ll(pow(10,U))-1;
	dump(U,MMAX);
	const int N=10000;
	vl ms(N),qs(N);
	vs rs(N);
	rep(i,N){
		ms[i]=rand(1,MMAX);
		qs[i]=rand(1,ms[i]);
		for(ll x=qs[i];x;x/=10){
			rs[i]+='A'+x%10;
		}
	}
	//rep(i,N)
	//	dump(ms[i],qs[i],rs[i]);

	vvi f(U,vi(10));
	rep(i,N){
		rep(j,rs[i].size())
			f[j][rs[i][j]-'A']++;
	}
	rep(i,U) dump(f[i]);
}

void solve()
{
	const int N=10000;

	int u; cin>>u;
	vl qs(N);
	vs rs(N);
	rep(i,N) cin>>qs[i]>>rs[i];
	rep(i,N) reverse(all(rs[i]));

	vvi f(u,vi(26));
	rep(i,N){
		rep(j,rs[i].size())
			f[j][rs[i][j]-'A']++;
	}

	vi is;
	rep(i,26)
		if(f[0][i]) is.push_back(i);

	// f[u-1][is[0],..is[9]] の中に
	// 0 に対応するアルファベットの出現回数は0
	// 1 に対応するアルファベットの出現回数は最も多い
	// 2 に対応するアルファベットの出現回数は2番目に多い
	// ...
	// 9 に対応するアルファベットの出現回数は9番目に多い
	sort(all(is),[&](int i,int j){return f[u-1][i]<f[u-1][j];});
	reverse(begin(is)+1,end(is));
	for(int i:is)
		cout<<char('A'+i);
	cout<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	//test();

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}
