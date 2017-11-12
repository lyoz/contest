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

struct UnionFind{
	vi data;
	UnionFind(int n):data(n,-1){}
	int Find(int i){
		return data[i]<0?i:(data[i]=Find(data[i]));
	}
	bool Unite(int a,int b){
		a=Find(a),b=Find(b);
		if(a==b) return false;
		if(-data[a]<-data[b]) swap(a,b);
		data[a]+=data[b];
		data[b]=a;
		return true;
	}
	int Size(int i){
		return -data[Find(i)];
	}
};

string solve(const vs& ss)
{
	for(string s:ss)
		if(set<char>(all(s)).size()!=s.size())
			return "NO";

	int n=ss.size();
	vvi a(26);  // a[i]: char('a'+i)を含む文字列のindexたち
	rep(i,n) for(char c:ss[i])
		a[c-'a'].push_back(i);

	vi os(26,INF);
	rep(i,26) if(os[i]==INF&&a[i].size()){
		queue<tuple<int,int>> q;
		q.emplace(i,0);
		while(q.size()){
			int ci,co; tie(ci,co)=q.front(); q.pop();
			if(os[ci]!=INF){
				if(os[ci]!=co)
					return "NO";
				else
					continue;
			}
			os[ci]=co;
			for(int j:a[ci]){
				int k=ss[j].find('a'+ci);
				rep(l,ss[j].size())
					q.emplace(ss[j][l]-'a',co+l-k);
			}
		}
	}

	map<int,set<int>> ccs;
	{
		UnionFind uf(n);
		rep(i,26) repi(j,1,a[i].size())
			uf.Unite(a[i][0],a[i][j]);
		rep(i,n){
			set<int>& s=ccs[uf.Find(i)];
			for(char c:ss[i]) s.insert(c-'a');
		}
	}

	vs ts;
	for(auto p:ccs){
		auto cc=p.second;
		int mn=INF,mx=-INF;
		for(int i:cc){
			chmin(mn,os[i]);
			chmax(mx,os[i]);
		}
		string t(mx-mn+1,'#');
		for(int i:cc)
			if(exchange(t[os[i]-mn],'a'+i)!='#')
				return "NO";
		ts.push_back(t);
	}
	sort(all(ts));

	string res;
	for(string t:ts) res+=t;
	return res;
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
		cout<<solve(ss)<<endl;
	}
}
