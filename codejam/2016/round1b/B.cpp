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

struct Solver{
	void input();
	string solve();
	string a,b;
};

void Solver::input()
{
	a.reserve(1); cin>>a;
	b.reserve(1); cin>>b;
}

void calc_min_max(string s,vl& mn,vl& mx)
{
	int n=s.size();
	string t=s;
	replace(all(s),'?','0');
	rep(i,n) mn[i]=stoll(s.substr(n-1-i));
	replace(all(t),'?','9');
	rep(i,n) mx[i]=stoll(t.substr(n-1-i));
}

string Solver::solve()
{
	int n=a.size();
	
	vl amin(n),amax(n);
	calc_min_max(a,amin,amax);
	
	vl bmin(n),bmax(n);
	calc_min_max(b,bmin,bmax);
	
	vl ten(n,1);
	rep(i,n-1) ten[i+1]=ten[i]*10;
	
	reverse(all(a)); reverse(all(b));
	
	ll dp[20][10][10]={};
	memset(dp,0x7f,sizeof(dp));
	tuple<ll,ll> scores[20][10][10];
	
	rep(i,10) if(a[0]=='?' || a[0]=='0'+i)
		rep(j,10) if(b[0]=='?' || b[0]=='0'+j){
			dp[0][i][j]=abs(i-j);
			scores[0][i][j]=mt(i,j);
		}
	
	rep(p,n-1){
		rep(i,10) if(a[p]=='?' || a[p]=='0'+i){
			rep(j,10) if(b[p]=='?' || b[p]=='0'+j){
				rep(k,10) if(a[p+1]=='?' || a[p+1]=='0'+k){
					rep(l,10) if(b[p+1]=='?' || b[p+1]=='0'+l){
						ll& cur=dp[p+1][k][l];
						if(k==l){
							ll tmp=dp[p][i][j];
							if(cur>tmp){
								cur=tmp;
								scores[p+1][k][l]=mt(
									k*ten[p+1]+get<0>(scores[p][i][j]),
									l*ten[p+1]+get<1>(scores[p][i][j])
								);
							}
						}
						else if(k<l){
							ll tmp=(l*ten[p+1]+bmin[p])-(k*ten[p+1]+amax[p]);
							if(cur>tmp){
								cur=tmp;
								scores[p+1][k][l]=mt(
									k*ten[p+1]+amax[p],
									l*ten[p+1]+bmin[p]
								);
							}
						}
						else if(k>l){
							ll tmp=(k*ten[p+1]+amin[p])-(l*ten[p+1]+bmax[p]);
							if(cur>tmp){
								cur=tmp;
								scores[p+1][k][l]=mt(
									k*ten[p+1]+amin[p],
									l*ten[p+1]+bmax[p]
								);
							}
						}
					}
				}
			}
		}
	}
	
	ll mn=LLONG_MAX;
	tuple<ll,ll> res;
	rep(i,10) rep(j,10) if(mn>dp[n-1][i][j]){
		mn=dp[n-1][i][j];
		res=scores[n-1][i][j];
	}
	char buf[80];
	sprintf(buf,"%0*lld %0*lld",n,get<0>(res),n,get<1>(res));
	return buf;
}

int main()
{
	int T; cin>>T;
	vector<Solver> solvers(T);
	rep(i,T) solvers[i].input();
	
	vector<string> results(T);
	#pragma omp parallel for schedule(dynamic)
	rep(i,T){
		results[i]=solvers[i].solve();
		fprintf(stderr,"#%d finish\n",i+1);
	}
	
	rep(i,T) printf("Case #%d: %s\n",i+1,results[i].c_str());
}
