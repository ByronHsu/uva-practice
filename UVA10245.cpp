#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
struct point{
	double x,y;
};
bool cmp(point,point);
double distance(point,point);
double divide(int,int);
double cross(int,int,int,double);
int N;
point p[10000];
int main(){
	while(cin>>N&&N!=0){
		for(int i=0;i<N;i++)
			cin>>p[i].x>>p[i].y;
		sort(p,p+N,cmp);
		double d=divide(0,N-1);
		if(d>=10000){
			cout<<"INFINITY"<<endl;
			continue;
		}
		printf("%.4lf\n",d);
	}
}

bool cmp(point a,point b){
	return a.x<b.x;
}
double distance(point a,point b){
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
double divide(int index1,int index2){
	if(index2-index1==1)
		return distance(p[index1],p[index2]);
	if(index2==index1)
		return 10000000;
	int mid=(index1+index2)/2;
	double left=divide(index1,mid);
	double right=divide(mid+1,index2);
	double middle=cross(index1,mid,index2,min(left,right));
	return min(min(left,right),middle);
}
double cross(int index1,int mid,int index2,double d){
	double line=(p[mid].x+p[mid+1].x)/2;
	vector<point> L,R;
	for(int i=mid;i>=index1;i--){
		if(line-p[i].x<=d)
			L.push_back(p[i]);
		else
			break;
	}
	for(int i=mid+1;i<=index2;i++){
		if(p[i].x-line<=d)
			R.push_back(p[i]);
		else
			break;
	}
	double m=10000000;
	for(int i=0;i<L.size();i++){
		for(int j=0;j<R.size();j++){
			if(distance(L[i],R[j])<m)
				m=distance(L[i],R[j]);
		}
	}
	return m;
}