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
	for(string s="#",t="#";cin>>s>>t && s!="#";){
		map<char,int> f;
		{
			for(int i=1;;i++){
				int d=0;
				for(int x=i;x;x/=10) d++;
				if(i+d==s.size()){
					for(char c:s) f[c]++;
					for(char c:t) f[c]--;
					for(char c:to_string(i)) f[c]--;
					break;
				}
			}
		}
		for(auto i=begin(f);i!=end(f);)
			if(i->second==0)
				i=f.erase(i);
			else
				i++;
		
		auto it=f.upper_bound('0');
		if(it==end(f)){
			cout<<t+string(f['0'],'0')<<endl;
			continue;
		}
		
		vs res;
		if(t[0]!='0'){
			string s=t;
			for(auto p:f) s.insert(end(s),p.second,p.first);
			res.push_back(s);
		}
		
		char p=it->first;
		it->second--;
		string a,b,c;
		for(auto p:f){
			if(p.first<t[0])  a.insert(end(a),p.second,p.first);
			if(p.first==t[0]) b.insert(end(b),p.second,p.first);
			if(p.first>t[0])  c.insert(end(c),p.second,p.first);
		}
		res.push_back(p+a+b+t+c);
		res.push_back(p+a+t+b+c);
		
		cout<<*min_element(all(res))<<endl;
	}
}
