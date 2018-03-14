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

template<typename C>
void RadixSort(const vi& src,vi& dst,const C& s,int ofs,int n,int asize)
{
	vi hist(asize+1);
	rep(i,n) hist[s[ofs+src[i]]]++;
	rep(i,asize) hist[i+1]+=hist[i];
	per(i,n) dst[--hist[s[ofs+src[i]]]]=src[i];
}

bool Less(int a1,int a2,int b1,int b2)
{
	return a1!=b1?a1<b1:a2<b2;
}
bool Less(int a1,int a2,int a3,int b1,int b2,int b3)
{
	return a1!=b1?a1<b1:Less(a2,a3,b2,b3);
}

// s[0..n-1]: 入力文字列．末尾に'\0'が3つ必要(s[n]=s[n+1]=s[n+2]=0)．
// sa[0..n-1]: 接尾辞配列．
// asize: アルファベットサイズ，s[i] \in [1,asize]
template<typename C>
void KaerkkaeinenSanders(const C& s,vi& sa,int asize)
{
	int n=sa.size();
	int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
	vi s12(n02+3),sa12(n02);
	
	for(int i=0,j=0;i<n+(n0-n1);i++)
		if(i%3) s12[j++]=i;
	RadixSort(s12,sa12,s,2,n02,asize);
	RadixSort(sa12,s12,s,1,n02,asize);
	RadixSort(s12,sa12,s,0,n02,asize);
	
	int name=0,x=-1,y=-1,z=-1;
	rep(i,n02){
		int j=sa12[i];
		if(s[j]!=x || s[j+1]!=y || s[j+2]!=z)
			x=s[j],y=s[j+1],z=s[j+2],name++;
		if(j%3==1) s12[j/3]=name;
		else       s12[n0+j/3]=name;
	}
	
	if(name==n02) // unique
		rep(i,n02) sa12[s12[i]-1]=i;
	else{
		KaerkkaeinenSanders(s12,sa12,name);
		rep(i,n02) s12[sa12[i]]=i+1;
	}
	
	vi s0(n0),sa0(n0);
	for(int i=0,j=0;i<n02;i++)
		if(sa12[i]<n0) s0[j++]=3*sa12[i];
	RadixSort(s0,sa0,s,0,n0,asize);
	
	int i=0,j=n0-n1,k=0;
	while(i<n0 && j<n02){
		int p=sa0[i],q=sa12[j]<n0?sa12[j]*3+1:(sa12[j]-n0)*3+2;
		if(sa12[j]<n0?
			Less(s[p],s12[p/3],s[q],s12[n0+sa12[j]]):
			Less(s[p],s[p+1],s12[n0+p/3],s[q],s[q+1],s12[sa12[j]+1-n0]))
			sa[k++]=p,i++;
		else
			sa[k++]=q,j++;
	}
	for(;i<n0;k++,i++)
		sa[k]=sa0[i];
	for(;j<n02;k++,j++)
		sa[k]=sa12[j]<n0?sa12[j]*3+1:(sa12[j]-n0)*3+2;
}
void KaerkkaeinenSanders(const string& s,vi& sa)
{
	KaerkkaeinenSanders<string>(s+string(3,0),sa,127);
}
void KaerkkaeinenSanders(const char* s,vi& sa)
{
	KaerkkaeinenSanders<string>(s+string(3,0),sa,127);
}

// s[0..n-1] (s[n]=0), sa[0..n-1]
// lcp[0..n-1] (lcp[i]:s[sa[i-1]..]とs[sa[i]..]のLCP.lcp[0]=0)
template<typename C>
void LCP(const C& s,const vi& sa,vi& lcp)
{
	int n=sa.size();
	vi rank(n);
	rep(i,n) rank[sa[i]]=i;
	for(int i=0,h=0;i<n;i++){
		if(h>0) h--;
		if(rank[i]>0)
			for(int j=sa[rank[i]-1];;h++)
				if(s[j+h]!=s[i+h]) break;
		lcp[rank[i]]=h;
	}
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(string a,b;cin>>a>>b;){
		int m=a.size(),n=b.size();

		string s=a+'$'+b;
		vi sa(m+n+1);
		KaerkkaeinenSanders(s,sa);

		vi lcp(m+n+1);
		LCP(s,sa,lcp);

		int pre=INF;
		ll res=0;
		repi(i,1,m+n+1){
			chmin(pre,lcp[i]);
			if(sa[i]<m)  // a
				res+=m-sa[i]-lcp[i];
			else  // b
				res-=lcp[i]-exchange(pre,INF);
		}
		cout<<res<<endl;
	}
}
