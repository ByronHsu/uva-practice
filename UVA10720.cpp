#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	int N;
	vector<int> v;
	while(cin>>N&&N!=0){
		v.clear();
		int a;
		for(int i=0;i<N;i++){
			cin>>a;
			v.push_back(a);
		}
		if(v.size()==1){
			if(v[0]!=0)
				cout<<"Not possible"<<endl;
			if(v[0]==0)
				cout<<"Possible"<<endl;
			continue;
		}
		while(v.size()!=1){
			sort(v.begin(),v.end(),greater<int>());
			int t=v[0];
			v.erase(v.begin());
			if(t>v.size()){
				cout<<"Not possible"<<endl;
				goto stop;
			}
			for(int i=0;i<t;i++){
				v[i]--;
				if(v[i]<0){
					cout<<"Not possible"<<endl;
					goto stop;
				}
			}
		}
		cout<<"Possible"<<endl;
		stop:;
	}
}