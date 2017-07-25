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

bool match(const string& s,const string& p,const vi& flg)
{
	if(s.size()!=p.size())
		return false;

	rep(i,s.size())
		if(!(s[i]==p[i]||p[i]=='?'&&flg[s[i]-'a']))
			return false;
	return true;
}

bool black(const string& s,const vi& flg)
{
	for(char c:s)
		if(flg[c-'a'])
			return false;
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for(string w,p;cin>>w>>p;){
		vi flg(26);  // 0:bad, 1:good
		for(char c:w) flg[c-'a']=1;

		int n; cin>>n;
		if(count(all(p),'*')){
			int i=find(all(p),'*')-begin(p);
			string pl=p.substr(0,i),pr=p.substr(i+1);
			rep(_,n){
				string s; cin>>s;
				if(s.size()<pl.size()+pr.size())
					cout<<"NO"<<endl;
				else{
					int j=s.size()-pr.size();
					string sl=s.substr(0,i);
					string sc=s.substr(i,j-i);
					string sr=s.substr(j);
					cout<<(match(sl,pl,flg)&&black(sc,flg)&&match(sr,pr,flg)?"YES":"NO")<<endl;
				}
			}
		}
		else{
			rep(_,n){
				string s; cin>>s;
				cout<<(s.size()==p.size()&&match(s,p,flg)?"YES":"NO")<<endl;
			}
		}
	}
}
