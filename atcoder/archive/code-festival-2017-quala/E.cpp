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
constexpr int MOD=998244353;
constexpr double EPS=1e-9;

template<uint M>
struct modint{
	uint val;
	modint(uint x=0):val((x%M+M)%M){}
	modint pow(uint r)const{
		ll a=val,x=1;
		for(;r;r>>=1){
			if(r&1)
				(x*=a)%=M;
			(a*=a)%=M;
		}
		return x;
	}
	modint inv()const{
		ll x=1;
		for(ll a=val,b=M,u=0;b;){
			ll t=a/b;
			swap(a-=b*t,b);
			swap(x-=u*t,u);
		}
		return (x+M)%M;
	}
	modint& operator=(const modint& x)&{val=x.val; return *this;}
	modint& operator+=(const modint& x)&{if((val+=x.val)>=M) val-=M; return *this;}
	modint& operator-=(const modint& x)&{if((val+=M-x.val)>=M) val-=M; return *this;}
	modint& operator*=(const modint& x)&{val=(ll)val*x.val%M; return *this;}
	modint& operator/=(const modint& x)&{val=(ll)val*x.inv().val%M; return *this;}
};

template<uint M> bool operator==(const modint<M>& a,const modint<M>& b){return a.val==b.val;}
template<uint M> bool operator!=(const modint<M>& a,const modint<M>& b){return a.val!=b.val;}
template<uint M> modint<M> operator+(modint<M> a,const modint<M>& b){a+=b; return a;}
template<uint M> modint<M> operator-(modint<M> a,const modint<M>& b){a-=b; return a;}
template<uint M> modint<M> operator*(modint<M> a,const modint<M>& b){a*=b; return a;}
template<uint M> modint<M> operator/(modint<M> a,const modint<M>& b){a/=b; return a;}
template<uint M> ostream& operator<<(ostream& os,const modint<M>& x){return os<<x.val;}

using mint=modint<MOD>;

int fact[300001],ifact[300001];
int ncr(int n,int r)
{
	return (ll)fact[n]*ifact[n-r]%MOD*ifact[r]%MOD;
}

vector<mint> calc(const vi& ls,const vi& ts,const vi& bs)
{
	vi js=ts; js.insert(js.end(),all(bs));
	sort(all(js)); js.erase(unique(all(js)),end(js));

	vector<mint> cs;
	int ln=ls.size();
	for(int j:js){
		int tn=lower_bound(all(ts),j)-begin(ts),bn=lower_bound(all(bs),j)-begin(bs);
		if(ln==0){
			if(tn+bn==0)
				cs.push_back(1);
			else
				cs.push_back(0);
		}
		else{
			cs.push_back(ncr(ln-1+tn+bn,tn+bn));
		}
	}
	return cs;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	fact[0]=ifact[0]=1;
	repi(i,1,300001){
		fact[i]=(ll)fact[i-1]*i%MOD;
		ifact[i]=mint(fact[i]).inv().val;
	}

	for(int h,w;cin>>h>>w&&h|w;){
		string a,b,c,d; cin>>a>>b>>c>>d;

		if(a==string(h,'0')&&b==string(h,'0')&&c==string(w,'0')&&d==string(w,'0')){
			cout<<1<<endl;
			continue;
		}

		mint res;
		rep(_,2){
			vi ls,rs,ts,bs;
			rep(i,h) if(a[i]=='1') ls.push_back(i);
			rep(i,h) if(b[i]=='1') rs.push_back(i);
			rep(i,w) if(c[i]=='1') ts.push_back(i);
			rep(i,w) if(d[i]=='1') bs.push_back(i);

			vi js=ts; js.insert(js.end(),all(bs));
			sort(all(js)); js.erase(unique(all(js)),end(js));

			vi two(w+1);
			rep(i,w) two[i+1]=two[i]+(c[i]=='1'&&d[i]=='1');

			vector<mint> dpl(js.size());
			{
				vector<mint> cs=calc(ls,ts,bs);
				mint prev=0;
				rep(i,js.size()){
					int j=js[i];
					dpl[i]=prev+cs[i]*mint(2).pow(two[w]-two[j]);
					prev=dpl[i];
				}
			}
			{
				vi ts2(rbegin(ts),rend(ts)),bs2(rbegin(bs),rend(bs));
				for(int& j:ts2) j=w-1-j;
				for(int& j:bs2) j=w-1-j;
				vector<mint> cs=calc(rs,ts2,bs2);
				reverse(all(cs));
				rep(i,js.size()){
					int j=js[i];
					res+=dpl[i]*cs[i]/mint(2).pow(two[w]-two[j+1]);
				}
			}
			tie(h,w,a,b,c,d)=mt(w,h,c,d,a,b);
		}
		cout<<res<<endl;
	}
}
