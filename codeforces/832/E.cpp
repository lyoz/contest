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

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

int main()
{
	vi inv={0,1,3,2,4};

	for(int n,m;cin>>n>>m&&n|m;){
		vvi a(m,vi(n));
		rep(i,n){
			string s; cin>>s;
			rep(j,m)
				a[j][i]=s[j]-'a';
		}

		vvi b(m,vi(m));
		rep(i,m) b[i][i]=1;

		int rank=0;
		for(int i=0,j=0;j<n;j++){
			{
				int k;
				for(k=i;k<m;k++)
					if(a[k][j])
						break;
				if(k==m)
					continue;
				swap(a[i],a[k]);
				swap(b[i],b[k]);
			}
			{
				int x=inv[a[i][j]];
				repi(l,j,n) (a[i][l]*=x)%=5;
				rep(l,m) (b[i][l]*=x)%=5;
			}
			{
				rep(k,m) if(k!=i){
					int x=a[k][j];
					repi(l,j,n) (((a[k][l]-=x*a[i][l])%=5)+=5)%=5;
					rep(l,m) (((b[k][l]-=x*b[i][l])%=5)+=5)%=5;
				}
			}
			rank=++i;
		}

		int q; cin>>q;
		rep(_,q){
			string s; cin>>s;
			vi x(m);
			rep(i,m) x[i]=s[i]-'a';
			vi y(m);
			rep(i,m) rep(j,m) (y[i]+=b[i][j]*x[j])%=5;

			int nz;
			for(nz=m;nz--;)
				if(y[nz])
					break;

			if(nz<rank)
				cout<<ModPow(5,n-rank,MOD)<<endl;
			else
				cout<<0<<endl;
		}
	}
}
