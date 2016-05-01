#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T; cin>>T;
	for(int _case=1;_case<=T;_case++){
		cout<<"Case #"<<_case<<": ";
		int n; cin>>n;
		if(n==0){
			cout<<"INSOMNIA"<<endl;
			continue;
		}
		set<int> s;
		for(int i=0;i<10;i++)
			s.insert(i);
		for(int i=1;;i++){
			for(long long x=i*n;x;x/=10)
				s.erase(x%10);
			if(s.empty()){
				cout<<(long long)i*n<<endl;
				break;
			}
		}
	}
}
