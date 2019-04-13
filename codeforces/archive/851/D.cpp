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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	vi primes(2e6+10);
	repi(i,2,primes.size())
		primes[i]=i;
	repi(i,2,primes.size())
		if(primes[i])
			for(int j=i*i;j<primes.size();j+=i)
				primes[j]=0;
	primes.erase(remove(all(primes),0),end(primes));

	const int P=primes.back();

	for(int n,x,y;cin>>n>>x>>y&&n|x|y;){
		vi a(n);
		rep(i,n) cin>>a[i];

		const int t=x/y;  // t加えるコスト≦消すコスト

		vi f(P+1);
		rep(i,n)
			f[a[i]]++;

		vl cs(P+1),ss(P+1);
		rep(i,P){
			cs[i+1]=cs[i]+f[i];
			ss[i+1]=ss[i]+(ll)f[i]*i;
		}

		ll res=INF;
		for(int p:primes){
			ll sum=0;
			for(int i=p;i<=P;i+=p){
				// [i-p+1,i-t)は消す [i-t,i)は足す
				int j=max(i-p+1,i-t);
				sum+=(cs[j]-cs[i-p+1])*x;
				sum+=((cs[i]-cs[j])*i-(ss[i]-ss[j]))*y;
			}
			res=min(res,sum);
		}
		cout<<res<<endl;
	}
}
