#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int main(){
	int l,n,L[100];
	while(cin>>l&&l!=0&&cin>>n){
		L[0]=0;
		L[n+1]=l;
		for(int i=1;i<=n;i++)
			cin>>L[i];
		int dp[1000][1001];
		for(int i=0;i<1000;i++)
			for(int j=0;j<1001;j++)
				dp[i][j]=1000000;
		for(int i=0;i<=n;i++){
			dp[L[i]][L[i+1]]=0;
		}
		for(int j=1;j<=n+1;j++){
			for(int i=j-1;i>=0;i--){
				for(int k=i+1;k<j;k++){
					int m=(dp[L[i]][L[k]]+dp[L[k]][L[j]]+L[j]-L[i]);
					if(dp[L[i]][L[j]]>m)
						dp[L[i]][L[j]]=m;
				}
			}
		}
		cout<<"The minimum cutting is "<<dp[L[0]][L[n+1]]<<"."<<endl;
	}
}