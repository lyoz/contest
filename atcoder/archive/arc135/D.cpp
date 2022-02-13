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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w;cin>>h>>w&&h|w;){
		vvl a(h,vl(w));
		rep(i,h) rep(j,w) cin>>a[i][j];

		rep(i,h) rep(j,w) if((i+j)%2)
			a[i][j]=-a[i][j];

		vl rsums(h),csums(w);
		rep(i,h) rep(j,w){
			rsums[i]+=a[i][j];
			csums[j]+=a[i][j];
		}

		ll res=max(
			accumulate(all(rsums),0ll,[](ll s,ll x){return s+abs(x);}),
			accumulate(all(csums),0ll,[](ll s,ll x){return s+abs(x);})
		);

		map<ll,vi> rq,cq; // sum,indices
		rep(i,h) rq[rsums[i]].push_back(i);
		rep(j,w) cq[csums[j]].push_back(j);

		vvl b(h,vl(w));
		// -,-
		for(;;){
			auto& [rsum,ris]=*begin(rq);
			auto& [csum,cis]=*begin(cq);
			if(!(rsum<0&&csum<0))
				break;
			auto &ris2=rq[rsum-max(rsum,csum)],&cis2=cq[csum-max(rsum,csum)];
			while(ris.size()&&cis.size()){
				int ri=ris.back(); ris.pop_back();
				int ci=cis.back(); cis.pop_back();
				b[ri][ci]=max(rsum,csum);
				ris2.push_back(ri);
				cis2.push_back(ci);
			}
			if(ris.empty()) rq.erase(begin(rq));
			if(cis.empty()) cq.erase(begin(cq));
		}
		// +,+
		for(;;){
			auto& [rsum,ris]=*rbegin(rq);
			auto& [csum,cis]=*rbegin(cq);
			if(!(rsum>0&&csum>0))
				break;
			auto &ris2=rq[rsum-min(rsum,csum)],&cis2=cq[csum-min(rsum,csum)];
			while(ris.size()&&cis.size()){
				int ri=ris.back(); ris.pop_back();
				int ci=cis.back(); cis.pop_back();
				b[ri][ci]=min(rsum,csum);
				ris2.push_back(ri);
				cis2.push_back(ci);
			}
			if(ris.empty()) rq.erase(prev(end(rq)));
			if(cis.empty()) cq.erase(prev(end(cq)));
		}

		while(begin(rq)->first<0){
			assert(cq.size()==1);
			auto& [rsum1,ris1]=*begin(rq);
			auto& [rsum2,ris2]=*rbegin(rq);
			ll x=min(-rsum1,rsum2);
			auto &ris3=rq[rsum1+x],&ris4=rq[rsum2-x];
			int ci=begin(cq)->second[0];
			while(ris1.size()&&ris2.size()){
				int ri1=ris1.back(); ris1.pop_back();
				int ri2=ris2.back(); ris2.pop_back();
				b[ri1][ci]-=x;
				b[ri2][ci]+=x;
				ris3.push_back(ri1);
				ris4.push_back(ri2);
			}
			if(ris1.empty()) rq.erase(begin(rq));
			if(ris2.empty()) rq.erase(prev(end(rq)));
		}

		while(begin(cq)->first<0){
			assert(rq.size()==1);
			auto& [csum1,cis1]=*begin(cq);
			auto& [csum2,cis2]=*rbegin(cq);
			ll x=min(-csum1,csum2);
			auto &cis3=cq[csum1+x],&cis4=cq[csum2-x];
			int ri=begin(rq)->second[0];
			while(cis1.size()&&cis2.size()){
				int ci1=cis1.back(); cis1.pop_back();
				int ci2=cis2.back(); cis2.pop_back();
				b[ri][ci1]-=x;
				b[ri][ci2]+=x;
				cis3.push_back(ci1);
				cis4.push_back(ci2);
			}
			if(cis1.empty()) cq.erase(begin(cq));
			if(cis2.empty()) cq.erase(prev(end(cq)));
		}

		rep(i,h) rep(j,w) if((i+j)%2)
			b[i][j]=-b[i][j];

		cout<<res<<endl;
		rep(i,h) rep(j,w)
			cout<<b[i][j]<<"\n "[j+1<w];
	}
}
