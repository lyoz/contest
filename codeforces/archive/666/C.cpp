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

int mod_pow(int a,int b,int m)
{
	int x=1;
	for(;b;b/=2){
		if(b&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

int ncr(int n,int r)
{
	static vi fs,gs;
	static bool first=true;
	if(first){
		fs.resize(100001); fs[0]=1;
		gs.resize(100001); gs[0]=1;
		repi(i,1,fs.size()){
			fs[i]=(ll)fs[i-1]*i%MOD;
			gs[i]=mod_pow(fs[i],MOD-2,MOD);
		}
		first=false;
	}
	return (ll)fs[n]*gs[r]%MOD*gs[n-r]%MOD;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	
	vi p25(100001);  // 25^i
	vi q26(100001);  // 26^(-i)
	{
		const int INV_26=mod_pow(26,MOD-2,MOD);
		p25[0]=q26[0]=1;
		repi(i,1,p25.size()){
			p25[i]=(ll)p25[i-1]*25%MOD;
			q26[i]=(ll)q26[i-1]*INV_26%MOD;
		}
	}
	
	for(int q;cin>>q && q;){
		string s="#"; cin>>s;
		map<int,vector<int>> memo;
		while(q--){
			int t; cin>>t;
			if(t==1)  // update
				cin>>s;
			else{  // query
				int m=s.size();
				if(!memo.count(m)){
					vi& x=memo[m];
					x.resize(m);
					repi(i,m-1,100000)
						x.push_back((x[i]+(ll)ncr(i,m-1)*p25[i-(m-1)]%MOD*q26[i+1]%MOD)%MOD);
				}
				int n; cin>>n;
				cout<<(ll)mod_pow(26,n,MOD)*memo[m][n]%MOD<<endl;
			}
		}
	}
}
