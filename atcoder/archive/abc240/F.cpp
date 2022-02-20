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

	for(int tc;cin>>tc&&tc;){
		rep(_,tc){
			int n,m; cin>>n>>m;
			vl xs(n),ys(n);
			rep(i,n) cin>>xs[i]>>ys[i];

			vl is={-1},bs={0};
			rep(i,n){
				ll iback=is.back(),bback=bs.back();
				if(xs[i]<0){
					// xs[i]を何回足したら負になるか
					int lo=0,hi=ys[i]+1;
					while(lo<hi){
						int mi=(lo+hi)/2;
						ll z=bs.back()+xs[i]*mi;
						if(z<0)
							hi=mi;
						else
							lo=mi+1;
					}
					if(1<lo&&lo<=ys[i]){
						is.push_back(iback+(lo-1));
						bs.push_back(iback+(lo-1)*xs[i]);
					}
				}
				is.push_back(iback+ys[i]);
				bs.push_back(bback+ys[i]*xs[i]);
			}

			ll res=xs[0],asum=0,bsum=0;
			for(int i=0,j=1,k=0;j<is.size();j++){
				for(;k<n;k++){
					if(i<=is[j]&&is[j]<i+ys[k])
						break;
          i+=ys[k];
					asum+=bsum*ys[k]+xs[k]*ys[k]*(ys[k]+1)/2;
					bsum+=xs[k]*ys[k];
				}
				ll cnt=is[j]-i+1;
				ll add=bsum*cnt+xs[k]*cnt*(cnt+1)/2;
				chmax(res,asum+add);
			}
			cout<<res<<endl;
		}
	}
}
