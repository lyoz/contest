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

bool ok(string s)
{
	int n=s.size();
	return n%2==0&& s.substr(0,n/2)==s.substr(n/2);
}

int count(string s)
{
	int n=s.size();
	int res=0;
	rep(i,1<<n){
		string t;
		rep(j,n)
			if(i>>j&1)
				t+=s[j];
		res+=ok(t);
	}
	return res;
}

void test()
{
	dump(count("aa"));
	dump(count("abab"));
	dump(count("abba"));
	dump(count("abcabc"));
	dump(count("abccab"));
	dump(count("abcdcabd"));
	dump(count("abcddcab"));
}

int main()
{
	for(ll n;cin>>n&&n;){
		n++;
		int m=64-__builtin_clzll(n);
		deque<int> a,b;
		int c=0;
		per(i,m-1){
			a.push_back(++c);
			b.push_back(c);
			if(n>>i&1){
				a.push_back(++c);
				b.push_front(c);
			}
		}
		cout<<2*c<<endl;
		rep(i,a.size()) cout<<a[i]<<' ';
		rep(i,b.size()) cout<<b[i]<<" \n"[i+1==b.size()];
	}
}
