#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cerr<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cerr<<endl;}while(0)
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vvvl=vector<vvl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vvvd=vector<vvd>;
using vs=vector<string>;
using vvs=vector<vs>;

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

vi input(int n)
{
	vi a(n);
	rep(i,n) cin>>a[i];
	return a;
}

int output(const vi& a)
{
	rep(i,a.size())
		cout<<a[i]<<(i+1<a.size()?" ":"");
	cout<<endl;
	int res; cin>>res;
	return res;
}

int solve(int n)
{
	for(int bump=0;;){
		vi a=input(n);
		rep(i,n) a[i]--;

		vi vis(n);
		vvi ss;
		rep(i,n) if(!vis[i]&&a[i]!=i){
			vi s;
			for(int j=i;!vis[j];j=a[j]){
				s.push_back(j);
				vis[j]=1;
			}
			ss.push_back(s);
		}

		int color=0;
		vi b(n,-1);
		for(auto s:ss){
			constexpr int m=5;
			for(int i=0;i<s.size();i+=m){
				int l=i,r=min<int>(i+m,s.size());
				if(r-l==m){
					b[s[l]]=b[s[r-1]]=++color;
					color++;
					for(int j=l+1;j<r-1;j++)
						b[s[j]]=color;
				}
				else{
					color++;
					for(int j=l;j<r;j++)
						b[s[j]]=color;
				}
			}
		}
		for(int& x:b)
			if(x==-1)
				x=++color;

		bump++;
		if(output(b)==1)
			return bump;
	}
}

int main()
{
	int tc,n,k; cin>>tc>>n>>k;
	int sum=0;
	rep(_,tc)
		sum+=solve(n);
	dump(sum); // sum=9971 (local testing tool)
}
