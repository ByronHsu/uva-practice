#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int main(){
	int n,a[100000];
	queue<int> q1,q2;
	while(cin>>n&&n!=0){
		for(int i=0;i<n;i++)
			cin>>a[i];
		sort(a,a+n);
		while(!q1.empty())
			q1.pop();
		while(!q2.empty())
			q2.pop();
		for(int i=0;i<n;i++){
			q1.push(a[i]);
		}
		int sum=0;
		for(int i=1;i<=n-1;i++){
			int m=0;
			for(int j=0;j<2;j++){
				if(q1.empty()){
					m+=q2.front();
					q2.pop();
					continue;
				}
				if(q2.empty()){
					m+=q1.front();
					q1.pop();
					continue;					
				}
				if(q1.front()<q2.front()){
					m+=q1.front();
					q1.pop();
					continue;
				}
				if(q2.front()<=q1.front()){
					m+=q2.front();
					q2.pop();
					continue;
				}
			}
			q2.push(m);
			sum+=m;
		}
		cout<<sum<<endl;
	}
}
