#include <iostream>
#include <cstring>
#include <queue>
#include <ctime>
using namespace std;
int num_of_answer;
char oterris[7][3][3][4]=
{
    {{{"aaa"},{"a.."},{"..."}},{{"..."},{"..."},{"..."}},{{"..."},{"..."},{"..."}}},
    {{{"bb."},{"b.."},{"..."}},{{"..."},{"..."},{"..."}},{{"..."},{"..."},{"..."}}},
    {{{"ccc"},{".c."},{"..."}},{{"..."},{"..."},{"..."}},{{"..."},{"..."},{"..."}}},
    {{{"d.."},{"dd."},{".d."}},{{"..."},{"..."},{"..."}},{{"..."},{"..."},{"..."}}},
    {{{"ee."},{"e.."},{"..."}},{{"e.."},{"..."},{"..."}},{{"..."},{"..."},{"..."}}},
    {{{"ff."},{"f.."},{"..."}},{{"..."},{"f.."},{"..."}},{{"..."},{"..."},{"..."}}},
    {{{"gg."},{"g.."},{"..."}},{{".g."},{"..."},{"..."}},{{"..."},{"..."},{"..."}}},
};
char type_show[7]={'a','b','c','d','e','f','g'};
char terris[7][24][3][3][4];
int num_of_type[7];
int kind_a; //輸入中a的種類
char in_map[3][3][4],dfs_map[3][3][4];
char ans[24][480][28];
//0 90 180 270
int rotation[3][4][3][3]=
{
    //繞x
    {
    {{1,0,0},
     {0,1,0},
     {0,0,1},},

    {{1,0,0},
     {0,0,1},
     {0,-1,0},},
    
    {{1,0,0},
     {0,-1,0},
     {0,0,-1},},
    
    {{1,0,0},
     {0,0,-1},
     {0,1,0},},
    },
    //繞y
    {
    {{1,0,0},
     {0,1,0},
     {0,0,1},},

    {{0,0,1},
     {0,1,0},
     {-1,0,0},},
    
    {{-1,0,0},
     {0,1,0},
     {0,0,-1},},
    
    {{0,0,-1},
     {0,1,0},
     {1,0,0},},
    },
    //繞z
    {
    {{1,0,0},
     {0,1,0},
     {0,0,1},},

    {{0,1,0},
     {-1,0,0},
     {0,0,1},},
    
    {{-1,0,0},
     {0,-1,0},
     {0,0,1},},
    
    {{0,-1,0},
     {1,0,0},
     {0,0,1},},
    }
};
int metris_mutiple_x(int rotation_type,int degree,int x,int y,int z){
    int new_x;
    new_x=rotation[rotation_type][degree][0][0]*x
         +rotation[rotation_type][degree][0][1]*y
         +rotation[rotation_type][degree][0][2]*z;
    return new_x;
}
int metris_mutiple_y(int rotation_type,int degree,int x,int y,int z){
    int new_y;
    new_y=rotation[rotation_type][degree][1][0]*x
         +rotation[rotation_type][degree][1][1]*y
         +rotation[rotation_type][degree][1][2]*z;
    return new_y;   
}
int metris_mutiple_z(int rotation_type,int degree,int x,int y,int z){
    int new_z;
    new_z=rotation[rotation_type][degree][2][0]*x
         +rotation[rotation_type][degree][2][1]*y
         +rotation[rotation_type][degree][2][2]*z;
    return new_z;  
}

void metris_rotation(int rotation_type,int terris_type,int degree,bool done){
    /*
    //debug 
    cout<<"in_rotation"<<endl;
    for(int d=0;d<3;d++){
        for(int dd=0;dd<3;dd++){
            for(int ddd=0;ddd<3;ddd++){
                cout<<terris[terris_type][num_of_type[terris_type]][d][dd][ddd];
            }
            cout<<endl;
        }
    cout<<endl;
    }
    getchar();
    //debug
    */
    //第x個點的x座標     //暫存
    int x[4],y[4],z[4],t[4],tx[4],ty[4],tz[4];
    int point_num=0;

    //z
    for(int i=0;i<3;i++)
        //y
        for(int j=0;j<3;j++)
            //x
            for(int k=0;k<3;k++){
                //如果那點是字母的話
                if(terris[terris_type][num_of_type[terris_type]][i][j][k]!='.'){
                    terris[terris_type][num_of_type[terris_type]][i][j][k]='.';
                    /*
                    cout<<"before"<<endl;
                    cout<<"x="<<k<<endl;
                    cout<<"y="<<j<<endl;
                    cout<<"z="<<i<<endl;
                    */
                    x[point_num]=metris_mutiple_x(rotation_type,degree,k,j,i);
                    y[point_num]=metris_mutiple_y(rotation_type,degree,k,j,i);
                    z[point_num]=metris_mutiple_z(rotation_type,degree,k,j,i);
                    /*
                    cout<<"after"<<endl;
                    cout<<"x="<<x[point_num]<<endl;
                    cout<<"y="<<y[point_num]<<endl;
                    cout<<"z="<<z[point_num]<<endl;
                    getchar();
                    */
                    point_num++;
                }
            }
    /*
    //debug 
    cout<<"after_rotation_set"<<endl;
    for(int d=0;d<3;d++){
        for(int dd=0;dd<3;dd++){
            for(int ddd=0;ddd<3;ddd++){
                cout<<terris[terris_type][num_of_type[terris_type]][d][dd][ddd];
            }
            cout<<endl;
        }
    cout<<endl;
    }
    getchar();
    //debug
    */
    //先確保他們都在第一象限
    for(int i=0;i<point_num;i++){
        x[i]+=100;
        y[i]+=100;
        z[i]+=100;
        tx[i]=x[i];//保存原本的
        ty[i]=y[i];
        tz[i]=z[i];
    }

    //把他移到最靠近(0,0,0)
    //先全部往-x移到不能再移 再往-y 再往-z
    for(int i=0;;i++){
        for(int j=0;j<point_num;j++){
            t[j]=tx[j]-i;
            if(t[j]<0){
                goto stop4;
            }
        }
        for(int j=0;j<point_num;j++){
            x[j]=t[j];
        }       
    }
    stop4:;
    for(int i=0;;i++){
        for(int j=0;j<point_num;j++){
            t[j]=ty[j]-i;
            if(t[j]<0){
                goto stop5;
            }
        }
        for(int j=0;j<point_num;j++){
            y[j]=t[j];
        }       
    }
    stop5:;
    for(int i=0;;i++){
        for(int j=0;j<point_num;j++){
            t[j]=tz[j]-i;
            if(t[j]<0){
                goto stop6;
            }
        }
        for(int j=0;j<point_num;j++){
            z[j]=t[j];
        }       
    }
    stop6:;


    //把做好的新立方體存進去
    for(int i=0;i<point_num;i++){
        //cout<<x[i]<<" "<<y[i]<<" "<<z[i]<<endl;
        terris[terris_type][num_of_type[terris_type]][z[i]][y[i]][x[i]]=type_show[terris_type];
    }

    if(done){
    //如果跟前面長的一樣就不要存
        bool same;
        for(int t=0;t<num_of_type[terris_type];t++){
            same=1;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    for(int k=0;k<3;k++){
                        if(terris[terris_type][t][i][j][k]!=
                            terris[terris_type][num_of_type[terris_type]][i][j][k])
                            {same=0;goto notsame;}
                    }
            if(same==1){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        for(int k=0;k<3;k++){
                            terris[terris_type][num_of_type[terris_type]][i][j][k]
                            =oterris[terris_type][i][j][k];
                        }
                    }
                }
                return;            
            }
            notsame:;
        }
        /*
        //debug
        //cout<<"after_rotation"<<endl;
        //cout<<sign<<endl;
        for(int d=0;d<3;d++){
            for(int dd=0;dd<3;dd++){
                for(int ddd=0;ddd<3;ddd++){
                    cout<<terris[terris_type][num_of_type[terris_type]][d][dd][ddd];
                }
                //cout<<endl;
            }
        //cout<<endl;
        }
        cout<<endl;
        getchar();
        //debug
        */
        num_of_type[terris_type]++;
    }
}

void make_terris(){
    //void metris_rotation(int rotation_type,int terris_type,int degree,bool done)
    //terris_type
    for(int i=0;i<7;i++){
        //繞z 0,90,180,270 繞x 90 270        
        for(int k=0;k<4;k++){
            metris_rotation(2,i,0,0);
            metris_rotation(1,i,k,1);
        }        
        for(int k=0;k<4;k++){
            metris_rotation(2,i,1,0);
            metris_rotation(1,i,k,1);
        }
        for(int k=0;k<4;k++){
            metris_rotation(2,i,2,0);
            metris_rotation(1,i,k,1);
        }
        for(int k=0;k<4;k++){
            metris_rotation(2,i,3,0);
            metris_rotation(1,i,k,1);
        }
        for(int k=0;k<4;k++){
            metris_rotation(0,i,1,0);
            metris_rotation(1,i,k,1);
        }
        for(int k=0;k<4;k++){
            metris_rotation(0,i,3,0);
            metris_rotation(1,i,k,1);        
        }
        //cout<<"type"<<i<<"="<<num_of_type[i]<<endl;
    }
}

typedef struct tpoint{
    int x,y,z;
}point;
bool cut_edge(){
    /*
    //debug
    for(int z=0;z<3;z++){
        for(int y=0;y<3;y++){
            for(int x=0;x<3;x++){
                cout<<dfs_map[z][y][x];
            }
            cout<<endl;
        }       
        cout<<endl;
    }
    getchar();
    //debug
    */
    queue<point> q;
    while(!q.empty())q.pop();
    bool bool_dfs_map[3][3][4];
    //initialize
    for(int z=0;z<3;z++)
        for(int y=0;y<3;y++)
            for(int x=0;x<3;x++){
                if(dfs_map[z][y][x]=='.')
                    bool_dfs_map[z][y][x]=0;
                else
                    bool_dfs_map[z][y][x]=1;
            }
    int isolate_num;
    int xx[6]={1,-1,0,0,0,0};
    int yy[6]={0,0,1,-1,0,0};
    int zz[6]={0,0,0,0,1,-1};
    for(int z=0;z<3;z++)
        for(int y=0;y<3;y++)
            for(int x=0;x<3;x++){
                if(!bool_dfs_map[z][y][x]){
                    /*
                    //debug
                    for(int z=0;z<3;z++){
                        for(int y=0;y<3;y++){
                            for(int x=0;x<3;x++){
                                cout<<bool_dfs_map[z][y][x];
                            }
                            cout<<endl;
                        }       
                        cout<<endl;
                    }
                    getchar();
                    //debug
                    */
                    point tpoint;
                    tpoint.x=x,tpoint.y=y,tpoint.z=z;
                    q.push(tpoint);
                    bool_dfs_map[q.front().z][q.front().y][q.front().x]=1;//將這點設為尋訪
                    isolate_num=1;
                    while(!q.empty()){
                        for(int i=0;i<6;i++){
                            //下一個點
                            point ttpoint;
                            ttpoint.x=q.front().x+xx[i];
                            ttpoint.y=q.front().y+yy[i];
                            ttpoint.z=q.front().z+zz[i];
                            //越界                                         
                            if(ttpoint.x>2||ttpoint.x<0
                                ||ttpoint.y>2||ttpoint.y<0
                                    ||ttpoint.z>2||ttpoint.z<0)
                                continue;
                            else{
                                //如果下一點沒走過
                                if(!bool_dfs_map[ttpoint.z][ttpoint.y][ttpoint.x]){
                                    //走下去
                                    q.push(ttpoint);
                                    bool_dfs_map[ttpoint.z][ttpoint.y][ttpoint.x]=1;//將這點設為尋訪
                                    isolate_num++;//封閉區塊點加一
                                }
                            }
                        }
                        q.pop();
                    }
                    /*
                    cout<<isolate_num<<endl;
                    getchar();
                    */
                    if(isolate_num%4!=0){
                        return 0;
                    }
                }
            }
    return 1;   
}
void dfs(int terris_type){

    if(terris_type==7){
        
        //cout<<"{"<<'"';
        for(int z=0;z<3;z++){
            for(int y=0;y<3;y++){
                for(int x=0;x<3;x++){
                    //printf("%c",dfs_map[z][y][x]);
                    ans[kind_a][num_of_answer][z*9+y*3+x]=dfs_map[z][y][x];
                }
                //cout<<endl;
            }       
            //cout<<endl;
        }
        //getchar();
        //cout<<'"'<<"},"<<endl;
        //cout<<endl;
        

        num_of_answer++;
        return;        
    } 

    char remember_map[3][3][4];//記得這層原本的樣子
    for(int z=0;z<3;z++)
        for(int y=0;y<3;y++)
            for(int x=0;x<3;x++){
                remember_map[z][y][x]=dfs_map[z][y][x];
            } 
    /*
    //debug
    for(int z=0;z<3;z++){
        for(int y=0;y<3;y++){
            for(int x=0;x<3;x++){
                cout<<dfs_map[z][y][x];
            }
            cout<<endl;
        }       
        cout<<endl;
    }
    getchar();
    //debug
    */
    if(terris_type==-1)
        dfs(0);
    else{
        if(terris_type==0){
            for(int z=0;z<3;z++)
                for(int y=0;y<3;y++)
                    for(int x=0;x<3;x++){
                        //判斷能否放進去
                        bool can_put=1;
                        for(int zz=0;zz<3;zz++)
                            for(int yy=0;yy<3;yy++)
                                for(int xx=0;xx<3;xx++){
                                    if(terris[0][kind_a][zz][yy][xx]=='a'){
                                        if(zz+z>2||yy+y>2||xx+x>2){
                                            can_put=0;
                                            goto cannotput;
                                        }
                                        if(dfs_map[zz+z][yy+y][xx+x]=='.'){
                                            can_put=1;
                                        }
                                        else{
                                            can_put=0;
                                            goto cannotput;
                                        }
                                    }
                                }
                        cannotput:;
                        if(!can_put) continue;//如果放不進去 迴圈走下一格

                        //如果可以
                        else{
                            //把它放進去
                            for(int zz=0;zz<3;zz++)
                                for(int yy=0;yy<3;yy++)
                                    for(int xx=0;xx<3;xx++){
                                        if(terris[0][kind_a][zz][yy][xx]=='a'){
                                            dfs_map[zz+z][yy+y][xx+x]='a';
                                        }
                                    }
                            dfs(terris_type+1); 
                            //把它設回來
                            for(int z=0;z<3;z++)
                                for(int y=0;y<3;y++)
                                    for(int x=0;x<3;x++){
                                        dfs_map[z][y][x]=remember_map[z][y][x];
                                    } 
                        }
                    }
        }
        
        else{
            for(int k=0;k<num_of_type[terris_type];k++){
                for(int z=0;z<3;z++)
                    for(int y=0;y<3;y++)
                        for(int x=0;x<3;x++){
                            //判斷能否放進去
                            bool can_put=1;
                            for(int zz=0;zz<3;zz++)
                                for(int yy=0;yy<3;yy++)
                                    for(int xx=0;xx<3;xx++){
                                        if(terris[terris_type][k][zz][yy][xx]
                                            ==type_show[terris_type]){
                                            if(zz+z>2||yy+y>2||xx+x>2){
                                                can_put=0;
                                                goto cannotput2;
                                            }
                                            if(dfs_map[zz+z][yy+y][xx+x]=='.'){
                                                can_put=1;
                                            }
                                            else{
                                                can_put=0;
                                                goto cannotput2;
                                            }
                                        }
                                    }
                            cannotput2:;
                                            
                            if(!can_put) continue;//如果放不進去 迴圈走下一格
                            //如果可以
                            else{
                                //把它放進去
                                for(int zz=0;zz<3;zz++)
                                    for(int yy=0;yy<3;yy++)
                                        for(int xx=0;xx<3;xx++){
                                            if(terris[terris_type][k][zz][yy][xx]==type_show[terris_type]){
                                                dfs_map[zz+z][yy+y][xx+x]=type_show[terris_type];
                                            }
                                        }                           
                                if(!cut_edge()){goto can_not_dfs;}
                                //遞迴下一種type
                                dfs(terris_type+1);
                                //把它設回來
                                can_not_dfs:;
                                for(int z=0;z<3;z++)
                                    for(int y=0;y<3;y++)
                                        for(int x=0;x<3;x++){
                                            dfs_map[z][y][x]=remember_map[z][y][x];
                                        } 
                            }
                        }
            }
        }       
    }
    return;
}
int main(){
    //initialize
    clock_t t1;
    memset(terris,'.',sizeof(terris));
    memset(num_of_type,0,sizeof(num_of_type));
    for(int t=0;t<7;t++){
        for(int kk=0;kk<24;kk++){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    for(int k=0;k<3;k++){
                        terris[t][kk][i][j][k]=oterris[t][i][j][k];
                    }
                }
            }
        }
    }
    make_terris();

    for(int i=0;i<24;i++){
        kind_a=i;
        num_of_answer=0;
        memset(dfs_map,'.',sizeof(dfs_map));
        dfs(-1);
    }
    //cout<<(float)(clock()-t1)/CLOCKS_PER_SEC<<endl;
    
    char gg;
    while(cin>>gg){
        clock_t t;
        t=clock();
        num_of_answer=0;
        in_map[0][0][0]=gg;
        for(int z=0;z<3;z++)
            for(int y=0;y<3;y++)
                for(int x=0;x<3;x++){
                    if(x!=0||y!=0||z!=0)
                        cin>>in_map[z][y][x];
                    dfs_map[z][y][x]='.';//初始化dfs_map
                }
        //getchar();
        //平移
        {
            int point_num=0,x[4],y[4],z[4],tx[4],ty[4],tz[4],t[4];
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    for(int k=0;k<3;k++){
                        //如果那點是字母的話
                        if(in_map[i][j][k]!='.'){
                            in_map[i][j][k]='.';
                            x[point_num]=k;
                            y[point_num]=j;
                            z[point_num]=i;
                            point_num++;
                        }
                    }
            for(int i=0;i<point_num;i++){
                x[i]+=100;
                y[i]+=100;
                z[i]+=100;
                tx[i]=x[i];//保存原本的
                ty[i]=y[i];
                tz[i]=z[i];
            }
            //把他移到最靠近(0,0,0)
            //先全部往-x移到不能再移 再往-y 再往-z
            for(int i=0;;i++){
                for(int j=0;j<point_num;j++){
                    t[j]=tx[j]-i;
                    if(t[j]<0){
                        goto stop4;
                    }
                }
                for(int j=0;j<point_num;j++){
                    x[j]=t[j];
                }       
            }
            stop4:;
            for(int i=0;;i++){
                for(int j=0;j<point_num;j++){
                    t[j]=ty[j]-i;
                    if(t[j]<0){
                        goto stop5;
                    }
                }
                for(int j=0;j<point_num;j++){
                    y[j]=t[j];
                }       
            }
            stop5:;
            for(int i=0;;i++){
                for(int j=0;j<point_num;j++){
                    t[j]=tz[j]-i;
                    if(t[j]<0){
                        goto stop6;
                    }
                }
                for(int j=0;j<point_num;j++){
                    z[j]=t[j];
                }       
            }
            stop6:;
           //把做好的新立方體存進去
            for(int i=0;i<point_num;i++){
                //cout<<x[i]<<" "<<y[i]<<" "<<z[i]<<endl;
                in_map[z[i]][y[i]][x[i]]=type_show[0];
            }
        }
        //判斷a種類
        {
            for(int k=0;k<24;k++){
                for(int z=0;z<3;z++)
                    for(int y=0;y<3;y++)
                        for(int x=0;x<3;x++){
                            if(terris[0][k][z][y][x]!=in_map[z][y][x]){
                                goto notsame;
                            }
                        }
                kind_a=k;break;
                notsame:;
            }
        }

        for(int i=0;i<480;i++){
            for(int k=0;k<27;k++){
                cout<<ans[kind_a][i][k];
            }
        cout<<endl;
        }
        cout<<endl;
        //dfs(-1);

        //cout<<(float)(clock()-t)/CLOCKS_PER_SEC<<endl;
        //cout<<num_of_answer<<endl;
    }

}