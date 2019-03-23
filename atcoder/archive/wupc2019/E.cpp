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

struct SegmentTree{
	using T=int;
	const T data_unit=INF;
	T Merge(T a,T b){
		return min(a,b);
	}
	T Apply(T x,T){
		return x;
	}
	int NextPow2(int n){
		n--;
		for(int i=1;i<32;i*=2) n|=n>>i;
		return n+1;
	}

	int size;
	vector<T> data;
	SegmentTree(int n):size(NextPow2(n)),data(2*size,data_unit){}
	SegmentTree(const vector<T>& a):size(NextPow2(a.size())),data(2*size,data_unit){
		copy(all(a),begin(data)+size);
		peri(i,1,size) data[i]=Merge(data[i*2],data[i*2+1]);
	}
	void PointUpdate(int i,T x){
		data[size+i]=Apply(x,data[size+i]);
		for(i+=size;i/=2;) data[i]=Merge(data[i*2],data[i*2+1]);
	}
	T RangeQuery(int a,int b,int i,int l,int r){
		if(b<=l||r<=a) return data_unit;
		if(a<=l&&r<=b) return data[i];
		return Merge(RangeQuery(a,b,i*2,l,(l+r)/2),RangeQuery(a,b,i*2+1,(l+r)/2,r));
	}
	T RangeQuery(int a,int b){return RangeQuery(a,b,1,0,size);}
};

// [0,i),[i,n)がともに回文であるならtrue
bool ok(int n,SegmentTree& st,vi& rank,int i)
{
	if(i>0){
		if(i%2==0){
			int c=i/2;
			int x=rank[c],y=rank[2*n-(c-1)];
			int len=st.RangeQuery(min(x,y)+1,max(x,y)+1);
			if(2*len<i) return false;
		}
		else{
			int c=i/2;
			int x=rank[c],y=rank[2*n-c];
			int len=st.RangeQuery(min(x,y)+1,max(x,y)+1);
			if(2*len-1<i) return false;
		}
	}

	if(n-i>0){
		if((n-i)%2==0){
			int c=i+(n-i)/2;
			int x=rank[c],y=rank[2*n-(c-1)];
			int len=st.RangeQuery(min(x,y)+1,max(x,y)+1);
			if(2*len<n-i) return false;
		}
		else{
			int c=i+(n-i)/2;
			int x=rank[c],y=rank[2*n-c];
			int len=st.RangeQuery(min(x,y)+1,max(x,y)+1);
			if(2*len-1<(n-i)) return false;
		}
	}

	return true;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int h,w;cin>>h>>w&&h|w;){
		vs grid(h);
		rep(i,h) cin>>grid[i];

		vi rsum(h),csum(w);
		rep(i,h) rep(j,w){
			rsum[i]+=grid[i][j]-'0';
			csum[j]+=grid[i][j]-'0';
		}
		vi rsa(h*2+1),csa(w*2+1),rlcp(h*2+1),clcp(w*2+1);
		{
			vi rs(h*2+1+3);
			rep(i,h) rs[i]=rs[2*h-i]=rsum[i]+100;
			rs[h]=1;
		  KaerkkaeinenSanders(rs,rsa,w+100);
		  LCP(rs,rsa,rlcp);
		}
		{
			vi cs(w*2+1+3);
			rep(i,w) cs[i]=cs[2*w-i]=csum[i]+100;
			cs[w]=1;
		  KaerkkaeinenSanders(cs,csa,h+100);
		  LCP(cs,csa,clcp);
		}

		vi rrank(h*2+1),crank(w*2+1);
		rep(i,h*2+1) rrank[rsa[i]]=i;
		rep(i,w*2+1) crank[csa[i]]=i;
		SegmentTree rst(rlcp),cst(clcp);

		int res=0;
		repi(i,1,h) repi(j,1,w)
			res+=ok(h,rst,rrank,i)&&ok(w,cst,crank,j);
		cout<<res<<endl;
	}
}
