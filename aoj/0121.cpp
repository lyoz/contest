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

int main()
{
	queue<string> q;
	unordered_map<string,int> dist;
	q.push("01234567");
	dist.emplace("01234567",0);
	while(q.size()){
		string s=q.front(); q.pop();
		int d=dist[s];
		int x=s.find('0');
		rep(k,4){
			int i=x/4+"\xff\x1\0\0"[k],j=x%4+"\0\0\xff\x1"[k];
			if(i<0 || 2<=i || j<0 || 4<=j) continue;
			int y=i*4+j;
			swap(s[x],s[y]);
			if(!dist.count(s)){
				q.push(s);
				dist.emplace(s,d+1);
			}
			swap(s[x],s[y]);
		}
	}
	
	for(int a[8];;){
		rep(i,8) cin>>a[i];
		if(cin.eof()) break;
		string s(8,'0');
		rep(i,8) s[i]+=a[i];
		cout<<dist[s]<<endl;
	}
}
