#include <bits/stdc++.h>
using namespace std;

string to_sequence(int n)
{
	string res;
	for(int i=32;i--;)
		if(n>>i)
			res+="01"[n>>i&1];
	return res;
}

int interpret(const string& s,int base)
{
	int res=0;
	for(int i=0;i<s.size();i++)
		res=res*base+s[i]-'0';
	return res;
}

int get_factor(const string& seq,int base,const vector<int>& primes)
{
	for(int p:primes){
		int x=0;
		for(int i=0;i<seq.size();i++)
			x=(x*base+seq[i]-'0')%p;
		if(x==0)
			return p;
	}
	return -1;
}

int main()
{
	vector<int> primes(10000);
	{
		for(int i=2;i<primes.size();i++) primes[i]=i;
		for(int i=2;i*i<primes.size();i++) if(primes[i])
			for(int j=i*i;j<primes.size();j+=i)
				primes[j]=0;
		primes.erase(remove(begin(primes),end(primes),0),end(primes));
	}
	
	int T; cin>>T;
	for(int _case=1;_case<=T;_case++){
		int n,j; cin>>n>>j;
		
		vector<tuple<string,vector<int>>> res;
		for(int i=0;i<(1<<(n-2));i++){
			string seq=to_sequence((1<<(n-1))+i*2+1);
			vector<int> factors;
			for(int base=2;base<=10;base++)
				factors.push_back(get_factor(seq,base,primes));
			if(count(begin(factors),end(factors),-1)==0){
				res.emplace_back(seq,factors);
				if(res.size()==j) break;
			}
		}
		cout<<"Case #"<<_case<<":"<<endl;
		for(int i=0;i<res.size();i++){
			string s; vector<int> fs; tie(s,fs)=res[i];
			cout<<s;
			for(int f:fs) cout<<' '<<f;
			cout<<endl;
		}
	}
}
