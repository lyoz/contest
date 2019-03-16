#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(int n;cin>>n && n;){
		vector<int> a(n);
		for(int& x:a) cin>>x;

		vector<int> b=a;
		sort(begin(b),end(b));

		int res=0;
		for(int i=0;i<n;i++){
			int j=lower_bound(begin(b),end(b),a[i])-begin(b);
			res+=i&1^j&1;
		}

		cout<<res/2<<endl;
	}
}
