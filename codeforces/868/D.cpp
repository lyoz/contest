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
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

constexpr int K_MAX=16;

string prefix(const string& s,int n)
{
	assert(s.size()>=n);
	return s.substr(0,n);
}

string suffix(const string& s,int n)
{
	assert(s.size()>=n);
	return s.substr(s.size()-n);
}

// 長さkのビット列が2^k個seに含まれているならtrue
bool in(const set<string>& se,int k)
{
	rep(b,1<<k){
		string s;
		rep(i,k)
			s+="01"[b>>i&1];
		if(!se.count(s))
			return false;
	}
	return true;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		vs ss(n);
		rep(i,n) cin>>ss[i];

		vector<set<string>> ses;
		for(string s:ss){
			set<string> se;
			rep(i,s.size()) repi(j,i,s.size())
				se.insert(s.substr(i,j-i+1));
			ses.push_back(se);
		}

		int m; cin>>m;
		rep(_,m){
			int a,b; cin>>a>>b; a--,b--;
			{
				string s=ss[a]+ss[b];
				if(s.size()>2*K_MAX)
					s=prefix(s,K_MAX)+".."+suffix(s,K_MAX);
				ss.push_back(s);
			}
			{
				set<string> se=ses[a]; se.insert(all(ses[b]));
				for(int k=2;k<=K_MAX;k++){
					for(int suf_len=k-1;suf_len>=1;suf_len--){
						int pre_len=k-suf_len;
						if(ss[a].size()<suf_len||ss[b].size()<pre_len)
							continue;
						se.insert(suffix(ss[a],suf_len)+prefix(ss[b],pre_len));
					}
				}
				ses.push_back(se);
			}
			for(int k=1;;k++)
				if(!in(ses.back(),k)){
					cout<<k-1<<endl;
					break;
				}
		}
	}
}
