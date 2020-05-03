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

	for(ll d,l,n;cin>>d>>l>>n&&d|l|n;){
		vl cs(d);
		rep(i,d) cin>>cs[i];
		vl ks(n),fs(n),ts(n);
		rep(i,n){
			cin>>ks[i]>>fs[i]>>ts[i];
			fs[i]--;
		}
		//dump(d,l,n);

		map<int,vl> days;
		rep(i,d)
			days[cs[i]].push_back(i);
		for(auto p:days){
			int k=p.first,day=d+p.second[0];
			days[k].push_back(day);
		}

		map<int,vl> sums;
		for(auto p:days){
			int k=p.first;
			vl day=p.second;
			vl sum(day.size());
			repi(i,1,day.size()){
				int x=day[i]-day[i-1];
				sum[i]=sum[i-1]+1+(x-1)/l;
			}
			sums[k]=sum;
		}

		//dump(days);
		//dump(sums);

		rep(i,n){
			//dump(i,ks[i],fs[i],ts[i]);
			if(days.count(ks[i])==0){
				cout<<0<<endl;
				continue;
			}
			const vl& day=days[ks[i]];
			const vl& sum=sums[ks[i]];
			//dump(day);
			//dump(sum);

			int j=lower_bound(all(day),fs[i])-begin(day);
			ll pre=day[j]-fs[i];

			ll t=ts[i]-(pre+l-1)/l; // 好みでないものを食べているぶん減らす
			//dump(pre,t);
			if(t<=0){
				cout<<0<<endl;
				continue;
			}
			int k=lower_bound(all(sum),sum[j]+t)-begin(sum);
			//dump(j,k,t);
			if(k<sum.size()){
				cout<<k-j<<endl;
				continue;
			}

			ll cnt=sum.size()-1-j;
			t-=sum.back()-sum[j];
			cnt+=t/sum.back()*(sum.size()-1);
			t%=sum.back();
			//dump(cnt,t);

			int l=lower_bound(all(sum),t)-begin(sum);
			cnt+=l;
			cout<<cnt<<endl;
		}
	}
}
