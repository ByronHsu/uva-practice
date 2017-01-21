#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int dp[300][300];
int main(){
	int n,L[300];
	while(cin>>n){
		for(int i=0;i<300;i++)
			for(int j=0;j<300;j++)
				dp[i][j]=10000000;
		for(int i=1;i<=n;i++){
			cin>>L[i];
			dp[i][i]=0;
		}
		for(int j=2;j<=n;j++){
			for(int i=j-1;i>=1;i--){
				int sum=0;
				for(int index=i;index<=j;index++){
					sum+=L[index];
				}
				dp[i][j]=min(dp[i][j],L[i]*0+dp[i+1][j]+sum-L[i]);
				dp[i][j]=min(dp[i][j],L[j]*0+dp[i][j-1]+sum-L[j]);
				for(int k=i+1;k<=j-1;k++){
					dp[i][j]=min(dp[i][j],dp[i][k-1]+L[k]*0+dp[k+1][j]+sum-L[k]);
				}
				//printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
			}
		}
		cout<<dp[1][n]<<endl;

	}
}