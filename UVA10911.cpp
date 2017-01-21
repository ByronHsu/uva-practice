#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
struct point{
	double x,y;
};
double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main(){
	int N,index=0;;
	point p[20];
	string s;
	double dp[100000];
	while(cin>>N&&N!=0){
		index++;
		N=N*2;
		for(int i=0;i<N;i++)
			cin>>s>>p[i].x>>p[i].y;
		for(int i=0;i<100000;i++)
			dp[i]=10000000;
		dp[0]=0;
		for(int i=0;i<N;i++){
			dp[1<<i]=0;
		}
		for(int i=1;i<(1<<N);i++){
			int left,right;
			for(left=N-1;left>=0;left--){
				if(i&(1<<left))break;
			}
			for(right=0;right<left;right++){
				dp[i]=min(dp[i],dp[(i^(1<<left))^(1<<right)]+dis(p[left],p[right]));
			}
			//cout<<"dp["<<i<<"]="<<dp[i]<<endl;
		}
		printf("Case %d: %.2lf\n",index,dp[(1<<N)-1]);
	}
}