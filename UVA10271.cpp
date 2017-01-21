#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int dp[1001][5001];
//dp[i][j]=min(dp[i][j-1],dp[i-1][j-2]+l(j,j-1)) (j-2)-(i-1)*3>=1 => j>=3i
int main(){
	int T,K,N,L[6000];
	cin>>T;
	for(int t=0;t<T;t++){
		cin>>K>>N;
		K=K+8;
		for(int i=1;i<=N;i++)
			cin>>L[i];
		sort(L+1,L+N+1,greater<int>());
		memset(dp,1000000,sizeof(dp));
		for(int j=1;j<=5000;j++)
			dp[0][j]=0;
		for(int i=1;i<=K;i++){
			for(int j=3*i;j<=N;j++)
				dp[i][j]=min(dp[i][j-1],dp[i-1][j-2]+(L[j]-L[j-1])*(L[j]-L[j-1]));
		}
		cout<<dp[K][N]<<endl;
	}
}