/*
想法：
N*L=sum
先記錄傳進來的木棍的最大值(m)
當L>=m時進行遞迴
將木棍由大到小排列排列
開一個陣列記錄哪些數字不需要再跑
跑過的數字如果失敗就不要再跑
還有兩個重要剪支
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional> 
#include <cstring>  
using namespace std;
int stick[105],num,stick_set,L;
bool used[105];
					//有幾組
int  cmp( const int  &a,  const int  &b){    
    return  a > b;  
}  
bool dfs(int length,int index,int set){
	/*
	if(L==77&&length==77){	
	for(int i=0;i<num;i++){
		if(used[i])
			cout<<'{'<<stick[i]<<'}'<<" ";
		else
			cout<<stick[i]<<" ";
	}
	cout<<endl;
	getchar();
	}*/
	bool dfs_used[100];
	memset(dfs_used,0,sizeof(dfs_used));//初始化“dfs中不該再走”這個陣列
	if(set==stick_set)
		return true;
	for(int i=index+1;i<num;i++){
		//如果這個元素沒用過
		if(!used[i]&&!dfs_used[stick[i]]){
			if(length-stick[i]==0){
				used[i]=1;
				if(dfs(L,-1,set+1))
					return true;
				else{
					dfs_used[stick[i]]=1;
					used[i]=0;
					return false;
				}	
			}
			if(length-stick[i]>0){
				used[i]=1;
				if(dfs(length-stick[i],i,set))
					return true;
				else{
					dfs_used[stick[i]]=1;
					used[i]=0;
					if(length==L)
						return false;
				}

			}
		}
	}
	return false;
}
int main(){
	while(cin>>num){
		if(!num){break;}
		int stick_max=0,sum=0;
		for(int i=0;i<num;i++){
			cin>>stick[i];
			sum+=stick[i];
			if(stick[i]>stick_max)
				stick_max=stick[i];
		}
		//cout<<endl;
		sort(stick,stick+num, cmp);//由大到小排序
		//getchar();
		/*
		for(int i=0;i<num;i++){
			cout<<stick[i]<<" ";
		}
		cout<<endl;
		getchar();
		*/
		for(L=stick_max;L<=sum;L++){
			if(sum%L==0){
				stick_set=sum/L;//要有幾組
				memset(used,0,sizeof(used));//初始化“dfs中是否用過”這個陣列
				if(dfs(L,-1,0)){
					cout<<L<<endl;
					break;
				}
			}
		}
	}
}