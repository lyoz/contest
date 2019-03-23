#include <bits/stdc++.h>
using namespace std;

bool solve(vector<int> a)
{
	int mn=*min_element(begin(a),end(a)),mx=*max_element(begin(a),end(a));
	if(mn<(mx+1)/2)
		return false;
	for(int x=mn+1;x<=mx;x++)
		if(count(begin(a),end(a),x)<2)
			return false;
	if(mx&1)
		return count(begin(a),end(a),mn)==2;
	else
		return count(begin(a),end(a),mn)==1;
}

int main()
{
	for(int n;cin>>n && n;){
		vector<int> a(n);
		for(int& x:a) cin>>x;
		cout<<(solve(a)?"Possible":"Impossible")<<endl;
	}
}
