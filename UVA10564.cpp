#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
//dp[i][j][k]=dp[i+1][j][k-v[i][j]]+dp[i+1][j-1][k-v[i][j]]
long long int N,S,v[100][100],dp[100][100][500],ans,pathnum,path[100][100];
bool p[100][100][500][2];//0 left 1 right
int main(){
	while(cin>>N>>S&&(N!=0||S!=0)){
		ans=0,pathnum=0;
		for(long long int i=0;i<100;i++)
			for(long long int j=0;j<100;j++)
				v[i][j]=-1;
		for(long long int i=1;i<=N;i++){
			for(long long int j=1;j<=N-i+1;j++)
				cin>>v[i][j];
		}
		for(long long int i=N+1;i<=2*N-1;i++){
			for(long long int j=1;j<=i-N+1;j++){
				cin>>v[i][j];
			}
		}
		for(long long int i=0;i<100;i++)
			for(long long int j=0;j<100;j++)
				for(long long int k=0;k<500;k++)
					dp[i][j][k]=0,p[i][j][k][0]=0,p[i][j][k][1]=0;
		for(long long int j=1;j<=N;j++)
			dp[2*N-1][j][v[2*N-1][j]]=1;

		for(long long int i=2*N-2;i>=N;i--){
			for(long long int j=1;j<=i-N+1;j++){
				for(long long int k=0;k<500;k++){
					if(v[i+1][j]!=-1&&k-v[i][j]>=0&&dp[i+1][j][k-v[i][j]]){
						p[i][j][k][0]=1;
						dp[i][j][k]+=dp[i+1][j][k-v[i][j]];
					}
					if(v[i+1][j+1]!=-1&&k-v[i][j]>=0&&dp[i+1][j+1][k-v[i][j]]){
						p[i][j][k][1]=1;
						dp[i][j][k]+=dp[i+1][j+1][k-v[i][j]];
					}
					//if(dp[i][j][k])
					//prlong long intf("dp[%d][%d][%d]=%d\n",i,j,k,dp[i][j][k]);				
				}
			}
		}	

		for(long long int i=N-1;i>=1;i--){
			for(long long int j=1;j<=N-i+1;j++){
				for(long long int k=0;k<500;k++){
					if(v[i+1][j]!=-1&&k-v[i][j]>=0&&dp[i+1][j][k-v[i][j]]){
						p[i][j][k][1]=1;
						dp[i][j][k]+=dp[i+1][j][k-v[i][j]];
					}
					if(j-1>=1&&v[i+1][j-1]!=-1&&k-v[i][j]>=0&&dp[i+1][j-1][k-v[i][j]]){
						p[i][j][k][0]=1;
						dp[i][j][k]+=dp[i+1][j-1][k-v[i][j]];
					}
					//if(dp[i][j][k])
					//prlong long intf("dp[%d][%d][%d]=%d\n",i,j,k,dp[i][j][k]);
				}
			}
		}	
		for(long long int j=1;j<=N;j++){
			ans+=dp[1][j][S];
		}
		cout<<ans<<endl;
		if(!ans){
			cout<<endl;
		}
		if(ans){
			long long int now;
			for(now=1;now<=N;now++){
				if(dp[1][now][S])
					{cout<<now-1<<" ";break;}
			}
			for(long long int i=1;i<=2*N-2;i++){
				if(i<N){
					if(p[i][now][S][0]){
						cout<<"L";
						S=S-v[i][now];
						now=now-1;
						continue;
					}
					if(p[i][now][S][1]){
						cout<<"R";
						S=S-v[i][now];
						now=now;
						continue;
					}
				}
				if(i>=N){
					if(p[i][now][S][0]){
						cout<<"L";
						S=S-v[i][now];
						now=now;
						continue;
					}
					if(p[i][now][S][1]){
						cout<<"R";
						S=S-v[i][now];
						now=now+1;
						continue;
					}
				}
			}
			cout<<endl;
		}
	}
}