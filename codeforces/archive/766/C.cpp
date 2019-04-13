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

bool ok(int size,const vi& a,const vi& f)
{
	int mn=INF;
	rep(i,26) if(f[i]) mn=min(mn,a[i]);
	return size<=mn;
}

int main()
{
	for(int n;cin>>n;){
		string s; cin>>s;
		vi a(26);
		rep(i,26) cin>>a[i];

		vl dp(n+1); dp[0]=1;
		vi f(26);
		int substr_max=0;
		ll sum=0;
		for(int i=0,j=0;j<n;j++){
			(sum+=dp[j])%=MOD;
			for(f[s[j]-'a']++;!ok(j-i+1,a,f);i++){
				f[s[i]-'a']--;
				((sum-=dp[i])+=MOD)%=MOD;
			}
			substr_max=max(substr_max,j-i+1);
			dp[j+1]=sum;
		}
		cout<<dp[n]<<endl;
		cout<<substr_max<<endl;

		fill(all(f),0);
		int split_min=1;
		for(int i=0,j=0;j<n;){
			f[s[j]-'a']++;
			if(!ok(j-i+1,a,f)){
				fill(all(f),0);
				split_min++;
				i=j;
			}
			else{
				j++;
			}
		}
		cout<<split_min<<endl;
	}
}
