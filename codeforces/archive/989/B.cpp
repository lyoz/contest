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

string fill(vs ss)
{
	int p=ss.size();
	string res;
	for(int i=0;i/p<ss[i%p].size();i++){
		char c=ss[i%p][i/p];
		res+=c=='.'?'0':c;
	}
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,p;cin>>n>>p&&n|p;){
		string s; cin>>s;

		vs ss(p);
		rep(i,n) ss[i%p]+=s[i];

		string res="No";
		rep(i,p){
			map<char,vi> f;
			rep(j,ss[i].size()) f[ss[i][j]].push_back(j);

			bool ok=false;
			if(f['.'].size()>=2){
				f['0'].push_back(f['.'].back()); f['.'].pop_back();
				f['1'].push_back(f['.'].back()); f['.'].pop_back();
				ok=true;
			}
			else if(f['0'].size()>=1&&f['.'].size()>=1){
				f['1'].push_back(f['.'].back()); f['.'].pop_back();
				ok=true;
			}
			else if(f['1'].size()>=1&&f['.'].size()>=1){
				f['0'].push_back(f['.'].back()); f['.'].pop_back();
				ok=true;
			}
			else if(f['0'].size()>=1&&f['1'].size()>=1){
				ok=true;
			}
				
			if(ok){
				for(int j:f['0']) ss[i][j]='0';
				for(int j:f['1']) ss[i][j]='1';
				for(int j:f['.']) ss[i][j]='.';
				res=fill(ss);
				break;
			}
		}
		cout<<res<<endl;
	}
}
