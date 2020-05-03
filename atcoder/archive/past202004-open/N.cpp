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

constexpr ll INF=1e18;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

struct FenwickTree{
	vector<ll> data;
	FenwickTree(int n):data(n+1){}
	void AddRange(int i,ll x){
		for(;i;i-=i&-i)
			data[i]+=x;
	}
	void AddRange(int i,int j,ll x){
		AddRange(i,-x);
		AddRange(j,x);
	}
	ll Get(int i){
		ll res=0;
		for(i++;i<data.size();i+=i&-i)
			res+=data[i];
		return res;
	}
};

struct Event{
	int kind; // 1:領域の追加, 2:質問, 3:領域の削除
	ll x,y,d,c; // kind==2の場合はdにインデックスが入っている
	Event(int k,ll x,ll y,ll d=-1,ll c=-1):kind(k),x(x),y(y),d(d),c(c){}
	bool operator<(const Event& e)const{
		if(x!=e.x) return x>e.x;
		return kind>e.kind;
	}
};

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(ll n,q;cin>>n>>q&&n|q;){
		vl xmins(n),ymins(n),ds(n),cs(n);
		rep(i,n) cin>>xmins[i]>>ymins[i]>>ds[i]>>cs[i];
		vl as(q),bs(q);
		rep(i,q) cin>>as[i]>>bs[i];

		vl ymaxs(n);
		rep(i,n)
			ymaxs[i]=ymins[i]+ds[i]+1;

		vl ymap;
		rep(i,n){
			ymap.push_back(ymins[i]);
			ymap.push_back(ymaxs[i]);
		}
		rep(i,q){
			ymap.push_back(bs[i]);
		}
		sort(all(ymap)); ymap.erase(unique(all(ymap)),end(ymap));
		//dump(ymap);

		priority_queue<Event> pq;
		rep(i,n){
			pq.emplace(1,xmins[i],ymins[i],ds[i],cs[i]);
			pq.emplace(3,xmins[i]+ds[i],ymins[i],ds[i],cs[i]);
		}
		rep(i,q){
			pq.emplace(2,as[i],bs[i],i);
		}

		vl res(q);
		FenwickTree ft(ymap.size()+1);
		while(pq.size()){
			Event e=pq.top(); pq.pop();
			//dump(e.kind,e.x,e.y,e.d,e.c);
			if(e.kind==1){
				ll y0=lower_bound(all(ymap),e.y)-begin(ymap);
				ll y1=lower_bound(all(ymap),e.y+e.d+1)-begin(ymap);
				ft.AddRange(y0,y1,e.c);
				//dump(ft.data);
			}
			if(e.kind==2){
				ll y=lower_bound(all(ymap),e.y)-begin(ymap);
				int i=e.d;
				//dump(__LINE__,i,ft.Get(y));
				res[i]=ft.Get(y);
			}
			if(e.kind==3){
				ll y0=lower_bound(all(ymap),e.y)-begin(ymap);
				ll y1=lower_bound(all(ymap),e.y+e.d+1)-begin(ymap);
				ft.AddRange(y0,y1,-e.c);
			}
		}

		rep(i,q) cout<<res[i]<<endl;
		//dump(res);
	}
}
