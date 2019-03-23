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

mt19937 engine;

// クリークにできる(どの2点間にも辺がない)頂点群を得る
vi get_clique(const vvi& a,int n,vi& used)
{
	vi is;
	rep(i,a.size()) if(!used[i]) is.push_back(i);

	for(;;){
		shuffle(all(is),engine);
		bool ok=true;
		rep(i,n) repi(j,i+1,n)
			ok&=a[is[i]][is[j]]==0;
		if(ok){
			rep(i,n) used[is[i]]=1;
			return {begin(is),begin(is)+n};
		}
	}
}

vi get_path(const vvi& a,const vi& c5,const vi& c7,int n,vi& used)
{
	vi is;
	rep(i,a.size()) if(!used[i]) is.push_back(i);

	for(;;){
		shuffle(all(is),engine);
		bool ok=a[c5[0]][is[0]]==0;
		rep(i,n) ok&=a[is[i]][c7[0]]==0;
		rep(i,n-1) ok&=a[is[i]][is[i+1]]==0;
		if(ok){
			rep(i,n) used[is[i]]=1;
			return {begin(is),begin(is)+n};
		}
	}
}

void encode()
{
	int n,m; cin>>n>>m;
	vvi a(n,vi(n));
	rep(i,m){
		int u,v; cin>>u>>v; u--,v--;
		a[u][v]=a[v][u]=1;
	}
	ll x; cin>>x;

	vi deg(n);
	rep(i,n) rep(j,n) deg[i]+=a[i][j];

	vi used(n);
	rep(i,n) if(deg[i]>=10) used[i]=1; // 次数が大きいやつは使いにくいので捨てる

	vi c5=get_clique(a,5,used);
	vi c7=get_clique(a,7,used);
	vi path=get_path(a,c5,c7,60,used);

	vector<tuple<int,int>> es;
	rep(i,c5.size()) repi(j,i+1,c5.size()) es.emplace_back(c5[i],c5[j]);
	rep(i,c7.size()) repi(j,i+1,c7.size()) es.emplace_back(c7[i],c7[j]);
	es.emplace_back(c5[0],path[0]);
	rep(i,path.size()-1)
		es.emplace_back(path[i],path[i+1]);
	rep(i,path.size())
		if(x>>i&1) es.emplace_back(path[i],c7[0]);

	cout<<es.size()<<endl;
	for(auto e:es) cout<<get<0>(e)+1<<' '<<get<1>(e)+1<<endl;
}

void decode()
{
	int n,m; cin>>n>>m;
	vvi g(n);
	rep(i,m){
		int u,v; cin>>u>>v; u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vi c5,c7,path,flg(n);
	rep(i,n){
		if(g[i].size()==0)
			continue;
		else if(4<=g[i].size()&&g[i].size()<=5)
			flg[i]=5,c5.push_back(i);
		else if(6<=g[i].size())
			flg[i]=7,c7.push_back(i);
		else
			flg[i]=1;
	}
	int p0=-1;
	rep(i,n) if(flg[i]==1){
		for(int v:g[i]) if(flg[v]==5){
			p0=i;
			break;
		}
		if(p0!=-1) break;
	}
	path.push_back(p0);
	for(int i=0,p=-1,u=p0;i<59;i++)
		for(int v:g[u]) if(v!=p&&flg[v]==1){
			path.push_back(v);
			p=u,u=v;
			break;
		}
	ll res=0;
	rep(i,60) for(int v:g[path[i]]) if(flg[v]==7)
		res|=1ll<<i;
	cout<<res<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	string s; cin>>s;
	if(s=="encode")
		encode();
	else
		decode();
}
