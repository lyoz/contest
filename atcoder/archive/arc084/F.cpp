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
constexpr int MOD=998244353;
constexpr double EPS=1e-9;

vi mod(vi a,vi b)
{
	int m=a.size(),n=b.size();
	int j=find(all(b),1)-begin(b);
	for(int i=0;i+(n-j)<=m;i++) if(a[i])
		rep(k,n-j) a[i+k]^=b[j+k];
	return a;
}

vi gcd(vi a,vi b)
{
	while(count(all(b),1))
		tie(a,b)=mt(b,mod(a,b));
	return vi(find(all(a),1),end(a));
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vi x;
		{
			string s; cin>>s;
			rep(j,s.size()) x.push_back(s[j]-'0');
		}
		vvi a(n);
		rep(i,n){
			string s; cin>>s;
			rep(j,s.size()) a[i].push_back(s[j]-'0');
		}

		vi g=a[0];
		repi(i,1,n) g=gcd(g,a[i]);

		ll res=0;
		vi y(x.size());
		for(int i=0;i+g.size()<=y.size();i++){
			res=(res*2+x[i])%MOD;
			if(y[i]!=x[i])
				rep(j,g.size()) y[i+j]^=g[j];
		}
		if(x<y)
			res=(res-1+MOD)%MOD;
		cout<<res+1<<endl;
	}
}
