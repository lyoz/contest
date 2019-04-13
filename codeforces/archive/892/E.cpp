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
	vector<tuple<int,int,int,int>> hist;
	UnionFind(int n):data(n,-1){}
	int Find(int i){
		//return data[i]<0?i:(data[i]=Find(data[i]));
		return data[i]<0?i:Find(data[i]);
	}
	bool Unite(int a,int b){
		a=Find(a),b=Find(b);
		if(a==b) return false;
		if(-data[a]<-data[b]) swap(a,b);
		hist.emplace_back(a,b,data[a],data[b]);
		tie(data[a],data[b])=mt(data[a]+data[b],a);
		return true;
	}
	int Size(int i){
		return -data[Find(i)];
	}
	void Rollback(){
		int a,b,da,db; tie(a,b,da,db)=hist.back(); hist.pop_back();
		data[a]=da,data[b]=db;
	}
};

template<typename T,typename Compare>
auto make_priority_queue(const Compare& comp)
{
	return priority_queue<T,vector<T>,Compare>(comp);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		vector<tuple<int,int,int>> es;
		rep(i,m){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			es.emplace_back(u,v,w);
		}

		vi eis(m); iota(all(eis),0);
		sort(all(eis),[&](int i,int j){return get<2>(es[i])<get<2>(es[j]);});

		int q; cin>>q;
		vvi qs;
		rep(_,q){
			int size; cin>>size;
			vi qis(size);
			for(int& i:qis) cin>>i,i--;
			sort(all(qis),[&](int i,int j){return get<2>(es[i])<get<2>(es[j]);});
			qs.push_back(qis);
		}

		vi res(q,1);

		UnionFind uf(n);
		auto pq=make_priority_queue<tuple<int,int>>([&](auto a,auto b){
			int i=qs[get<0>(a)][get<1>(a)],j=qs[get<0>(b)][get<1>(b)];
			return get<2>(es[i])>get<2>(es[j]);
		});
		rep(i,q) pq.emplace(i,0);

		for(int l=0;pq.size();){
			int ci,cl,cr; tie(ci,cl)=pq.top(); pq.pop();
			int cw=get<2>(es[qs[ci][cl]]);
			for(;l<m&&get<2>(es[eis[l]])<cw;l++){
				int u,v; tie(u,v,ignore)=es[eis[l]];
				uf.Unite(u,v);
			}
			for(cr=cl;cr<qs[ci].size()&&get<2>(es[qs[ci][cr]])==cw;cr++);

			int cnt=0;
			repi(i,cl,cr){
				int u,v; tie(u,v,ignore)=es[qs[ci][i]];
				if(uf.Unite(u,v))
					cnt++;
				else
					res[ci]=false;
			}
			rep(_,cnt)
				uf.Rollback();
			if(cr<qs[ci].size()&&res[ci])
				pq.emplace(ci,cr);
		}

		rep(i,q) cout<<(res[i]?"YES":"NO")<<endl;
	}
}
