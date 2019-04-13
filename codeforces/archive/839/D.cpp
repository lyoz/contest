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

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

int solve(vi a)
{
	int m=*max_element(all(a));
	vi cs(m+1);
	for(int x:a)
		for(int i=1;i*i<=x;i++)
			if(x%i==0){
				cs[i]++;
				cs[x/i]+=i*i!=x;
			}
	int res=0;
	vi ss(m+1);
	peri(i,2,m+1){
		if(cs[i]){
			ss[i]=(ll)cs[i]*ModPow(2,cs[i]-1,MOD)%MOD;
			for(int j=i+i;j<=m;j+=i)
				ss[i]=(ss[i]-ss[j]+MOD)%MOD;
			res=(res+(ll)i*ss[i])%MOD;
		}
	}
	return res;
}

int main()
{
	#ifdef ONLINE_JUDGE
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	#endif

	for(int n;cin>>n&&n;){
		vi a(n);
		rep(i,n) cin>>a[i];
		cout<<solve(a)<<endl;
	}
}
