#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int w,h;//width height 2 ≤ w, h ≤ 16.
char canmap[1000][17][17]; //可能的map
char showtype[7]={'1','2','3','4','5','6','7'};//每個type的表示符號
int canmap_num;//有幾個canmap
int o[17][17];//記錄每個位置出現的o次數
int noto[17][17];
bool determinedmap[1000];
//19 kind of ships
int ship_type[7][4]={
	{0,-1,-1,-1},
	{1,2,-1,-1},
	{3,4,-1,-1},
	{5,6,7,8},
	{9,10,11,12},
	{13,14,15,16},
	{17,18,-1,-1}
};
char ship[19][5][5]={
    //type 0
    {{"xx.."},
     {"xx.."},
     {"...."},
     {"...."}},
     //type 1
    {{"xx.."},
     {".xx."},
     {"...."},
     {"...."}},
    {{".x.."},
     {"xx.."},
     {"x..."},
     {"...."}},
     //type 2
    {{".xx."},
     {"xx.."},
     {"...."},
     {"...."}},
    {{"x..."},
     {"xx.."},
     {".x.."},
     {"...."}},
     //type 3
    {{"x..."},
     {"xxx."},
     {"...."},
     {"...."}},
    {{".x.."},
     {".x.."},
     {"xx.."},
     {"...."}},
    {{"xx.."},
     {"x..."},
     {"x..."},
     {"...."}},
    {{"xxx."},
     {"..x."},
     {"...."},
     {"...."}},
     //type 4
    {{"..x."},
     {"xxx."},
     {"...."},
     {"...."}},
    {{"x..."},
     {"x..."},
     {"xx.."},
     {"...."}},
    {{"xx.."},
     {".x.."},
     {".x.."},
     {"...."}},
    {{"xxx."},
     {"x..."},
     {"...."},
     {"...."}},
     //type 5
    {{".x.."},
     {"xxx."},
     {"...."},
     {"...."}},
    {{"x..."},
     {"xx.."},
     {"x..."},
     {"...."}},
    {{"xxx."},
     {".x.."},
     {"...."},
     {"...."}},
    {{".x.."},
     {"xx.."},
     {".x.."},
     {"...."}},
     //type 6
    {{"xxxx"},
     {"...."},
     {"...."},
     {"...."}},
    {{"x..."},
     {"x..."},
     {"x..."},
     {"x..."}}
};
				//要放哪一種船
bool canmap_dfs(int type){
	/*
	//debug
	cout<<endl;
	cout<<"type="<<type<<endl;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cout<<canmap[canmap_num][i][j];
		}
		cout<<endl;
	}
	getchar();
	*/
	//全部都放上來了
	if(type==7){
		//如果檯面上還有x
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++){
				if(canmap[canmap_num][i][j]=='x')
					return 1;
			}


		//先把剩下的.改成o
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++){
				if(canmap[canmap_num][i][j]=='.')
					canmap[canmap_num][i][j]='o';
			}
		//如果這張圖跟前面某張長的一樣 就不要存
		for(int m=0;m<canmap_num;m++){
			bool same=1;
			for(int i=0;i<h;i++){
				for(int j=0;j<w;j++){
					if(canmap[canmap_num][i][j]=='o'){
						if(canmap[m][i][j]!='o'){
							same=0;
							goto byron;
						}

					}
				}
			}
			if(same){
				return 1;
			}
			byron:;
		}


		//記錄每一點有幾個o幾個非o
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++){
				if(canmap[canmap_num][i][j]=='o')
					o[i][j]++;
				else{
					noto[i][j]++;
				}
			}
		//剪枝
		//盤面上的最小o崎異點如果o>1就無法
		int nowmino=100000;
		bool havekiwi=0;
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++){
				//if it is kiwi
				if(o[i][j]>0&&noto[i][j]>0){
					havekiwi=1;
					if(o[i][j]<nowmino)
						nowmino=o[i][j];
				}
			}
		/*
		//debug	
		cout<<endl;
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				cout<<canmap[canmap_num][i][j];
			}
			cout<<endl;
		}
		getchar();
		*/
		//如果沒有崎異點 nowmino=0;
		if(!havekiwi)
			nowmino=0;
		if(nowmino>1){
			return 0;		
		}
		

	
		
		canmap_num+=1;
		//做好一個canmap惹
		return 1;




	}

	//紀錄一下原本圖長怎樣
	char remembermap[17][17];
	memset(remembermap,NULL,sizeof(remembermap));
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++){
			remembermap[i][j]=canmap[canmap_num][i][j];
		}

	//每個點都跑跑看
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++){
			//每個type又有很多種可能
			for(int k=0;k<4;k++){
				bool canput=1;
				int nowtype=ship_type[type][k];
				if(nowtype==-1)
					break;//試完了
				for(int l=0;l<4;l++){
					for(int g=0;g<4;g++){
						if(ship[nowtype][l][g]=='x'){
							//越界了
							if(l+i>h||g+j>w){
								goto stop;
							}
							if(canmap[canmap_num][l+i][g+j]=='x'||canmap[canmap_num][l+i][g+j]=='.'){
								canput=1;//可以放
							}
							else{
								canput=0;
								goto stop;//這種type不能放
							}
						}
					}
				}
				//如果可以放 把它放進去				
				if(canput){

				for(int l=0;l<4;l++){
						for(int g=0;g<4;g++){
							if(ship[nowtype][l][g]=='x'){
								if(canmap[canmap_num][l+i][g+j]=='x'||canmap[canmap_num][l+i][g+j]=='.'){
									//這點可以放
									canmap[canmap_num][l+i][g+j]=showtype[type];
								}
							}
						}
					}
				//遞迴下一種type
				if(!canmap_dfs(type+1))
					return 0;

				//dfs完把它改回來
				for(int i=0;i<h;i++)
					for(int j=0;j<w;j++){
						canmap[canmap_num][i][j]=remembermap[i][j];
					}	
				}
				stop:;
			}
		}
		return 1;
}
bool kiwidfs(){
	//search next kiwi
	bool havekiwi=0;
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++){
			//if it is kiwi
			if(o[i][j]>0&&noto[i][j]>0){
				havekiwi=1;
				//find new kiwi
				if(o[i][j]==1){

					int kiwionmap;//這個崎異點在哪張圖上
					for(int m=0;m<canmap_num;m++){
						   //圖確定的不能再用
						if(!determinedmap[m]&&canmap[m][i][j]=='o'){
							kiwionmap=m;
							break;
						}
					}
					/*
					//debug
					cout<<"kiwionmap="<<kiwionmap<<endl;
					cout<<"nowkiwi="<<i<<" "<<j<<endl;
					getchar();
					*/
					determinedmap[kiwionmap]=1;//那張map可確定
					//o noto要更新
					for(int ii=0;ii<h;ii++)
						for(int jj=0;jj<w;jj++){
							if(canmap[kiwionmap][ii][jj]=='o')
								o[ii][jj]--;
							else{
								noto[ii][jj]--;
							}
						}
					if(kiwidfs())
						return 1;
					//要改回來
					else{
						determinedmap[kiwionmap]=0;//那張map改回非確定
						//o noto要更新
						for(int ii=0;ii<h;ii++)
							for(int jj=0;jj<w;jj++){
								if(canmap[kiwionmap][ii][jj]=='o')
									o[ii][jj]++;
								else{
									noto[ii][jj]++;
								}
							}
					}					
				}
			}
		}
	//success
	if(!havekiwi){
		return 1;
	}
	return 0;
}

int main(){
	char givemap[17][17];
	int game=1;
	while(scanf("%d%d",&w,&h)==2){
		if(w==0&&h==0)
			break;
		//initialize
		canmap_num=0;
		memset(givemap,NULL,sizeof(givemap));
		memset(canmap,NULL,sizeof(canmap));
		memset(o,0,sizeof(o));
		memset(noto,0,sizeof(noto));
		memset(determinedmap,0,sizeof(determinedmap));
		//input
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++){
				cin>>givemap[i][j];
				for(int k=0;k<1000;k++){
					canmap[k][i][j]=givemap[i][j];
				}
			}
		//debug
		//getchar();
		cout<<"Game #"<<game++<<endl;
		if(!canmap_dfs(0)){
			cout<<"no."<<endl<<endl;
			continue;
		}else{
			if(kiwidfs()){
				cout<<"yes."<<endl<<endl;
				continue;
			}
			else{
				cout<<"no."<<endl<<endl;
			}
		}
	}
}