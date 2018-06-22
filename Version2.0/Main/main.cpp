#define MaxVnum 60
#define Max 40
#include<bits/stdc++.h>
#include <iostream>
#include <ostream>
#include<fstream>
#include<conio.h>
#include <string>
#include "tinyxml.h"
#include "tinystr.h"
#include <QApplication>
#include <QStringListModel>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QLineEdit>
#include <QTextEdit>
#include <windows.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 199;
int Main_n,Top_dis;
int n=52, m,ans,ttop,top;
int Bike_speed=5,Walk_speed=1,Bus_speed=15;
int Stack[99999];
int dist[maxn],path[maxn];
char c[20];
bool book[maxn];
int tu[maxn][maxn];
std::string Temp;
std::string Atrans[maxn];
int tu1[6][6] =
{
    { 0, 2, 10, 5, 3, inf },
    { inf, 0, 12, inf, inf, 10 },
    { inf, inf, 0, inf, 7, inf },
    { 2,inf, inf, 0, 2, inf },
    { 4, inf, inf, 1, 0, inf },
    { 3, inf, 1, inf, 2, 0 }
};
/*-------��·���������Ӧ��ʱ��------*/
string Cal_time(int length)
{
    int time = floor((length/Walk_speed)/60.0)+1;
    if(length%(Walk_speed*60)==0)
        time--;
    Temp ="\n��Լ����ʱ�䣺";
    Temp+="���У� ";
    sprintf(c,"%d",time);
    Temp+=c;
    Temp+="����";
    time = floor((length/Bike_speed)/60.0)+1;
    if(length%(Bike_speed*60)==0)
        time--;
    Temp+=" ���У� ";
    sprintf(c,"%d",time);
    Temp+=c;
    Temp+="����";
    Temp+=" ����: ";
    time = floor((length/Bus_speed)/60.0)+1;
    if(length%(Bus_speed*60)==0)
        time--;
    sprintf(c,"%d",time);
    Temp+=c;
    Temp+="����";
    return Temp;
}
/*-----------------End----------------*/

/*-------id��������Ӧ��ת��------*/
int Transform2(string temp)
{

    for(int i=0; i<n; i++)
    {

        if(Atrans[i]==temp)
            return i;
    }
    return 0;
}
/*-----------------End----------------*/


/*---------------K��·------------------*/
const int N=5,M=N*N,INF=1<<29;
struct Gragh
{
    int cnt,x[M],y[M],z[M],nxt[M],fst[N];
    void init()
    {
        cnt=0;
        memset(fst,0,sizeof fst);
    }
    void add(int a,int b,int c)
    {
        x[++cnt]=a,y[cnt]=b,z[cnt]=c;
        nxt[cnt]=fst[a],fst[a]=cnt;
    }
} ;
struct Path
{
    int g,f,to;
    vector <int> path;
    bool vis[N];
    bool operator < (const Path x) const
    {
        if (f==x.f)
            return g>x.g;
        return f>x.f;
    }
};

class Find_Kth
{
public:
    void spfa(int s,int e,int n,int (&dist)[N],Gragh B);
    string Get_Kth_Road(int s,int e,int k,int dist[],Gragh A);
    string Find_kth(int Graph[][N],int K,int Src,int End,int n);
};
bool cmp(Path a,Path b)
{
    if (a.f!=b.f)
        return a.f<b.f;
    int sa=a.path.size(),sb=b.path.size();
    for (int i=0; i<min(sa,sb); i++)
        if (a.path[i]!=b.path[i])
            return a.path[i]<b.path[i];
    return sa<sb;
}
void Find_Kth::spfa(int Src,int End,int n,int (&dist)[N],Gragh B)
{
    int T =End;
    bool f[N];
    int Q[N*N];
    int ttop=0;
    for (int i=1; i<=n; i++)
        dist[i]=INF;
    memset(f,0,sizeof f);
    dist[T]=0,f[T]=1;
    Q[ttop++] = T;
    while (ttop!=0)
    {
        int x=Q[ttop-1];
        ttop--;
        f[x]=0;
        for (int i=B.fst[x]; i; i=B.nxt[i])
        {
            int y=B.y[i],z=B.z[i];
            if (dist[y]>dist[x]+z)
            {
                dist[y]=dist[x]+z;
                if (!f[y])
                {
                    f[y]=1;
                    Q[ttop++] = T;
                }
            }
        }
    }

}
string Find_Kth::  Get_Kth_Road(int S,int T,int k,int dist[],Gragh A)
{
    string rel;
    rel+="·����";
    int cnt=0,y,z;
    char c[15];
    priority_queue <Path> q;
    vector <Path> ans;
    Path p,p2;
    p.path.clear();
    p2.path.clear();
    memset(p.vis,false,sizeof(p.vis));
    memset(p2.vis,false,sizeof(p2.vis));
    p.path.push_back(S),p.to=S,p.g=0,p.vis[S]=1,p.f=dist[S];
    q.push(p);
    while (!q.empty())
    {
        if (q.size()>500000)
            break;
        p=q.top();
        q.pop();
        if (p.to==T)
        {
            cnt++;
            if (cnt>k&&ans[k-1].f<p.f)
                break;
            ans.push_back(p);
        }
        for (int i=A.fst[p.to]; i; i=A.nxt[i])
        {
            y=A.y[i],z=A.z[i];
            if (p.vis[y])
                continue;
            p2=p;
            p2.to=y,p2.g=p.g+z,p2.f=p2.g+dist[y];
            p2.path.push_back(y),p2.vis[y]=1;
            q.push(p2);
        }
    }
    if ((int)ans.size()<k)
    {
        rel+="No";
        //printf("No");
        return rel;
    }
    sort(ans.begin(),ans.end(),cmp);
    for (int i=0; i<(int)ans[k-1].path.size()-1; i++)
    {
        //sprintf(c, "%d",ans[k-1].path[i]);
        //rel+=c;
        Temp = Atrans[ans[k-1].path[i]];
        rel+=Temp;
        rel+=" ";
    }

    //printf("%d-",ans[k-1].path[i]);
    // sprintf(c, "%d",ans[k-1].path[ans[k-1].path.size()-1]);
    //rel+=c;
    Temp = Atrans[ans[k-1].path[ans[k-1].path.size()-1]];
    rel+=Temp;
    //printf("%d",ans[k-1].path[ans[k-1].path.size()-1]);
    rel+="\n����:";
    sprintf(c,"%d",ans[k-1].f);
    rel+=c;
    rel+=Cal_time(ans[k-1].f);
    // cout<<rel<<endl;
    return rel;
}
string Find_Kth:: Find_kth(int Graph[][N],int K,int Src,int End,int n)

{
    Gragh A,B;
    int dist[N]= {0};
    A.init(),B.init();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(Graph[i][j]!=INF&&i!=j)
            {
                A.add(i,j,Graph[i][j]);
                B.add(i,j,Graph[i][j]);
            }
        }
    }
    spfa(Src,End,n,dist,B);
    return Get_Kth_Road(Src,End,K,dist,A);

}
/*------------------------K��·----------------------*/

/*---------------------ֱ�������·-----------------------------*/
void dijkstra(int Src,int End)
{
    memset(path,-1,sizeof(path));
    int vis[maxn]= {0};
    for(int i=0; i<n; i++)
    {
        dist[i] = tu[Src][i];
        vis[i] = 0;
    }
    vis[Src] = 1;
    dist[Src] =0;
    for(int i=1; i<n; i++)
    {
        int min_val =inf,min_id =-1;
        for(int j=0; j<n; j++)
        {
            if(!vis[j]&&dist[j]<min_val)
            {
                min_val = dist[j];
                min_id = j;
            }
        }
        if(min_val==-inf)break;
        vis[min_id] = 1;
        for(int j=0; j<n; j++)
        {
            if(dist[j]>min_val+tu[min_id][j])
            {
                path[j] = min_id;
                dist[j] = min_val+tu[min_id][j];
            }
        }
    }
    Top_dis = dist[End];
}

string dijkstra_print_path(int Src,int End)
{
    string temp;
    char c[20];
    int Stack[maxn*10];
    top=0;
    for(int i=0; i<=n; i++)
    {
        if(i==Src)continue;
        int j= i;
        while(path[j]!=-1)
        {

            Stack[top++] = j;
            j = path[j];

        }
        Stack[top++] = j;
        //printf("%d=>%d, length:%d, path: %d ",Src,i,dist[i],Src);
        sprintf(c,"%d=>%d, length:%d, path: %d ",Src,i,dist[i],Src);
        temp+=c;
        while(top!=0)       //�Ƚ����,�������
        {
            //printf("%d ",Stack[top-1]);//��ӡջ��ͷ�ڵ�
            sprintf(c,"%d ",Stack[top-1]);//��ӡջ��ͷ�ڵ�
            temp+=c;
            top--;            //��ջ��ͷ�ڵ㵯��
        }
        temp+="\n";
        //printf("\n");
    }
    return temp;
}
/*---------------------------------------------------*/

/*-----------------���Ż������·----------------------*/
struct Node
{
    int d,id;
} Heap[99999];
struct store_road
{
    int id[maxn];
    int length;
    int Vnum;
} s[maxn];
int num = 0;
void Swap(int a,int b)
{
    Node temp=Heap[a];
    Heap[a]=Heap[b];
    Heap[b]=temp;
}
void Heap_adjust(int x)
{
    int d,f=0;//��Ϊ�ж��¼���Ľڵ�������ڵ��С�ı�־
    while(x!=1&&f==0)//�߽�����
    {
        if(Heap[x/2].d>Heap[x].d)//�½ڵ�С�ڸ��ڵ��򽻻�ֵ
        {
            d=x/2;
            Swap(x,d);
        }
        else f=1;//�½ڵ���ڸ��ڵ��򲻷����ı�
        x=x/2;//����������һ�����ڵ��Ƿ�С�ڸ��½ڵ㣬������������ң�ֱ����һ�����ڵ�ֵС�ڸ��½ڵ�
    }
}
void Heap_del(int x)//��Heap[n]����Heap[1]������С���ѵ����ʣ�����Ҫ���е���
{
    int d=x,f=0;
    while(x*2<=ttop&&f==0)//�߽�����
    {
        if(Heap[x].d>Heap[x*2].d&&x*2<=ttop)
        {
            d=x*2;
        }
        if(Heap[x].d>Heap[x*2+1].d&&Heap[x*2+1].d<Heap[x*2].d&&x*2+1<=ttop)
        {
            d=x*2+1;
        }
        if(x!=d)
        {
            Swap(x,d);
            x=d;
        }
        else f=1;
    }
}
void dijkstra_opt(int Src,int End)
{
    memset(path,-1,sizeof(path));
    int vis[maxn]= {0};
    for(int i=0; i<n; i++)dist[i]=inf;
    dist[Src] =0;
    ttop  = 0;
    Node tt;
    tt.id = Src;
    tt.d = 0;
    Heap[++ttop]=tt;
    Heap_adjust(ttop);
    while(ttop)
    {
        int min_val =Heap[1].d,min_id =Heap[1].id;
        Heap[1]=Heap[ttop];//���±���С�Ľڵ�ֵ����Heap[1]�У�Ȼ��n--ɾ��Heap[n]
        ttop--;
        Heap_del(1);
        if(vis[min_id])continue;
        vis[min_id] = 1;
        for(int j=0; j<n; j++)
        {
            if(dist[j]>min_val+tu[min_id][j])
            {
                path[j] = min_id;
                dist[j] = min_val+tu[min_id][j];
                tt.id = j;
                tt.d = dist[j];
                Heap[++ttop]=tt;
                Heap_adjust(ttop);
            }
        }
    }
    Top_dis = dist[End];
}

string dijkstra_print_path_opt(int Src,int End)
{
    string temp;
    char c[20];
    int Stack[maxn*10];
    top=0;
    //for(int i=1; i<n; i++)
    for(int i=End; i<=End; i++)
    {
        int j= i;
        while(path[j]!=-1)
        {

            Stack[top++] = j;
            j = path[j];

        }
        Stack[top++] = j;

        //printf("%d=>%d, length:%d, path: ",Src,i,dist[i]);
        sprintf(c,"����:%d, path: ",dist[i]);
        temp+=c;
        while(top!=0)       //�Ƚ����,�������
        {
            //printf("%d ",Stack[top-1]);//��ӡջ��ͷ�ڵ�
            sprintf(c,"%s ",Atrans[Stack[top-1]].c_str());//��ӡջ��ͷ�ڵ�
            temp+=c;
            top--;            //���ѵ�ͷ�ڵ㵯��
        }
        //temp+="\n";
        //printf("\n");
        temp+=Cal_time(dist[i]);
    }
    return temp;
}

void road_sort(int l,int r)
{
    store_road x = s[l];
    int i = l,j = r;
    if(l <= r)
    {
        while(i < j)
        {
            while(i < j&&s[j].length > x.length)j--;
            while(i < j&&s[j].length == x.length&&s[j].Vnum > x.Vnum)j--;
            s[i] = s[j];
            while(i < j&&s[i].length < x.length)i++;
            while(i < j&&s[i].length == x.length&&s[i].Vnum <= x.Vnum)i++;
            s[j] = s[i];
        }
        s[i] = x;
        road_sort(l,i - 1);
        road_sort(i + 1,r);
    }
}
void get_all_path()
{
    for(int i=0; i<top; i++)
    {
        //printf("%d ",Stack[i]);
        s[num].id[s[num].Vnum++] = Stack[i];
    }
    for(int i = 0; i < s[num].Vnum - 1; i++)
        s[num].length += tu[s[num].id[i]][s[num].id[i + 1]];
    num++;
}
string Print_all_path()//�����Ĵ�ӡ����·��
{
    string temp;
    char c[20];
    int i,j;
    for(i = 0; i < num; i++)
    {
        //printf("length:%d, path: ",s[i].length);
        sprintf(c,"����:%d, path: ",s[i].length);
        temp+=c;
        for(j = 0; j < s[i].Vnum; j++)
            //printf("%d ",s[i].id[j]);
            sprintf(c,"%s ",Atrans[s[i].id[j]].c_str()),temp+=c;
        //printf("\n");
        //temp+="\n";
        temp+=Cal_time(s[i].length);
        temp+="\n";
        temp+="\n";
    }
    return temp;
}
void Print_all_path2()//������Ĵ�ӡ����·��
{
    for(int i=0; i<top; i++)
    {
        printf("%d ",Stack[i]);
    }
    printf("\n");
}
void AllPath(int Src,int End)
{
    if(Src==End)
    {
        //Print_all_path2();
        get_all_path();
        top--;
        return;
    }
    for(int i=0; i<n; i++)
    {
        if(tu1[Src][i]!=inf&&Src!=i&&!book[i])
        {
            Stack[top++] = i;
            book[i] = true;
            AllPath(i,End);
            book[i] = false;
        }
    }
    top--;
}
void find_all_path(int Src,int End)
{
    top =0 ;
    memset(book,false,sizeof(book));
    Stack[top++]=Src;
    book[Src] = true;
    while(top!=0)
    {
        AllPath(Src,End);
    }
}
string Init_dijkstra(int Src,int End)
{

    dijkstra_opt(Src,End);
    //��ӽڵ�0���������ڵ����̾���
    string String_path = dijkstra_print_path_opt(Src,End);
    return String_path;
    //��ӡ�ӽڵ�0���������ڵ����̾����·��;
 
}

string Init_Print_all_path(int Src,int End)//��ӡ����·�����������
{
    string temp;
    memset(s,0,sizeof(s));
    find_all_path(Src,End);//��ӡ���ڵ������·��
    road_sort(0,num - 1);
    temp = Print_all_path();
    return temp;
}
/*---------------------END---------------------------*/



/*--------------------����У԰---------------------------*/
const int MAX_CITY_SIZE = 200;//�����и���
int Graph[MAX_CITY_SIZE][MAX_CITY_SIZE];//�������
int cur_path[MAX_CITY_SIZE];//��ǰ��
int exd_path[MAX_CITY_SIZE];//��չ��

double t = 100;
const int L = 2000;

double randf() //����0��1֮������������
{
    return (float)rand()/RAND_MAX;
}

int randi(int a,int b) //����a��b֮���������� ����a<=b
{
    return rand()%(b-a+1)+a;
}

void printGraph() //��ӡ�������
{
    int i,j;
    cout<<n<<endl;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            cout<<Graph[i][j]<<" ";
        cout<<endl;
    }
}

string printPath(int *Path,int o) //��ӡ·��
{
    int i;
    string rel;
    for(i=0; i<n; i++)
    {
        if(Path[i]==o)continue;
        //sprintf(c,"%d",Path[i]);
        rel+=Atrans[Path[i]];
        rel+=" ";
        //cout<<Path[i]<<" ";
    }
    rel+="\n";
    return rel;
}

void initPath(int *path) //��ʼ�����ɽ�
{
    int i;
    for(i=0; i<n; i++)
        path[i] = i;

    for(i=0; i<n; i++)
        swap(path[i],path[randi(i,n-1)]);//������� ���Ҵ���
}

int result(int *Path) //·���ܳ���
{
    int sum=0;
    int i;
    for(i=0; i<n; i++)
    {
        sum+=Graph[Path[i]][Path[(i+1)%n]];
    }
    return sum;
}

void copyPath(int *dest,int *src) //��src·��������dest��
{
    int i;
    for(i=0; i<n; i++)
        dest[i] = src[i];
}

void reversePath(int *path) //��·����begin��end֮���·����ת begin,end�������
{
    int begin,end,len,i;
    begin = randi(0,n-1);
    end = randi(0,n-1);

    if(begin > end) swap(begin,end);
    len = end - begin + 1;
    for(i=0; i<len/2; i++)
        swap(path[begin+i],path[end-i]);
}

bool accept(int *curPath,int *exdPath) //�Ƿ�����µĽ�
{
    int curResult = result(curPath);
    int exdResult = result(exdPath);
    if(exdResult < curResult)
        return true;

    double probability = 0;
    if(t > 0.000001)		
        probability = exp((curResult - exdResult) / t);//���ܸ���
    if(probability > randf())
        return true;

    return false;
}
string TSP(string name)
{

    string rel;
    int Src;
    //cin>>Src;
    Src = Transform2(name);
    srand(time(NULL));//��ʼ�����������
    int i,j;
    ifstream infile;
    infile.open("TSP20.txt");//�������ļ�
    if(!infile)
    {
        cerr<<"error: unable to open input file: "
            << infile << endl;
        return rel;
    }
    infile>>n;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            infile>>Graph[i][j];//����������
    infile.close();
    for(int i=0; i<n; i++)Graph[Src][i] = 0 ;
    //printGraph();
    initPath(cur_path);//��ʼ����
    bool bChange;
    int s=0;
    while(s!=2)
    {
        bChange = false;
        for(i=0; i<L; i++)
        {
            copyPath(exd_path,cur_path);
            reversePath(exd_path);
            if(accept(cur_path,exd_path))
            {
                copyPath(cur_path,exd_path);
                bChange = true;
            }
        }
        t = t * 0.9;
        if(bChange == false)
            s++;
        else
            s = 0;
    }
    rel+="path:";
//	cout<<endl<<"·��:";
//	cout<<Src<<" ";
    string temp  = printPath(cur_path,Src);
    rel+=temp;
    rel+="\n���ȣ�";
    sprintf(c,"%d",result(cur_path)+2*Graph[i][Src]);
    rel+=c;
    return rel;
    //cout<<"����:"<<result(cur_path)<<endl;
    //cout<<"����:"<<result(cur_path)+dist[cur_path[0]]<<endl;
}

/*-----------------------���㹲�����ĵ��ȷ���-------------------------*/
/*����������*/
const int maxm  = 999;
typedef long long ll;

struct Bike_info
{
    int n,m;
    int num_n[maxn];
    int num_m[maxn];
    int In_id[maxn];
    int Out_id[maxn];

} info;
class BIKE
{
public:
    int  n;
    int num[maxn];//ÿ�����ִ�����г���Ŀ
    int num_pre[maxn];//ÿ����֮ǰ�����г���Ŀ
    int num_change[maxn];//ÿ����
    double num_by[maxn];//ÿ���������ֵ
    int num_shift[maxn];//ÿ����Ҫ�ƶ��ĳ�����
    int total_num;//�ܹ������г���Ŀ
    int date;//ģ������
    double Dx_pre[maxn];//��¼ǰһ�εķ���
    int state;//�޸Ĳ���ʱ������״̬��
    int Fa,Fb;
} Bike;

//��������¼
void bike_memo(int s,int e,int path[],int path_size,BIKE Bike)
{
    Bike.num[s]++;
    Bike.num[e]++;
    double One = 5;
    for(int i=0; i<path_size/2; i++)
    {
        if(One>=0)
        {
            Bike.num_by[path[i]]+=One;
            One = One-0.5;
        }
        else break;
    }
    for(int i=path_size-1; i>=path_size/2; i--)
    {
        if(One>=0)
        {
            Bike.num_by[path[i]]+=One;
            One = One-0.5;
        }
        else break;
    }
}
//int Bike_num[maxn],Bike_num_change[maxn];
double cal_Dx(int Bike_num[],int Bike_num_change[])
{
    double rel=0;
    for(int i=0; i<n; i++)
    {
        double temp = 0;
        temp = (Bike_num_change[i]-Bike_num[i])*(Bike_num_change[i]-Bike_num[i]);
        rel += temp;
    }
    rel = rel/(n*1.0);
    return rel;
}
BIKE Bike_shift_plan(BIKE Bike)
{
    double Ratio1 = Bike.Fa/(Bike.Fa+Bike.Fb);
    double Ratio2 = 1-Ratio1;
    double Ratio_deno=0;
    for(int i=0; i<n; i++)
    {
        Ratio_deno += (Ratio2*Bike.num_by[i]+Ratio1*Bike.num[i]);
    }
    for(int i=0; i<n; i++)
    {
        double temp;
        temp =  (Ratio2*Bike.num_by[i]+Ratio1*Bike.num[i])/Ratio_deno*Bike.total_num;
        Bike.num_pre[i] = Bike.num[i];
        Bike.num_change[i] = temp;
        Bike.num_shift[i] = temp - Bike.num[i];
        Bike.num[i] = temp;
    }
    //�޸Ĳ���
    Bike.Dx_pre[Bike.date++] = cal_Dx(Bike.num,Bike.num_change);
    if(Bike.state!=0)
    {
        if(Bike.date>=2&&Bike.Dx_pre[Bike.date-1]>Bike.Dx_pre[Bike.date-2])
        {
            int x = Bike.state;
            switch(x)
            {
            case 1:
                Bike.Fa--;
                break;
            case 2:
                Bike.Fb--;
                break;
            case 3:
                Bike.Fa++;
                break;
            case 4:
                Bike.Fb++;
                break;
            case 5:
                Bike.Fa--,Bike.Fb--;
                break;
            case 6:
                Bike.Fa--,Bike.Fb++;
                break;
            case 7:
                Bike.Fa++,Bike.Fb--;
                break;
            case 8:
                Bike.Fa++,Bike.Fb++;
                break;
            default:
                break;
            }

        }
        else
        {
            Bike.state = 0;
        }
    }
    else
    {
        if(Bike.date>=2&&Bike.Dx_pre[Bike.date-1]>Bike.Dx_pre[Bike.date-2])
        {
            srand(time(NULL));
            int x = rand()%8+1;
            switch(x)
            {
            case 1:
                Bike.Fa++;
                break;
            case 2:
                Bike.Fb++;
                break;
            case 3:
                Bike.Fa--;
                break;
            case 4:
                Bike.Fb--;
                break;
            case 5:
                Bike.Fa++,Bike.Fb++;
                break;
            case 6:
                Bike.Fa++,Bike.Fb--;
                break;
            case 7:
                Bike.Fa--,Bike.Fb++;
                break;
            case 8:
                Bike.Fa--,Bike.Fb--;
                break;
            default:
                break;
            }
            Bike.state = x;
        }
        else
        {
            Bike.state = 0;
        }
    }
    return Bike;
}

/*---------------��С������������·��-------------------*/
struct MaxFlow
{
    int size, n;
    int s, t, k,  maxflow, mincost;
    bool vis[maxn];
    int net[maxn], pre[maxn], cur[maxn], dis[maxn];
    std::queue <int> Q;
    int netNode,consumeNode, serverCost;
    //���
    vector<int> res[maxn];  // p�����·��
    vector<int> outFlow;  //p��·���� ��������
    int outCnt; //��¼�ж��������·��
    //for search path
    int fa[1505];
    int find_flow;
    int p_edge[1505]; //���Ӧ�ıߵı��
    int ok;
    int find_vis[1505];
    struct EDGE
    {
        int v, cap, cost, next,flow;
        EDGE() {}
        EDGE(int a, int b, int c, int d,int e)
        {
            v = a, cap = b, cost = c, next = d;
            flow = e;
        }
    } E[maxm << 1];

    void init(int _n)
    {
        n = _n, size = 0;
        memset(net, -1, sizeof(net));
    }

    void add(int u, int v, int cap, int cost)
    {
        E[size] = EDGE(v, cap, cost, net[u], 0);
        net[u] = size++;
        E[size] = EDGE(u, 0, -cost, net[v], 0);
        net[v] = size++;
    }

    bool adjust()
    {
        int v, min = inf;
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
                continue;
            for (int j = net[i];  j != -1; j = E[j].next)
            {
                v = E[j].v;
                if (E[j].cap > E[j].flow)
                    if (!vis[v] && dis[v] - dis[i] + E[j].cost < min)
                        min = dis[v] - dis[i] + E[j].cost;
            }
        }
        if (min == inf)
            return false;
        for (int i = 0; i <n; i++)
            if (vis[i])
                cur[i] = net[i], vis[i] = false, dis[i] += min;
        return true;
    }

    //������·
    int augment(int i, int flow)
    {
        if (i == t)
        {
            mincost += dis[s] * flow;
            maxflow += flow;
            return flow;
        }
        vis[i] = true;

        for (int j = cur[i], v; v = E[j].v, j != -1; j = E[j].next)
            if (E[j].cap > E[j].flow)
            {

                if (vis[v] || dis[v] + E[j].cost != dis[i]) continue;

                int delta = augment(v, std::min(flow, E[j].cap - E[j].flow));
                if (delta)
                {
                    E[j].flow += delta;
                    E[j ^ 1].flow -= delta;
                    cur[i] = j;
                    return delta;
                }
            }

        return 0;
    }


    int zkw(int _s, int _t, int need)
    {
        s = _s, t = _t;

        mincost = maxflow = 0;
        for (int i = 0; i < n; i++)
        {
            vis[i] = false;
            cur[i] = net[i];
        }

        do
        {
            while (augment(s, inf))
                memset(vis, false, sizeof(vis));
        }
        while (adjust());
        if (maxflow < need)
            return -1;
        return mincost;
    }


    //------------- for search path

    void update_flow(int minflow, int fa[])
    {
        //��s��ʼ
        int cnt = outCnt;
        // printf("cnt=%d: minflow=%d\n",cnt, minflow);
        int u=t;
        while(u!=s)
        {
            //�������£�����minflow
            //  if(p[u]==s) printf("p_edeg=%d ,s.flow=%d ",p_edge[u], edges[p_edge[u]].flow);
            //edges[p_edge[u]].flow -=minflow;
            E[p_edge[u]].flow -=minflow;
            if(u != s) res[cnt].push_back(u);
            //   if(p[u]==s) printf("^^^^ , s.flow=%d \n",edges[p_edge[u]].flow);
            u = fa[u];
        }
        outFlow.push_back(minflow);

        find_flow += minflow;
        outCnt++;
    }


    //cur��ʾ��ǰ��
    void dfs_findPath(int cur, int minflow)
    {

        if(ok) return;

        //��s��������
        if(cur == t)
        {

            //��������·�ϵ� ����
            update_flow(minflow, fa);
            ok=1;
            return ;
        }

        for (int i = net[cur], v; v = E[i].v, i != -1; i = E[i].next)
        {

            if(E[i].flow<=0) continue; //����߲�����
            if(find_vis[v]) continue;

            fa[v] = cur;
            p_edge[v] = i;
            find_vis[v] = 1;

            dfs_findPath(v, min(minflow, E[i].flow));

            find_vis[v] = 0;

            if(ok) return;

        }

    }




    void search_path()
    {

        //printf("search start\n");
        outCnt = 0;
        for(int i=0; i<1500; i++)
        {
            res[i].clear();
            outFlow.clear();
        }
        find_flow = 0;
        fa[s] = -1;
        while(find_flow< k )
        {

            // for(int i=0; i<(int)G[st].size(); i++){
            for (int i = net[s], v; v = E[i].v, i != -1; i = E[i].next)
            {
                //puts("ss");
                // printf("i=%d, e.flow =%d e.from =%d, e.to =%d\n",i, e.flow , e.flow , e.to);
                fa[v] = s;
                p_edge[v] = i;

                if(E[i].flow>0)    //��·�� ,��ʼΪ�����
                {
                    ok=0;
                    memset(find_vis, 0, sizeof(find_vis));
                    find_vis[s] = 1;
                    dfs_findPath(v, inf);
                }


            }
        }
    }

    //�������·��
    void OutputPath(string& str,int In_id[],int Out_id[])
    {
        char c[50];
        //ת��·��������
        // printf("outCnt = %d\n\n", outCnt);
        sprintf(c, "ת��·��������%d\n\n", outCnt);
        str += c;
        sprintf(c,"ת�����      ת���յ�\n");
        str+=c;
        for(int i=0; i< outCnt ; i++)
        {
            int Top = 1,SS = 1;
            for(int j= (int)res[i].size()-1 ; j>0; j--)
            {
                if(Top||j==1)
                {
                    int temp = res[i][j]>=netNode?(res[i][j]-netNode):res[i][j];
                    if(SS)
                    {
                        SS = 0;
                        sprintf(c,"%7s      ",Atrans[In_id[temp]].c_str());
                        //sprintf(c,"%5d\t",In_id[temp]);
                        str+=c;
                    }
                    else
                    {
                        if(strcmp("��ѧ����������", Atrans[Out_id[temp]].c_str())!=0){
                        sprintf(c,"%7s      ",Atrans[Out_id[temp]].c_str());
                        }else{
                            sprintf(c,"%7s",Atrans[Out_id[temp]].c_str());
                        }
                     //   sprintf(c,"%5d\t",Out_id[temp]);
                        str+=c;
                    }
//
                    Top = 0;
                }
            }
            sprintf(c,"\tת�Ƴ��������ǣ�%d\n",outFlow[i]);
            str+=c;
//            sprintf(c, "%d\n",outFlow[i]);
//            str +=c;
        }
    }
} zkw;

string Distribute_plan(Bike_info real)
{
    struct MaxFlow ob;
    int netNode,consumeNode;
    int s,t;
    int cap;
    //int from, to, cap, cost, cnt;
    string temp,str;
    //����ڵ����� ������·���� ���ѽڵ�����
    netNode=real.n ;
    consumeNode=real.m;
    //scanf("%d%d",&netNode, &consumeNode);
    ob.netNode = netNode;
    ob.consumeNode = consumeNode;
    s = netNode+consumeNode;
    t = s+1;
    ob.init(netNode+consumeNode+2);
    for(int i=0; i<netNode ; i++)
    {
        int o;
        //cin>>o;
        o=real.num_n[i];
        ob.add(s, i, o, 0);
    }
    int indx,nodeID;
    ob.k = 0;
    //���ѵ�
    for(int i=0; i<consumeNode; i++)
    {
        cap = real.num_m[i];
        // scanf("%d",&cap);
        indx = i;
        ob.k += cap;
        for(int j=0; j<netNode; j++)
        {
            //�������
            nodeID = j;
            ob.add(indx + netNode, nodeID, 9999, 0);
            ob.add(nodeID,indx + netNode, 9999, 0);
        }

        //��t��
        ob.add(indx+netNode, t, cap, 0);
    }
    int ans = ob.zkw(s, t, ob.k);
    ob.search_path();
    ob.OutputPath(str,real.In_id,real.Out_id);
    temp+=str;
    cout<<temp<<endl;
    return temp;
}
/*
�����ʽ��
ת������� ת�����Ŀ
ת����
ת���
*/
/*-------------------End------------------*/


/*-----------------��������ĳ�ʼ��--------------------*/
string info_init(BIKE Bike)
{
    //int n1,m1;�ṹ��
    //���ݴ�ӡ���䷽����
    int In[maxn],In_id[maxn];
    int Out[maxn],Out_id[maxn];
    int top1=0,top2=0;
    for(int i=0; i<Bike.n; i++)
    {
        if(Bike.num_shift[i]<0)
        {
            In_id[top1] = i;
            In[top1++] = -Bike.num_shift[i];
        }
        else if(Bike.num_shift[i]>0)
        {
            Out_id[top2] = i;
            Out[top2++] = -Bike.num_shift[i];
        }
    }

    Bike_info real;
    real.n = top1;
    real.m = top2;
    for(int i=0; i<real.n; i++)
    {
        real.num_n[i] = In[i];
        real.In_id[i] = In_id[i];
    }

    for(int i=0; i<real.m; i++)
    {
        real.num_m[i] = Out[i];
        real.Out_id[i] = Out_id[i];
    }
    return Distribute_plan(real);
}
/*---------------------End--------------------*/


/*---------------------------------------------------*/
// 3.2 Ѱ�Ҹ�������·�����㷨
string find_Bike_path(int Src,int End)
{
    string temp;
    if(Bike.num[Src]==0)
    {
        int Min = inf,Min_id=Src;
        for(int i=0; i<n; i++)
        {
            if(i==Src)continue;
            if(Bike.num[i]!=0)
            {
                if(Min>dist[i])
                {
                    Min = dist[i];
                    Min_id = i;
                }
            }
        }
        int Total_num=0;
        temp+=Init_dijkstra(Src,Min_id);
        Total_num+=Top_dis;
        temp+=Init_dijkstra(Min_id,End);
        Total_num+=Top_dis;
        temp+="�ܼ�";
        temp+=Cal_time(Total_num);
//        dijkstra(Src,Min_id);
//        temp+=dijkstra_print_path(Src,Min_id);
//        dijkstra(Min_id,End);
//        temp+=dijkstra_print_path(Min_id,End);
    }
    else
    {
//        dijkstra(Src,End);
//        temp+=dijkstra_print_path(Src,End);
        temp+=Init_dijkstra(Src,End);
    }
    return temp;
}
/*---------------------------------------------------*/


/*------------�������Ƶ�����·���------------------*/
struct re_vector
{
    int Size,top;
    int length;
    int data[maxn<<4];
};
re_vector dijkstra_print_path2(int s,int e)
{
    re_vector o;
    int Stack[maxn*10];
    top=0;
    int j= e;
    while(path[j]!=-1)
    {

        Stack[top++] = j;
        j = path[j];

    }
    Stack[top++] = j;
    // printf("%d=>%d, length:%d, path: %d ",s,j,dist[j],s);
    o.top =0;
    o.data[o.top++] = s;
    while(top!=0)       //�Ƚ����,�������
    {
        o.data[o.top++] = Stack[top-1];
        top--;            //��ջ��ͷ�ڵ㵯��
    }
    o.Size =o.top;
    return o;
}
string limit_dijkstra(int Limit[],int L_size,int s,int e)
{
    string temp;
    int Sum = 0;
    temp+="·����";
    char c[20];
    re_vector o;
    int temp_path[maxn*10];
    int ttop = 0;
    int pre = s,i;
    for(i=1; i<=L_size; i++)
    {
        dijkstra(pre,Limit[i]);
        Sum+=Top_dis;
        // cout<<pre<<" "<<Limit[i]<<endl;
        o = dijkstra_print_path2(pre,Limit[i]);
        for(int j=0; j<o.Size-1; j++)
        {
            temp_path[ttop++] = o.data[j];
            //printf("%d ",o.data[j]);
        }
        pre = Limit[i];
    }
    i--;
    // cout<<Limit[i]<<" "<<e<<endl;
    dijkstra(Limit[i],e);
    Sum+=Top_dis;
    o = dijkstra_print_path2(Limit[i],e);
    for(int j=0; j<o.Size-1; j++)
    {
        temp_path[ttop++] = o.data[j];
        //printf("%d ",o.data[j]);
    }
    temp_path[ttop++] = e;
    for(int j=0; j<ttop; j++)
    {
        // printf("%d ",temp_path[j]);
        sprintf(c,"%s ",Atrans[temp_path[j]].c_str());
        temp+=c;
    }
//    temp+="\n";
    temp+=Cal_time(Sum);
    sprintf(c,"\n���ȣ�%d\n",Sum);
    temp+=c;
    return temp;
}
string Init_limit_dijksta(int Src,int End,int Size,string limit[])
{
    int Limit[maxn];
//    printf("���������Ƶ������");
//    int Size;
//    cin>>Size;
//    printf("�������������Ƶ㣺");
    for(int i=1; i<=Size; i++)
        Limit[i]= Transform2(limit[i]);
//        scanf("%d",&Limit[i]);
    return limit_dijkstra(Limit,Size,Src,End);
}
/*--------------------------END------------------------*/

/*-------------��У԰С��������С���˺�����վ��---------------------*/

int MM,NN;
int Spe_Graph[maxn][maxn];
int V[maxn];
struct road
{
    int r[maxn][maxn];
} road[maxn];
void Bus_road_init()//��ʼ��
{
    for(int i = 0; i < NN; i++)
    {
        for(int j = 0; j < NN ; j++)
        {
            if(i == j)
                Spe_Graph[i][j] = 0;
            else
                Spe_Graph[i][j] = inf;
        }
    }
    memset(road,0,sizeof(road));
}
int build_map(int id)
{

    ifstream infile;
    infile.open("Bus_data.txt");//�������ļ�
    if(!infile)
    {
        cerr<<"error: unable to open input file: "
            << infile << endl;
        return 1;
    }
    infile>>MM>>NN;
    Bus_road_init();
//    printf("�����빫����·�����͵���\n");
//    scanf("%d%d", &m, &n);
//    int sum,k,t;
    int temp[maxn];
    int ttop = 0;
    if(id==1)
    {
        for(int i=1; i<=MM; i++)
        {
            int mm;
            //scanf("%d",&mm);
            infile>>mm;
            ttop = 0;
            for(int j=1; j<=mm; j++)
            {
                int yy;
                //scanf("%d",&yy);
                infile>>yy;
                temp[ttop++] = yy;
            }
            for(int j = 0; j < ttop - 1; j++)
            {
                road[i].r[temp[j]][temp[j + 1]] = road[i].r[temp[j + 1]][temp[j]] = 1;
            }
            for(int j=0; j<ttop; j++)
            {
                for(int k = 0; k<ttop; k++)
                {
                    Spe_Graph[temp[j]][temp[k]] = abs(k-j);
                    Spe_Graph[temp[k]][temp[j]] = abs(k-j);
                    //����ǵ���Ļ����������޸ĳ�k��j+1��ʼ,�������ĳ�һ��
                }
                //Spe_Graph[temp[j]][temp[j + 1]] = Spe_Graph[temp[j + 1]][temp[j]] = 1;
            }
        }

    }
    else
    {
        for(int i=1; i<=MM; i++)
        {
            int mm;
            //scanf("%d",&mm);
            infile>>mm;
            ttop = 0;
            for(int j=1; j<=mm; j++)
            {
                int yy;
                //scanf("%d",&yy);
                infile>>yy;
                temp[ttop++] = yy;
            }
            for(int j = 0; j < ttop - 1; j++)
            {
                road[i].r[temp[j]][temp[j + 1]] = road[i].r[temp[j + 1]][temp[j]] = 1;
            }
            for(int j=0; j<ttop - 1; j++)
            {
                /*for(int k = 0;k<ttop;k++)
                {
                    if(id==1)
                    {
                      Spe_Graph[temp[j]][temp[k]] = abs(k-j);
                      Spr_Graph[temp[k]][temp[j]] = abs(k-j);
                    }
                    else {
                         Spe_Graph[temp[j]][temp[k]] = 1;
                         Spe_Graph[temp[k]][temp[j]] = 1;
                    }
                    //����ǵ���Ļ����������޸ĳ�k��j+1��ʼ,�������ĳ�һ��
                }*/
                Spe_Graph[temp[j]][temp[j + 1]] = Spe_Graph[temp[j + 1]][temp[j]] = 1;
            }
        }
    }

    infile.close();
    return 1;
}

void Bus_road_dijkstra(int Src,int End)
{
    memset(path,-1,sizeof(path));
    int vis[maxn]= {0};
    for(int i=0; i<=NN; i++)
    {
        dist[i] = Spe_Graph[Src][i];
        vis[i] = 0;
    }
    vis[Src] = 1;
    dist[Src] =0;
    for(int i=1; i<NN; i++)
    {
        int min_val =inf,min_id =-1;
        for(int j=0; j<NN; j++)
        {
            if(!vis[j]&&dist[j]<min_val)
            {
                min_val = dist[j];
                min_id = j;
            }
        }
        if(min_val==-inf)break;
        vis[min_id] = 1;
        for(int j=0; j<NN; j++)
        {
            if(!vis[j]&&dist[j]>min_val+Spe_Graph[min_id][j])
            {
                path[j] = min_id;
                dist[j] = min_val+Spe_Graph[min_id][j];
            }
        }
    }
//    if(dist[End] <= 0)
//    printf("NO\n");
//    else
//    printf("%d\n", dist[End]-1);
}
string Bus_road_dijkstra_print_path(int Src,int End,int id)
{
    string temp;
    int Stack[maxn*10],N1,k;
    top=0;
    for(int i=End; i<=End; i++)
    {
        if(i==Src)continue;
        int j= i;
        while(path[j]!=-1)
        {

            Stack[top++] = j;
            j = path[j];

        }
        Stack[top++] = j;
        //printf("%d=>%d, length:%d, path: %d ",Src,i,dist[i],Src);
        //printf("%d=>%d ",Src,i);
        if(dist[i] == inf)
        {
            sprintf(c,"No Path!\n");
            temp+=c;
        }
        else
        {
            int Count = 1;
            N1 = 0;
            V[N1++] = Src;

            sprintf(c,"·��:\n%s",Atrans[Src].c_str());
            temp+=c;
            while(top!=0)       //�Ƚ����,�������
            {
                sprintf(c,"->%s",Atrans[Stack[top-1]].c_str());//��ӡջ��ͷ�ڵ�
                temp+=c;
                V[N1++] = Stack[top - 1];
                top--;
                if(Stack[top] == i) break;            //��ջ��ͷ�ڵ㵯��
            }
            int f;
            for(j = 1; j <= MM; j++)
                if(road[j].r[Src][V[1]])
                {
                    f = j;
                    break;
                }
            sprintf(c,"\n����·�ߣ�\n");
            temp+=c;
            if(id==1)
            {
                sprintf(c,"��%s�ϳ�",Atrans[Src].c_str());
            temp+=c;
            }
            else{
                sprintf(c,"��%s�ϳ�����%d·",Atrans[Src].c_str(),f);
            temp+=c;
            }

            for(j = 0; j < N1 - 1; j++)
            {
                for(k = 1; k <= MM; k++)
                {
                    if(road[k].r[V[j]][V[j + 1]])
                    {
                        if(f == k)
                        {
                            break;
                        }
                        else
                        {
                            sprintf(c,"��%s�³�",Atrans[V[j]].c_str());
                            temp+=c;
                            f = k;
                            Count++;
                            if(V[j] != i)
                            {
                                if(id==1)
                                {
                                    sprintf(c,"\n��%s�ϳ�",Atrans[V[j]].c_str());
                                    temp+=c;
                                }
                                else{
                                    sprintf(c,"\n��%s�ϳ�����%d·",Atrans[V[j]].c_str(),f);
									temp+=c;
                                }

                            }
                            break;
                        }
                    }
                }
            }
            sprintf(c,"��%s�³�\n",Atrans[i].c_str());
            temp+=c;
            sprintf(c,"���˴�����%d\n",Count-1);
            temp+=c;
            if(id==1)
            {
                sprintf(c,"����վ��(�����)��%d\n",dist[End]+1);
                temp+=c;
            }

        }
    }
//    cout<<temp<<endl;
//    temp="";
    return temp;

}

string Bus_road(int Src,int End,int id)//id����1ʱ������վ����id����2ʱ���ٻ���
{

    build_map(id);
    Bus_road_dijkstra(Src,End);//�����·
    return Bus_road_dijkstra_print_path(Src,End,id);//������
}
/*----------------------END--------------------------*/

/*-----------------------��ȡ�����ļ�--------------------------*/
int Read_data()
{
    ifstream infile;
    infile.open("Graph_data.txt");//�������ļ�
    if(!infile)
    {
        cerr<<"error: unable to open input file: "
            << infile << endl;
        return 1;
    }
    infile>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            infile>>tu[i][j];//����������
            Graph[i][j] = tu[i][j];
        }

    infile.close();
    infile.open("Bike_data.txt");//�������ļ�
    if(!infile)
    {
        cerr<<"error: unable to open input file: "
            << infile << endl;
        return 1;
    }
    infile>>Bike.n;
    infile>>Bike.total_num;
    infile>>Bike.date;
    infile>>Bike.state;
    infile>>Bike.Fa;
    infile>>Bike.Fb;
    for(int i=0; i<n; i++)
        infile>>Bike.num[i];
    for(int i=0; i<n; i++)
        infile>>Bike.num_pre[i];
    for(int i=0; i<n; i++)
        infile>>Bike.num_by[i];
    for(int i=0; i<n; i++)
        infile>>Bike.Dx_pre[i];
    infile.close();
    return 1;
}
/*-----------------------���������ļ�--------------------------*/
void Update_n()
{
    ofstream outfile("Graph_data.txt");
    outfile<<n;
    outfile<<"\n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            outfile<<tu[i][j];
            outfile<<" ";
        }
        outfile<<"\n";
    }
    outfile.close();
}
void Save_data()
{
    ofstream outfile("Bike_data.txt");
    //outfile.open(out);
    outfile<<Bike.n;
    outfile<<"\n";
    outfile<<Bike.total_num;
    outfile<<"\n";
    outfile<<Bike.date;
    outfile<<"\n";
    outfile<<Bike.state;
    outfile<<"\n";
    outfile<<Bike.Fa;
    outfile<<"\n";
    outfile<<Bike.Fb;
    outfile<<"\n";
    for(int i=0; i<n; i++)
    {
        outfile<<Bike.num[i];
        outfile<<" ";
    }
    outfile<<"\n";
    for(int i=0; i<n; i++)
    {
        outfile<<Bike.num_pre[i];
        outfile<<" ";
    }
    outfile<<"\n";
    for(int i=0; i<n; i++)
    {
        outfile<<Bike.num_by[i];
        outfile<<" ";
    }
    outfile<<"\n";
    for(int i=0; i<n; i++)
    {
        outfile<<Bike.Dx_pre[i];
        outfile<<" ";
    }
    outfile<<"\n";
    outfile.close();
}
/*---------------------END--------------------*/

/*-------------------��ʼ����������----------------------*/
string INIT_BIKE_INFO()
{
//    for(int i=0; i<n; i++)
//    {
//        Bike.num[i] = 5;
//    }
    Read_data();
    Bike = Bike_shift_plan(Bike);
    Save_data();
    return info_init(Bike);

}
/*-----------------Floyd���TSP�������ļ�--------------------*/
void Floyd()
{
	//int n,tu[100][100];
	 freopen("Graph_data3.txt","r",stdin);
    freopen("Graph_data2.txt","w",stdout);
    cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>tu[i][j];
        }
    }
    for(int i=0;i<n;i++)
    {
        tu[i][i] = 0;
    }
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(tu[i][j]>tu[i][k]+tu[k][j]&&k!=i&&k!=j&&i!=j)
                {
                    tu[i][j] = tu[i][k]+tu[k][j];
                }
            }
        }
    }
    cout<<n<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<tu[i][j]<<" ";
        }
        cout<<endl;
    }
}
/*-----------------END--------------------*/

/*---------------�㷨�������������--------------------*/
void Function()
{
    string String_path;
    //INIT_BIKE_INFO();
    /*--------------------------
    ����1:Ѱ��Դ�㵽�յ��k��·
    ����ӡ·��
    API����ͼ���ڽӾ���,K����㣬�յ�,����n��
    -------------------------------*/
   int Graph[5][5]=
    {
        0,inf,inf,inf,inf,
        inf,0,1,2,3,
      inf,inf,0,1,2,
        inf,inf,inf,0,1
    };
    Find_Kth function1;
    //���Ե���
    string temp= function1.Find_kth(Graph,1,1,4,5);
    cout<<temp<<endl;

    /*--------------------------------
    ����2����ӡ��㵽�յ������·����
    ������·����������
    ----------------------------------*/
//    String_path = Init_Print_all_path(0,4);
//    cout<<String_path<<endl;
    /*---------------------------------
    ����3������㵽�յ�����·��
    ����+������+������+����
    ��1��ֱ�����·
    ��2������ǰ��û�й�����ʱ�ķ���
    ��3���ṩ��С���˷�������������վ�㷽��
    idΪ1�������վ�㣬idΪ2������ٻ���
    ----------------------------------*/
    /*String_path  = Init_dijkstra(0,4);//��1��
    cout<<String_path<<endl;
    String_path = find_Bike_path(0,4);
    cout<<String_path<<endl;*/
    /*String_path = Bus_road(1,7,1);//��3��
    cout<<String_path<<endl;*/
    /*----------------------------------
    ����4��ʵ�ִ������Ƶ�����·��
    �������������Ƶ㣬��������·��
    ���뾭����Щ��
    Api:����㣬�յ㣬���Ƶ���������Ƶ����飩
    ------------------------------------*/
    /*string Exm[maxn];
    Exm[1] = "15��";
     String_path = Init_limit_dijksta(0,4,1,Exm);
     cout<<String_path<<endl;*/
    /*----------------------------------
    ����5���Ƽ��ӵ�ǰ��һ�α���У԰���е�
    �ٻص���ǰ������·��
    ------------------------------------*/
//    String_path = TSP("����");
//    cout<<String_path<<endl;
    /*-----------------------------------
    ����6��һ������󣬼������������
    ��ѵ��ȷ�������ӡ
    ------------------------------------*/
    Bike_info real;
    real.n = 2;
    real.m = 2;
    for(int i=0; i<real.n; i++)
    {
        real.num_n[i] = i+1;
        real.In_id[i] = i+1;
    }
    for(int i=0; i<real.m; i++)
    {
        real.num_m[i] = 2-i;
        real.Out_id[i] = 2-i;
    }
    Distribute_plan(real);
}
/*---------------------------END------------------------------*/

/*---------------------------ͼ�ν���------------------------------*/

char buffer[99999];
typedef struct Arc //�ߵ�Ȩֵ��Ϣ
{
    int dis;//����
} matrix[MaxVnum][MaxVnum]; //�ڽӾ���
typedef struct Vinfo//������Ϣ
{
    int id;//�����ţ�
    char name[111];//�������ƣ�
    char introduction[1111];//������ܣ�

} Vinfo;
typedef struct graph //ͼ�ṹ��Ϣ��
{
    Vinfo V[MaxVnum];//�������飻
    matrix Arc;//�ڽӾ���
    int Vnum, Arcnum;
    int length;
} graph;
graph initgraph()
{
    int i,j;
    graph c;
    c.length = 52;//�������
    c.Vnum = 52;
    for(i = 1; i <= c.Vnum; i++)
        c.V[i].id = i;
    strcpy(c.V[1].name,"����");
    strcpy(c.V[1].introduction,"����������λ��ѧУ�����ǵ�һ��������");
    strcpy(c.V[2].name,"�Ĳ�");
    strcpy(c.V[2].introduction,"���Ĳ���λ��ɽ������ѧ��У�������棬˫�㽨��ʳ�ã������ḻ��ζ���ɿڣ�Ϊ��У�����ѧ���ṩ�����õ���ʳ����");
    strcpy(c.V[3].name,"15��");
    strcpy(c.V[3].introduction,"��Ҫ����ѧԺ�Ͽεĵط�");
    strcpy(c.V[4].name,"УҽԺ");
    strcpy(c.V[4].introduction,"ɽ������ѧҽԺ�Ǽ�ҽ�ơ�Ԥ��������һ����ۺ���ҽ�Ƶ�λ��ҽԺ����������У������У�����з�Ժ��ҽԺ�����ڻ���������У԰�ڣ��������5290ƽ����");
    strcpy(c.V[5].name,"21������");
    strcpy(c.V[5].introduction,"ѧ��ס�޵ĵط�");
    strcpy(c.V[6].name,"13������");
    strcpy(c.V[6].introduction,"ѧ��ס�޵ĵط�");
    strcpy(c.V[7].name,"ѧ����Ԣ");
    strcpy(c.V[7].introduction,"ѧ��ס�޵ĵط�");
    strcpy(c.V[8].name,"����");
    strcpy(c.V[8].introduction,"ֻ������ͨ����������·������·������·���Ķ���·��");
    strcpy(c.V[9].name,"����");
    strcpy(c.V[9].introduction,"�����������㣬����������԰�������羰����");
    strcpy(c.V[10].name,"ũ��");
    strcpy(c.V[10].introduction,"��ȡ�");
    strcpy(c.V[11].name,"��ѧ����������");
    strcpy(c.V[11].introduction,"��Ϊ�ĸ�¥�㣬�ĸ�¥��ֲ�����һ������ݳ���̨�͹���ϯ�⣬�������������ҡ����г���ȣ���������ί�칫�ҡ���վ�ʹ�ѧ����ҵָ�����ġ��ڹ���ѧ���ĵȣ�����ֲ���Уѧ���ᡢ�������ϻᡢ���������ĵȲ����Ĳ���Ҫ��һЩΪ��֤�������������ļ���豸�ȡ�Զ�������ǵ��������ģ�������һ˫�ſ��ֵ�˫�ۣ��ȴ��ű�ͬѧ��ӵ����ģ�������ݷ�ͼ���ң���Ӧ���γ�һ��Ư������Բ");
    strcpy(c.V[12].name,"ԡ��");
    strcpy(c.V[12].introduction,"ѧ����ԡ����");
    strcpy(c.V[13].name,"���³���");
    strcpy(c.V[13].introduction,"λ�����͸��������ڵ��£��ʵ������³���");
    strcpy(c.V[14].name,"���");
    strcpy(c.V[14].introduction,"����º���������Ǵ�ѧ�������㳡���׳ƴ�ӣ������Ǹ��ǳ���Ծ�ĵط����ܶ�Ĵ�����ᶼ����������еģ��������һ����־�Եط�������������ǧ���ڣ��ٰ�Ľ�Ŀ��ȻҲ���൱�ľ�����");
    strcpy(c.V[15].name,"��º�");
    strcpy(c.V[15].introduction,"����ѧУ�Ļ�԰���峺�ĺ�ˮ�ͻ����ź�ˮ��ɽ�£��������񣬷羰�������Ǹ��ۻ�ɢ���ĺõط�");
    strcpy(c.V[16].name,"10��");
    strcpy(c.V[16].introduction,"����ѧԺѧ���Ͽεĵط�");
    strcpy(c.V[17].name,"8��");
    strcpy(c.V[17].introduction,"�����ѧԺѧ���Ͽεĵط�");
    strcpy(c.V[18].name,"9��");
    strcpy(c.V[18].introduction,"�������ѧ�뼼��ѧԺѧ���Ͽεĵط�");
    strcpy(c.V[19].name,"11��");
    strcpy(c.V[19].introduction,"����ѧԺѧ���Ͽεĵط�");
    strcpy(c.V[20].name,"6��");
    strcpy(c.V[20].introduction,"ѧ���Ͽεĵط�");
    strcpy(c.V[21].name,"����");
    strcpy(c.V[21].introduction,"���в͹ݣ����У�����ȵ�");
    strcpy(c.V[22].name,"����");
    strcpy(c.V[22].introduction,"��Ҫ������,Ҳ�����������ĳ���");
    strcpy(c.V[23].name,"ɽ��");
    strcpy(c.V[23].introduction,"λ�����山�࣬��Ҫ��Сɽ���С����");
    strcpy(c.V[24].name,"����԰");
    strcpy(c.V[24].introduction,"����ũҵ���У����кͽ�ʦ��Ԣ¥�ȵ�");
    strcpy(c.V[25].name,"����");
    strcpy(c.V[25].introduction,"�ڹ�����·������ͷ��Ҳ������·���Ͼ�·�����ߣ�����������ʻ��");
    strcpy(c.V[26].name,"����");
    strcpy(c.V[26].introduction,"����ʮ·������·������Ҳ�����������Ķ���");
    strcpy(c.V[27].name,"У��");
    strcpy(c.V[27].introduction,"������ѧУ���ҵ�ܹ�˾��ѧУ��Ӫ���ʲ��Ĺ����ţ�����ѧУ��ʹ�ɶ�Ȩ������ѧУ��Ӫ���ʲ��е���ȫ����ֵ����ֵ���Σ��е��Ƽ��ɹ�ת���Ͳ�ҵ������");
    strcpy(c.V[28].name,"ʳ��");
    strcpy(c.V[28].introduction,"��ѧУ������������ְ�ܲ��ţ��ճ���������������ۺϿơ����̼����ƺͷ��ز�����ƣ�������������ʵ��");
    strcpy(c.V[29].name,"5��ʵ��");
    strcpy(c.V[29].introduction,"ʵ��¥");
    strcpy(c.V[30].name,"4��ʵ��");
    strcpy(c.V[30].introduction,"ʵ��¥");
    strcpy(c.V[31].name,"����ʵ��");
    strcpy(c.V[31].introduction,"����ͬѧ��ʵ��ĵط�");
    strcpy(c.V[32].name,"��ͨʵ��");
    strcpy(c.V[32].introduction,"��е����ͨѧԺͬѧ��ʵ��ĵط�");
    strcpy(c.V[33].name,"13��");
    strcpy(c.V[33].introduction,"����������ѧԺͬѧ�Ͽεĵط�");
    strcpy(c.V[34].name,"12��");
    strcpy(c.V[34].introduction,"��е����ͨѧԺͬѧ�Ͽεĵط�");
    strcpy(c.V[35].name,"5��");
    strcpy(c.V[35].introduction,"ѧ������ϰ���Ͽεĵط�");
    strcpy(c.V[36].name,"ͼ���");
    strcpy(c.V[36].introduction,"�������3.8��ƽ���ף��������ʯ������һ������ܣ��������̨Ԣ�����ʵǵĽ��ݣ�ͼ��ݽ��������쿪��˫�ۣ���ӭ����֪ʶ���ڷ�ѧϰ��ݷݷѧ���߽�����֪ʶ�ĵ���");
    strcpy(c.V[37].name,"4��");
    strcpy(c.V[37].introduction,"ѧ������ϰ���Ͽεĵط�");
    strcpy(c.V[38].name,"2��");
    strcpy(c.V[38].introduction,"��ɽ������ѧ������������ѧУ��־�Խ���֮һ��ʼ����2000�꣬������Ϊ�Ͳ��м�ѧУ�����ش���估�˶����������ش���");
    strcpy(c.V[39].name,"��԰");
    strcpy(c.V[39].introduction,"�����������ˣ�������Ȼ���Ǽ�ѧ��������������ѵ���ٰ���顢ס�ޡ������ȹ�����һ����ִ�������");
    strcpy(c.V[40].name,"��Ϣ¥");
    strcpy(c.V[40].introduction,"ɽ������ѧԭͼ��ݣ�������Ϊ�˻���");
    strcpy(c.V[41].name,"����");
    strcpy(c.V[41].introduction,"ѧ������ϰ���Ͽεĵط�");
    strcpy(c.V[42].name,"1��ʵ��");
    strcpy(c.V[42].introduction,"����ʵ��������������");
    strcpy(c.V[43].name,"��Զ¥");
    strcpy(c.V[43].introduction,"����ѧУ�İ칫����Ҳ��ѧУ�����棬��ѧУ���ţ�Ҳ�����š���Զ¥ǰ�и��㳡���ʺ�һЩС�͵Ļ");
    strcpy(c.V[44].name,"1�Ź�Ԣ");
    strcpy(c.V[44].introduction,"ѧ��ס�޵ĵط�");
    strcpy(c.V[45].name,"3�Ź�Ԣ");
    strcpy(c.V[45].introduction,"ѧ��ס�޵ĵط�");
    strcpy(c.V[46].name,"2�Ź�Ԣ");
    strcpy(c.V[46].introduction,"ѧ��ס�޵ĵط�");
    strcpy(c.V[47].name,"2��");
    strcpy(c.V[47].introduction,"��Ϊ���㣬��¥����ѡ��");
    strcpy(c.V[48].name,"1��");
    strcpy(c.V[48].introduction,"�ò�����һ��");
    strcpy(c.V[49].name,"һ��");
    strcpy(c.V[49].introduction,"ѧУ�Ĵ�������֮һ��λ��ѧУ������");
    strcpy(c.V[50].name,"2��");
    strcpy(c.V[50].introduction,"�������ľ۾ӵ�");
    strcpy(c.V[51].name,"1��");
    strcpy(c.V[51].introduction,"ѧ������ϰ���Ͽεĵط�");
    strcpy(c.V[52].name,"����");
    strcpy(c.V[52].introduction,"ѧУ�����ţ�λ���´�·��ԭ����·������");
    for(i = 1; i <= c.Vnum; i++)
        for(j = 1; j <= c.Vnum; j++)
            c.Arc[i][j].dis = 0x3f3f3f3f;//��ʼ������
    c.Arc[1][2].dis = 150;
    c.Arc[1][3].dis = 240;
    c.Arc[2][4].dis = 100;
    c.Arc[2][5].dis = 100;
    c.Arc[3][26].dis = 800;
    c.Arc[4][21].dis = 50;
    c.Arc[5][6].dis = 50;
    c.Arc[6][7].dis = 50;
    c.Arc[7][8].dis = 100;
    c.Arc[7][9].dis = 150;
    c.Arc[8][15].dis = 500;
    c.Arc[8][23].dis = 300;
    c.Arc[9][10].dis = 50;
    c.Arc[9][12].dis = 40;
    c.Arc[9][11].dis = 70;
    c.Arc[10][11].dis = 100;
    c.Arc[11][20].dis = 200;
    c.Arc[11][19].dis = 30;
    c.Arc[11][14].dis = 100;
    c.Arc[11][16].dis = 300;
    c.Arc[12][13].dis = 10;
    c.Arc[13][15].dis = 80;
    c.Arc[14][19].dis = 150;
    c.Arc[14][16].dis = 150;
    c.Arc[15][16].dis = 200;
    c.Arc[15][22].dis = 150;
    c.Arc[15][24].dis = 20;
    c.Arc[15][25].dis = 1300;
    c.Arc[16][19].dis = 150;
    c.Arc[16][17].dis = 50;
    c.Arc[17][18].dis = 150;
    c.Arc[17][35].dis = 500;
    c.Arc[17][37].dis = 500;
    c.Arc[18][19].dis = 50;
    c.Arc[22][24].dis = 200;
    c.Arc[22][23].dis = 50;
    c.Arc[23][24].dis = 20;
    c.Arc[24][25].dis = 600;
    c.Arc[25][26].dis = 1800;
    c.Arc[25][46].dis = 1000;
    c.Arc[26][27].dis = 300;
    c.Arc[26][29].dis = 600;
    c.Arc[26][33].dis = 700;
    c.Arc[27][28].dis = 100;
    c.Arc[27][30].dis = 100;
    c.Arc[27][29].dis = 90;
    c.Arc[28][31].dis = 80;
    c.Arc[28][52].dis = 1400;
    c.Arc[29][33].dis = 100;
    c.Arc[29][30].dis = 500;
    c.Arc[30][34].dis = 100;
    c.Arc[30][31].dis = 600;
    c.Arc[31][32].dis = 600;
    c.Arc[31][36].dis = 800;
    c.Arc[32][52].dis = 1200;
    c.Arc[33][35].dis = 800;
    c.Arc[33][34].dis = 100;
    c.Arc[34][35].dis = 600;
    c.Arc[35][37].dis = 150;
    c.Arc[35][36].dis = 500;
    c.Arc[36][37].dis = 500;
    c.Arc[36][38].dis = 800;
    c.Arc[36][42].dis = 1000;
    c.Arc[37][38].dis = 400;
    c.Arc[38][39].dis = 100;
    c.Arc[38][40].dis = 500;
    c.Arc[39][40].dis = 200;
    c.Arc[40][44].dis = 600;
    c.Arc[40][41].dis = 500;
    c.Arc[41][43].dis = 700;
    c.Arc[41][42].dis = 200;
    c.Arc[42][52].dis = 500;
    c.Arc[43][52].dis = 600;
    c.Arc[43][44].dis = 400;
    c.Arc[43][50].dis = 700;
    c.Arc[44][45].dis = 100;
    c.Arc[44][48].dis = 100;
    c.Arc[45][46].dis = 100;
    c.Arc[46][47].dis = 200;
    c.Arc[47][49].dis = 100;
    c.Arc[49][50].dis = 500;
    c.Arc[50][51].dis = 200;
    c.Arc[51][52].dis = 800;
    for(i = 1; i <= c.Vnum; i++)
        for(j = 1; j <= c.Vnum; j++)
            c.Arc[j][i].dis = c.Arc[i][j].dis;
    return c;
}
void initXml()
{
    TiXmlDocument *doc = new TiXmlDocument();
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "ANSI", "yes");
    doc->LinkEndChild(decl);
    doc->SaveFile("buildings.xml");
}
graph readXml()
{
    graph b;
    int i = 1;
    TiXmlDocument doc("buildings.xml");
    doc.LoadFile();
    TiXmlElement *rootElement = doc.RootElement();
    for(TiXmlElement *buildElement = rootElement->FirstChildElement();
            buildElement!=NULL;
            buildElement = buildElement->NextSiblingElement())
    {
        TiXmlElement *idElem = buildElement->FirstChildElement();
        TiXmlElement *nameElem = idElem->NextSiblingElement();
        TiXmlElement *desElem = nameElem->NextSiblingElement();;
        b.V[i].id = atoi(idElem->GetText());
        strcpy(b.V[i].name,(nameElem->FirstChild()->Value()));
        //b.V[i].name = (nameElem->FirstChild()->Value());
        strcpy(b.V[i].introduction,desElem->FirstChild()->Value());
        // b.V[i].introduction = desElem->FirstChild()->Value();
        i++;
    }
    b.length = i;
    return b;
}
void writeXml(graph b)
{
    TiXmlDocument *doc = new TiXmlDocument();
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "ANSI", "yes");
    doc->LinkEndChild(decl);
    TiXmlElement *rootElement = new TiXmlElement("buildings");
    for(int i=1; i<=b.length; i++)
    {
        TiXmlElement *buildElement = new TiXmlElement("building");
        TiXmlElement *idElement = new TiXmlElement("id");
        char string[100];
        //itoa((b.V[i].id) , string, 10);
        TiXmlText *text1 = new TiXmlText(string);
        idElement->LinkEndChild(text1);
        TiXmlElement *nameElement = new TiXmlElement("name");
        TiXmlText *text2 = new TiXmlText(b.V[i].name);
        nameElement->LinkEndChild(text2);
        TiXmlElement *desElement = new TiXmlElement("introduction");
        TiXmlText *text3 = new TiXmlText(b.V[i].introduction);
        desElement->LinkEndChild(text3);
        buildElement->LinkEndChild(idElement);
        buildElement->LinkEndChild(nameElement);
        buildElement->LinkEndChild(desElement);
        rootElement->LinkEndChild(buildElement);
    }
    doc->LinkEndChild(rootElement);
    doc->SaveFile("buildings.xml");
}
bool isBuilding(graph b, int id, string name)
{
    for(int i=1; i<=b.length; i++)
    {
        if(b.V[i].name==name|| b.V[i].id==id)
        {
            return true;
        }
    }
    return false;
}
bool isBuildName(graph b,  string name)
{
    for(int i=1; i<=b.length; i++)
    {
        if(b.V[i].name==name)
        {
            return true;
        }
    }
    return false;
}
bool isBuildId(graph b, int id)
{
    for(int i=1; i<=b.length; i++)
    {
        if(b.V[i].id==id)
        {
            return true;
        }
    }
    return false;
}
graph addXml(graph b, int id, string name, string introduction)
{
    b.V[b.length].id = id;
    strcpy(b.V[b.length].name,name.c_str());
    strcpy(b.V[b.length].introduction,introduction.c_str());
    //b.V[b.length].name = name.c_str();
    //b.V[b.length].introduction = introduction.c_str();
    b.length++;
    return b;
}
graph removeXml(graph b, int id)
{
    for(int i=1; i<=b.length; i++)
    {
        if(b.V[i].id == id)
        {
            for(int j=i; j<=b.length-1; j++)
            {
                b.V[j]=b.V[j+1];
            }
        }
    }
    b.length--;
    return b;
};
graph checkXml(graph b)
{
    int idid;
    for(int i=1; i<=b.length; i++)
    {
        if(b.V[i].id==0||b.V[i].id>62)
            idid = b.V[i].id;
    }
    b = removeXml(b, idid);
    return b;
}
graph changeXml(graph b, int id,string name,string introduction)
{
    for(int i=1; i<=b.length; i++)
    {
        if(b.V[i].id == id)
        {
            strcpy(b.V[i].name,name.c_str());
            strcpy(b.V[i].introduction,introduction.c_str());
//            b.V[i].name = name.c_str();
//            b.V[i].introduction = introduction.c_str();
        }
    }
    return b;
};


void writeGraph(graph node1)
{
    ofstream out("graph.txt");
    if(out.is_open())
    {
        char c[20];
        for(int i=0; i<=52; i++)
        {
            for(int j=0; j<=52; j++)
            {
                sprintf(c,"%d ",node1.Arc[i][j].dis);
                out<<c;
            }
        }
    }
    out.close();
}
graph readGraph(graph node)
{
    ifstream in;
    in.open("graph.txt");
    if(in.is_open())
    {
        in.get(buffer, 2809*12);
        in.close();
    }
    else
    {
        cout<<"�ļ�δ��"<<endl;
    }
    stringstream temp(buffer);
    int *a = new int[99999];
    int top = 0;
    while(temp)
    {
        temp>>a[top++];
    }
    int index = 0;
    for(int i=0; i<=52; i++)
    {
        for(int j=0; j<=52; j++)
        {
            node.Arc[i][j].dis = a[index++];
        }
    }
    return node;
}
struct node
{
    char  x[111];
    char  y[111];
    int xId;
    int yId;
} Data;
struct node2
{
    string x;
} Data2;
void Transform()
{
    graph real;
    real = readXml();
    std::string Temp;
    for(int i=1; i<=52; i++) //n
    {
        Temp =real.V[i].name;
        Atrans[i-1] = Temp;
        //cout<<real.V[i].id-1<<" "<<Temp<<endl;
        //Trans[Temp] = real.V[i].id;
        //Atrans[real.V[i].id] = Temp;
    }
    Read_data();

}
void Test1()
{
    Transform();
    string String_path;
    String_path = TSP("����");
    cout<<String_path<<endl;
}


std::string limit[100];
int index = 0;

class MyButton16 :public QPushButton{
    /***
       ���ؼ�������������Ϊ�˲������ŵ���¼��Ľ������Զ��ͷŵ��ؼ�
    ***/
        QString name;
        QWidget window;
        QPushButton button;
    public:
        /**
        ������ʼ����ť�����ݰ�ť�ϵ�����
        **/
        MyButton16(QString name)
        {
            this->name = name;
        };
        MyButton16() {};
        /****
         ����ť�����ִ����Լ����Ӵ���
        ****/
        void setChildText(QString name)
        {
        this->name = name;
        }
    protected:
        /***
        �����ť�������¼�
        ***/
        void mousePressEvent(QMouseEvent* event);

    };
void MyButton16::mousePressEvent(QMouseEvent* event)
{
    /**
     ���ô��ڵĴ�С
    **/
     window.resize(100,100);
     button.setText(name);
     button.resize(50,50);
     index++;
     limit[index] = string((const char *)name.toLocal8Bit());
     /**
     ����ť���뵽window�ؼ��У�
     **/
     button.setParent(&window);
     window.show();
     /****
     ��ʾ�������
     ****/
}

/********
ѡ�����ƾ���İ�ť
********/
class MyButton17 : public QPushButton
{
public :
    QString name;
    QWidget window;

    MyButton16 button1;
    MyButton16 button2;
    MyButton16 button3;
    MyButton16 button4;
    MyButton16 button5;
    MyButton16 button6;
    MyButton16 button7;
    MyButton16 button8;
    MyButton16 button9;
    MyButton16 button10;
    MyButton16 button11;
    MyButton16 button12;
    MyButton16 button13;
    MyButton16 button14;
    MyButton16 button15;
    MyButton16 button16;
    MyButton16 button17;
    MyButton16 button18;
    MyButton16 button19;
    MyButton16 button20;
    MyButton16 button21;
    MyButton16 button22;
    MyButton16 button23;
    MyButton16 button24;
    MyButton16 button25;
    MyButton16 button26;
    MyButton16 button27;
    MyButton16 button28;
    MyButton16 button29;
    MyButton16 button30;
    MyButton16 button31;
    MyButton16 button32;
    MyButton16 button33;
    MyButton16 button34;
    MyButton16 button35;
    MyButton16 button36;
    MyButton16 button37;
    MyButton16 button38;
    MyButton16 button39;
    MyButton16 button40;
    MyButton16 button41;
    MyButton16 button42;
    MyButton16 button43;
    MyButton16 button44;
    MyButton16 button45;
    MyButton16 button46;
    MyButton16 button47;
    MyButton16 button48;
    MyButton16 button49;
    MyButton16 button50;
    MyButton16 button51;
    MyButton16 button52;

    MyButton17(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton17::mousePressEvent(QMouseEvent* event)
{
     window.resize(600,600);
     button1.setText(QString::fromLocal8Bit("����"));
     button1.setChildText(QString::fromLocal8Bit("����"));
     button1.resize(100,30);
     button1.setGeometry(0,0,100,30);
     button1.setParent(&window);

     button2.setText(QString::fromLocal8Bit("�Ĳ�"));
     button2.setChildText(QString::fromLocal8Bit("�Ĳ�"));
     button2.resize(100,30);
     button2.setGeometry(0,30,100,30);
     button2.setParent(&window);

     button3.setText(QString::fromLocal8Bit("15��"));
     button3.setChildText(QString::fromLocal8Bit("15��"));
     button3.resize(100,30);
     button3.setGeometry(0,60,100,30);
     button3.setParent(&window);

     button4.setText(QString::fromLocal8Bit("УҽԺ"));
     button4.setChildText(QString::fromLocal8Bit("УҽԺ"));
     button4.resize(100,30);
     button4.setGeometry(0,90,100,30);
     button4.setParent(&window);

     button5.setText(QString::fromLocal8Bit("21������"));
     button5.setChildText(QString::fromLocal8Bit("21������"));
     button5.resize(100,30);
     button5.setGeometry(0,120,100,30);
     button5.setParent(&window);


     button6.setText(QString::fromLocal8Bit("13������"));
     button6.setChildText(QString::fromLocal8Bit("13������"));
     button6.resize(100,30);
     button6.setGeometry(0,150,100,30);
     button6.setParent(&window);

     button7.setText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.setChildText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.resize(100,30);
     button7.setGeometry(0,180,100,30);
     button7.setParent(&window);

     button8.setText(QString::fromLocal8Bit("����"));
     button8.setChildText(QString::fromLocal8Bit("����"));
     button8.resize(100,30);
     button8.setGeometry(0,210,100,30);
     button8.setParent(&window);

     button9.setText(QString::fromLocal8Bit("����"));
     button9.setChildText(QString::fromLocal8Bit("����"));
     button9.resize(100,30);
     button9.setGeometry(0,240,100,30);
     button9.setParent(&window);

     button10.setText(QString::fromLocal8Bit("ũ��"));
     button10.setChildText(QString::fromLocal8Bit("ũ��"));
     button10.resize(100,30);
     button10.setGeometry(0,270,100,30);
     button10.setParent(&window);

     button11.setText(QString::fromLocal8Bit("��ѧ����������"));
     button11.setChildText(QString::fromLocal8Bit("��ѧ����������"));
     button11.resize(100,30);
     button11.setGeometry(0,300,100,30);
     button11.setParent(&window);

     button12.setText(QString::fromLocal8Bit("ԡ��"));
     button12.setChildText(QString::fromLocal8Bit("ԡ��"));
     button12.resize(100,30);
     button12.setGeometry(0,330,100,30);
     button12.setParent(&window);

     button13.setText(QString::fromLocal8Bit("���³���"));
     button13.setChildText(QString::fromLocal8Bit("���³���"));
     button13.resize(100,30);
     button13.setGeometry(0,360,100,30);
     button13.setParent(&window);

     button14.setText(QString::fromLocal8Bit("���"));
     button14.setChildText(QString::fromLocal8Bit("���"));
     button14.resize(100,30);
     button14.setGeometry(0,390,100,30);
     button14.setParent(&window);

     button15.setText(QString::fromLocal8Bit("��º�"));
     button15.setChildText(QString::fromLocal8Bit("��º�"));
     button15.resize(100,30);
     button15.setGeometry(0,420,100,30);
     button15.setParent(&window);

     button16.setText(QString::fromLocal8Bit("10��"));
     button16.setChildText(QString::fromLocal8Bit("10��"));
     button16.resize(100,30);
     button16.setGeometry(0,450,100,30);
     button16.setParent(&window);

     button17.setText(QString::fromLocal8Bit("8��"));
     button17.setChildText(QString::fromLocal8Bit("8��"));
     button17.resize(100,30);
     button17.setGeometry(0,480,100,30);
     button17.setParent(&window);

     button18.setText(QString::fromLocal8Bit("9��"));
     button18.setChildText(QString::fromLocal8Bit("9��"));
     button18.resize(100,30);
     button18.setGeometry(0,510,100,30);
     button18.setParent(&window);

     button19.setText(QString::fromLocal8Bit("11��"));
     button19.setChildText(QString::fromLocal8Bit("11��"));
     button19.resize(100,30);
     button19.setGeometry(0,540,100,30);
     button19.setParent(&window);

     button20.setText(QString::fromLocal8Bit("6��"));
     button20.setChildText(QString::fromLocal8Bit("6��"));
     button20.resize(100,30);
     button20.setGeometry(0,570,100,30);
     button20.setParent(&window);

     button21.setText(QString::fromLocal8Bit("����"));
     button21.setChildText(QString::fromLocal8Bit("����"));
     button21.resize(100,30);
     button21.setGeometry(100,0,100,30);
     button21.setParent(&window);

     button22.setText(QString::fromLocal8Bit("����"));
     button22.setChildText(QString::fromLocal8Bit("����"));
     button22.resize(100,30);
     button22.setGeometry(100,30,100,30);
     button22.setParent(&window);

     button23.setText(QString::fromLocal8Bit("ɽ��"));
     button23.setChildText(QString::fromLocal8Bit("ɽ��"));
     button23.resize(100,30);
     button23.setGeometry(100,60,100,30);
     button23.setParent(&window);

     button24.setText(QString::fromLocal8Bit("����԰"));
     button24.setChildText(QString::fromLocal8Bit("����԰"));
     button24.resize(100,30);
     button24.setGeometry(100,90,100,30);
     button24.setParent(&window);

     button25.setText(QString::fromLocal8Bit("����"));
     button25.setChildText(QString::fromLocal8Bit("����"));
     button25.resize(100,30);
     button25.setGeometry(100,120,100,30);
     button25.setParent(&window);

     button26.setText(QString::fromLocal8Bit("����"));
     button26.setChildText(QString::fromLocal8Bit("����"));
     button26.resize(100,30);
     button26.setGeometry(100,150,100,30);
     button26.setParent(&window);

     button27.setText(QString::fromLocal8Bit("У��"));
     button27.setChildText(QString::fromLocal8Bit("У��"));
     button27.resize(100,30);
     button27.setGeometry(100,180,100,30);
     button27.setParent(&window);

     button28.setText(QString::fromLocal8Bit("ʳ��"));
     button28.setChildText(QString::fromLocal8Bit("ʳ��"));
     button28.resize(100,30);
     button28.setGeometry(100,210,100,30);
     button28.setParent(&window);

     button29.setText(QString::fromLocal8Bit("5��ʵ��"));
     button29.setChildText(QString::fromLocal8Bit("5��ʵ��"));
     button29.resize(100,30);
     button29.setGeometry(100,240,100,30);
     button29.setParent(&window);

     button30.setText(QString::fromLocal8Bit("4��ʵ��"));
     button30.setChildText(QString::fromLocal8Bit("4��ʵ��"));
     button30.resize(100,30);
     button30.setGeometry(100,270,100,30);
     button30.setParent(&window);

     button31.setText(QString::fromLocal8Bit("����ʵ��"));
     button31.setChildText(QString::fromLocal8Bit("����ʵ��"));
     button31.resize(100,30);
     button31.setGeometry(100,300,100,30);
     button31.setParent(&window);

     button32.setText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.setChildText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.resize(100,30);
     button32.setGeometry(100,330,100,30);
     button32.setParent(&window);

     button33.setText(QString::fromLocal8Bit("13��"));
     button33.setChildText(QString::fromLocal8Bit("13��"));
     button33.resize(100,30);
     button33.setGeometry(100,360,100,30);
     button33.setParent(&window);

     button34.setText(QString::fromLocal8Bit("12��"));
     button34.setChildText(QString::fromLocal8Bit("12��"));
     button34.resize(100,30);
     button34.setGeometry(100,390,100,30);
     button34.setParent(&window);

     button35.setText(QString::fromLocal8Bit("5��"));
     button35.setChildText(QString::fromLocal8Bit("5��"));
     button35.resize(100,30);
     button35.setGeometry(100,420,100,30);
     button35.setParent(&window);

     button36.setText(QString::fromLocal8Bit("ͼ���"));
     button36.setChildText(QString::fromLocal8Bit("ͼ���"));
     button36.resize(100,30);
     button36.setGeometry(100,450,100,30);
     button36.setParent(&window);

     button37.setText(QString::fromLocal8Bit("4��"));
     button37.setChildText(QString::fromLocal8Bit("4��"));
     button37.resize(100,30);
     button37.setGeometry(100,480,100,30);
     button37.setParent(&window);

     button38.setText(QString::fromLocal8Bit("2��"));
     button38.setChildText(QString::fromLocal8Bit("2��"));
     button38.resize(100,30);
     button38.setGeometry(100,510,100,30);
     button38.setParent(&window);

     button39.setText(QString::fromLocal8Bit("��԰"));
     button39.setChildText(QString::fromLocal8Bit("��԰"));
     button39.resize(100,30);
     button39.setGeometry(100,540,100,30);
     button39.setParent(&window);

     button40.setText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.setChildText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.resize(100,30);
     button40.setGeometry(100,570,100,30);
     button40.setParent(&window);

     button41.setText(QString::fromLocal8Bit("����"));
     button41.setChildText(QString::fromLocal8Bit("����"));
     button41.resize(100,30);
     button41.setGeometry(100,570,100,30);
     button41.setParent(&window);

     button42.setText(QString::fromLocal8Bit("1��ʵ��"));
     button42.setChildText(QString::fromLocal8Bit("1��ʵ��"));
     button42.resize(100,30);
     button42.setGeometry(200,0,100,30);
     button42.setParent(&window);

     button43.setText(QString::fromLocal8Bit("��Զ¥"));
     button43.setChildText(QString::fromLocal8Bit("��Զ¥"));
     button43.resize(100,30);
     button43.setGeometry(200,30,100,30);
     button43.setParent(&window);

     button44.setText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.setChildText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.resize(100,30);
     button44.setGeometry(200,60,100,30);
     button44.setParent(&window);

     button45.setText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.setChildText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.resize(100,30);
     button45.setGeometry(200,90,100,30);
     button45.setParent(&window);

     button46.setText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.setChildText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.resize(100,30);
     button46.setGeometry(200,120,100,30);
     button46.setParent(&window);

     button47.setText(QString::fromLocal8Bit("2��"));
     button47.setChildText(QString::fromLocal8Bit("2��"));
     button47.resize(100,30);
     button47.setGeometry(200,150,100,30);
     button47.setParent(&window);

     button48.setText(QString::fromLocal8Bit("1��"));
     button48.setChildText(QString::fromLocal8Bit("1��"));
     button48.resize(100,30);
     button48.setGeometry(200,180,100,30);
     button48.setParent(&window);

     button49.setText(QString::fromLocal8Bit("һ��"));
     button49.setChildText(QString::fromLocal8Bit("һ��"));
     button49.resize(100,30);
     button49.setGeometry(200,210,100,30);
     button49.setParent(&window);

     button50.setText(QString::fromLocal8Bit("2��"));
     button50.setChildText(QString::fromLocal8Bit("2��"));
     button50.resize(100,30);
     button50.setGeometry(200,240,100,30);
     button50.setParent(&window);

     button51.setText(QString::fromLocal8Bit("1��"));
     button51.setChildText(QString::fromLocal8Bit("1��"));
     button51.resize(100,30);
     button51.setGeometry(200,270,100,30);
     button51.setParent(&window);

     button52.setText(QString::fromLocal8Bit("����"));
     button52.setChildText(QString::fromLocal8Bit("����"));
     button52.resize(100,30);
     button52.setGeometry(200,300,100,30);
     button52.setParent(&window);

     window.show();
}

/*******
������Ϣ���¼���ť
*******/
class MyButton15 :public QPushButton{
        QString name;
        QWidget window;
        QPushButton button;
    public:
        MyButton15(QString name)
        {
            this->name = name;
        };
        MyButton15() {};
        void setChildText(QString name)
        {
        this->name = name;
        }
    protected:
        void mousePressEvent(QMouseEvent* event);

    };
void MyButton15::mousePressEvent(QMouseEvent* event)
{
     window.resize(100,100);
     std::string str = string((const char *)name.toLocal8Bit());
     std::string name;
     std::string introduction;
     int id ;
     if(str=="���ĺ�")
     {
          name = "���ĺ�";
          introduction = "����һ�����ĺ�";
     }else if(str=="���¯"){
          name = "���¯";
          introduction = "����һ�����¯";
     }else if(str=="��ƺ"){
          name = "��ƺ";
          introduction = "����һ����ƺ";
     }else if(str=="��У"){
          name = "��У";
          introduction = "����һ����У";
     }else if(str=="3�Ź�Ԣ"){
          name = "3�Ź�Ԣ";
          introduction = "����һ��3�Ź�Ԣ";
     }else if(str=="�о�����Ԣ"){
          name = "�о�����Ԣ";
          introduction = "����һ���о�����Ԣ";
     }else if(str=="9������"){
          name = "9������";
          introduction = "����һ��9������";
     }else if(str=="6������"){
          name = "6������";
          introduction = "����һ��6������";
     }else if(str=="8������"){
          name = "9������";
          introduction = "����һ��9������";
     }else if(str=="����"){
          name = "����";
          introduction = "����һ������";
     }
     graph gh = readXml();
     id = gh.V[gh.length-1].id+1;
     gh = addXml(gh, id, name, introduction);
     gh = checkXml(gh);
     writeXml(gh);
     button.setText(QString::fromLocal8Bit("��ӳɹ���"));

     button.resize(100,100);
     button.setParent(&window);
     window.show();
}





/**��ӡ���������¼�**/
class MyButton14 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton14(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton14::mousePressEvent(QMouseEvent* event)
{
    //label.setText("");
    window.resize(700,700);
    label.resize(500,500);
    label.setGeometry(0,0,500,500);
    label.setWordWrap(true);
    label.setAlignment(Qt::AlignTop);
    /*std::string str[100];
    str[1] = "15��";
    Transform();
    std::string String_path = Init_limit_dijksta(0,4,1,str);
    for(int i=0;i<=index-1;i++)
    {
        cout<<limit[i]<<endl;
    }*/
    Transform();

//    cout<<String_path<<endl;
     cout<<Data.x<<" "<<Data.y<<endl;

    int x = Transform2(Data.x);
    int y = Transform2(Data.y);
    cout<<x<<" "<<y<<endl;
    string String_path1;
    string String_path2;
    String_path1 = Bus_road(x,y,1);
    String_path2 = Bus_road(x,y,2);
    string String_path;
    //String_path = Init_Print_all_path(x,y);
    //String_path = Init_limit_dijksta(x,y,index,limit);
    //index = 0;
    String_path = "Ϊ����ӡ�������ٹ�������·�ߣ�\n"+String_path1+"\n\n\n\nΪ���´�ӡ����վ�����ٵĹ�������·�ߣ�\n"+String_path2;
    cout<<String_path<<endl;
    cout<<x<<" "<<y<<endl;
    char a[10000];
    strcpy(a, String_path.c_str());
    label.setText(QString::fromLocal8Bit(a));
    //cout<<String_path<<endl;
    //std::string String_path;

    //QString path1 = QString::fromStdString(path);

    //desLabel.setText(QString::fromLocal8Bit(node.V[i].introduction));
    //label.setText(path1);
    label.setParent(&window);
    window.show();
}



/**�߱�У԰���¼�**/
class MyButton13 :public QPushButton{
        QString name;
        QWidget window;
        QPushButton button;
        QLabel label;
    public:
        MyButton13(QString name)
        {
            this->name = name;
        };
        MyButton13() {};
        void setChildText(QString name)
        {
        this->name = name;
        }
    protected:
        void mousePressEvent(QMouseEvent* event);

    };
void MyButton13::mousePressEvent(QMouseEvent* event)
{
     window.resize(500,500);
     label.resize(400,400);
     std::string String_path;
     label.setWordWrap(true);
     label.setAlignment(Qt::AlignTop);
     std::string str= string((const char *)name.toLocal8Bit());
     char a[1000];

     Transform();
     String_path = TSP(str);

     strcpy(a, String_path.c_str());
     cout<<String_path;
     label.setText(QString::fromLocal8Bit(a));
     label.setParent(&window);
     window.show();
}


/**ѡ���յ���¼�*/
class MyButton12 :public QPushButton{
        QString name;
        QWidget window;
        QPushButton button;
    public:
        MyButton12(QString name)
        {
            this->name = name;
        };
        MyButton12() {};
        void setChildText(QString name)
        {
        this->name = name;
        }
    protected:
        void mousePressEvent(QMouseEvent* event);

    };
void MyButton12::mousePressEvent(QMouseEvent* event)
{
     window.resize(200,200);
     std::string str = string((const char *)name.toLocal8Bit());
     strcpy(Data.y , str.c_str());
     button.resize(100,100);
     button.setGeometry(50,50,100,100);
     button.setText(QString::fromLocal8Bit(Data.y/*"ѡ��ɹ���"*/));
     button.setParent(&window);
     window.show();
}
/**ѡ�������¼�**/
class MyButton11 :public QPushButton{
        QString name;
        QWidget window;
        QPushButton button;
    public:
        MyButton11(QString name)
        {
            this->name = name;
        };
        MyButton11() {};
        void setChildText(QString name)
        {
        this->name = name;
        }
    protected:
        void mousePressEvent(QMouseEvent* event);

    };
void MyButton11::mousePressEvent(QMouseEvent* event)
{
    window.resize(200,200);
    std::string str = string((const char *)name.toLocal8Bit());
    strcpy(Data.x, str.c_str());
    button.resize(100,100);
    button.setGeometry(50,50,100,100);
    button.setText(QString::fromLocal8Bit(/*"ѡ��ɹ�!"*/Data.x));
    button.setParent(&window);
    window.show();
}



/**���ܸ����������Ϣ�İ�ť**/
class MyButton : public QPushButton
{
    QWidget window;
    QString name;
    QLabel titleLabel;
    QLabel imageLabel;
    QLabel desLabel;
    QPixmap p;
public:
    MyButton(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
    void mousePressEvent(QMouseEvent* event);
};
void MyButton::mousePressEvent(QMouseEvent *event)
{
    window.resize(600,600);
    graph node = readXml();
    std::string str = string((const char *)name.toLocal8Bit());
    titleLabel.resize(100, 20);
    titleLabel.setGeometry(280,10,100,20);
    titleLabel.setText(name);
    //desLabel.setGeometry(QRect(328, 240, 329, 27*4));  //�ı��о�
    desLabel.setWordWrap(true);
    desLabel.setAlignment(Qt::AlignTop);
    desLabel.setGeometry(175,470,300,200);
    titleLabel.setParent(&window);
    for(int i=1;i<=node.length;i++)
    {
        if(str==node.V[i].name)
        {
         //QString str1 = QString::fromStdString(node.V[i].introduction);
         desLabel.setText(QString::fromLocal8Bit(node.V[i].introduction));
        }
    }
    desLabel.setParent(&window);
    if(str=="����")
    {
        p.load("img/1.jpg");
    }
    else if(str=="�Ĳ�")
    {
        p.load("img/2.jpg");
    }
    else if(str=="15��")
    {
        p.load("img/3.jpg");
    }
    else if(str=="УҽԺ")
    {
        p.load("img/4.jpg");
    }
    else if(str=="21������")
    {
        p.load("img/5.jpg");
    }
    else if(str=="13������")
    {
        p.load("img/6.jpg");
    }
    else if(str=="ѧ����Ԣ")
    {
        p.load("img/7.jpg");
    }
    else if(str=="����")
    {
        p.load("img/8.jpg");
    }
    else if(str=="����")
    {
        p.load("img/9.jpg");
    }
    else if(str=="ũ��")
    {
        p.load("img/10.jpg");
    }
    else if(str=="��ѧ����������")
    {
        p.load("img/11.jpg");
    }
    else if(str=="ԡ��")
    {
        p.load("img/12.jpg");
    }
    else if(str=="���³���")
    {
        p.load("img/13.jpg");
    }
    else if(str=="���")
    {
        p.load("img/14.jpg");
    }
    else if(str=="��º�")
    {
        p.load("img/15.jpg");
    }
    else if(str=="10��")
    {
        p.load("img/16.jpg");
    }
    else if(str=="8��")
    {
        p.load("img/17.jpg");
    }
    else if(str=="9��")
    {
        p.load("img/18.jpg");
    }
    else if(str=="11��")
    {
        p.load("img/19.jpg");
    }
    else if(str=="6��")
    {
        p.load("img/20.jpg");
    }
    else if(str=="����")
    {
        p.load("img/21.jpg");
    }
    else if(str=="����")
    {
        p.load("img/22.jpg");
    }
    else if(str=="ɽ��")
    {
        p.load("img/23.jpg");
    }
    else if(str=="����԰")
    {
        p.load("img/24.jpg");
    }
    else if(str=="����")
    {
        p.load("img/25.jpg");
    }
    else if(str=="����")
    {
        p.load("img/26.jpg");
    }
    else if(str=="У��")
    {
        p.load("img/27.jpg");
    }
    else if(str=="ʳ��")
    {
        p.load("img/28.jpg");
    }
    else if(str=="5��ʵ��")
    {
        p.load("img/29.jpg");
    }
    else if(str=="4��ʵ��")
    {
        p.load("img/30.jpg");
    }
    else if(str=="����ʵ��")
    {
        p.load("img/31.jpg");
    }
    else if(str=="��ͨʵ��")
    {
        p.load("img/32.jpg");
    }
    else if(str=="13��")
    {
        p.load("img/33.jpg");
    }
    else if(str=="12��")
    {
        p.load("img/34.jpg");
    }
    else if(str=="5��")
    {
        p.load("img/35.jpg");
    }
    else if(str=="ͼ���")
    {
        p.load("img/36.jpg");
    }
    else if(str=="4��")
    {
        p.load("img/37.jpg");
    }
    else if(str=="2��")
    {
        p.load("img/38.jpg");
    }
    else if(str=="��԰")
    {
        p.load("img/39.jpg");
    }
    else if(str=="��Ϣ¥")
    {
        p.load("img/40.jpg");
    }
    else if(str=="����")
    {
        p.load("img/41.jpg");
    }
    else if(str=="1��ʵ��")
    {
        p.load("img/42.jpg");
    }
    else if(str=="��Զ¥")
    {
        p.load("img/43.jpg");
    }
    else if(str=="1�Ź�Ԣ")
    {
        p.load("img/44.jpg");
    }
    else if(str=="4�Ź�Ԣ")
    {
        p.load("img/45.jpg");
    }
    else if(str=="2�Ź�Ԣ")
    {
        p.load("img/46.jpg");
    }
    else if(str=="2��")
    {
        p.load("img/47.jpg");
    }
    else if(str=="1��")
    {
        p.load("img/48.jpg");
    }
    else if(str=="һ��")
    {
        p.load("img/49.jpg");
    }
    else if(str=="2��")
    {
        p.load("img/50.jpg");
    }
    else if(str=="1��")
    {
        p.load("img/51.jpg");
    }
    else if(str=="����")
    {
        p.load("img/52.jpg");
    }
    imageLabel.resize(400,350);
    imageLabel.setPixmap(p);
    imageLabel.setGeometry(100,50,400,350);
    imageLabel.setParent(&window);
    window.show();
}




/**ѡ�����İ�ť**/
class MyButton1 : public QPushButton
{
public :
    QString name;
    QWidget window;


    MyButton11 button1;
    MyButton11 button2;
    MyButton11 button3;
    MyButton11 button4;
    MyButton11 button5;
    MyButton11 button6;
    MyButton11 button7;
    MyButton11 button8;
    MyButton11 button9;
    MyButton11 button10;
    MyButton11 button11;
    MyButton11 button12;
    MyButton11 button13;
    MyButton11 button14;
    MyButton11 button15;
    MyButton11 button16;
    MyButton11 button17;
    MyButton11 button18;
    MyButton11 button19;
    MyButton11 button20;
    MyButton11 button21;
    MyButton11 button22;
    MyButton11 button23;
    MyButton11 button24;
    MyButton11 button25;
    MyButton11 button26;
    MyButton11 button27;
    MyButton11 button28;
    MyButton11 button29;
    MyButton11 button30;
    MyButton11 button31;
    MyButton11 button32;
    MyButton11 button33;
    MyButton11 button34;
    MyButton11 button35;
    MyButton11 button36;
    MyButton11 button37;
    MyButton11 button38;
    MyButton11 button39;
    MyButton11 button40;
    MyButton11 button41;
    MyButton11 button42;
    MyButton11 button43;
    MyButton11 button44;
    MyButton11 button45;
    MyButton11 button46;
    MyButton11 button47;
    MyButton11 button48;
    MyButton11 button49;
    MyButton11 button50;
    MyButton11 button51;
    MyButton11 button52;

    MyButton1(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton1::mousePressEvent(QMouseEvent* event)
{
     window.resize(600,600);
     button1.setText(QString::fromLocal8Bit("����"));
     button1.setChildText(QString::fromLocal8Bit("����"));
     button1.resize(100,30);
     button1.setGeometry(0,0,100,30);
     button1.setParent(&window);

     button2.setText(QString::fromLocal8Bit("�Ĳ�"));
     button2.setChildText(QString::fromLocal8Bit("�Ĳ�"));
     button2.resize(100,30);
     button2.setGeometry(0,30,100,30);
     button2.setParent(&window);

     button3.setText(QString::fromLocal8Bit("15��"));
     button3.setChildText(QString::fromLocal8Bit("15��"));
     button3.resize(100,30);
     button3.setGeometry(0,60,100,30);
     button3.setParent(&window);

     button4.setText(QString::fromLocal8Bit("УҽԺ"));
     button4.setChildText(QString::fromLocal8Bit("УҽԺ"));
     button4.resize(100,30);
     button4.setGeometry(0,90,100,30);
     button4.setParent(&window);

     button5.setText(QString::fromLocal8Bit("21������"));
     button5.setChildText(QString::fromLocal8Bit("21������"));
     button5.resize(100,30);
     button5.setGeometry(0,120,100,30);
     button5.setParent(&window);


     button6.setText(QString::fromLocal8Bit("13������"));
     button6.setChildText(QString::fromLocal8Bit("13������"));
     button6.resize(100,30);
     button6.setGeometry(0,150,100,30);
     button6.setParent(&window);

     button7.setText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.setChildText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.resize(100,30);
     button7.setGeometry(0,180,100,30);
     button7.setParent(&window);

     button8.setText(QString::fromLocal8Bit("����"));
     button8.setChildText(QString::fromLocal8Bit("����"));
     button8.resize(100,30);
     button8.setGeometry(0,210,100,30);
     button8.setParent(&window);

     button9.setText(QString::fromLocal8Bit("����"));
     button9.setChildText(QString::fromLocal8Bit("����"));
     button9.resize(100,30);
     button9.setGeometry(0,240,100,30);
     button9.setParent(&window);

     button10.setText(QString::fromLocal8Bit("ũ��"));
     button10.setChildText(QString::fromLocal8Bit("ũ��"));
     button10.resize(100,30);
     button10.setGeometry(0,270,100,30);
     button10.setParent(&window);

     button11.setText(QString::fromLocal8Bit("��ѧ����������"));
     button11.setChildText(QString::fromLocal8Bit("��ѧ����������"));
     button11.resize(100,30);
     button11.setGeometry(0,300,100,30);
     button11.setParent(&window);

     button12.setText(QString::fromLocal8Bit("ԡ��"));
     button12.setChildText(QString::fromLocal8Bit("ԡ��"));
     button12.resize(100,30);
     button12.setGeometry(0,330,100,30);
     button12.setParent(&window);

     button13.setText(QString::fromLocal8Bit("���³���"));
     button13.setChildText(QString::fromLocal8Bit("���³���"));
     button13.resize(100,30);
     button13.setGeometry(0,360,100,30);
     button13.setParent(&window);

     button14.setText(QString::fromLocal8Bit("���"));
     button14.setChildText(QString::fromLocal8Bit("���"));
     button14.resize(100,30);
     button14.setGeometry(0,390,100,30);
     button14.setParent(&window);

     button15.setText(QString::fromLocal8Bit("��º�"));
     button15.setChildText(QString::fromLocal8Bit("��º�"));
     button15.resize(100,30);
     button15.setGeometry(0,420,100,30);
     button15.setParent(&window);

     button16.setText(QString::fromLocal8Bit("10��"));
     button16.setChildText(QString::fromLocal8Bit("10��"));
     button16.resize(100,30);
     button16.setGeometry(0,450,100,30);
     button16.setParent(&window);

     button17.setText(QString::fromLocal8Bit("8��"));
     button17.setChildText(QString::fromLocal8Bit("8��"));
     button17.resize(100,30);
     button17.setGeometry(0,480,100,30);
     button17.setParent(&window);

     button18.setText(QString::fromLocal8Bit("9��"));
     button18.setChildText(QString::fromLocal8Bit("9��"));
     button18.resize(100,30);
     button18.setGeometry(0,510,100,30);
     button18.setParent(&window);

     button19.setText(QString::fromLocal8Bit("11��"));
     button19.setChildText(QString::fromLocal8Bit("11��"));
     button19.resize(100,30);
     button19.setGeometry(0,540,100,30);
     button19.setParent(&window);

     button20.setText(QString::fromLocal8Bit("6��"));
     button20.setChildText(QString::fromLocal8Bit("6��"));
     button20.resize(100,30);
     button20.setGeometry(0,570,100,30);
     button20.setParent(&window);

     button21.setText(QString::fromLocal8Bit("����"));
     button21.setChildText(QString::fromLocal8Bit("����"));
     button21.resize(100,30);
     button21.setGeometry(100,0,100,30);
     button21.setParent(&window);

     button22.setText(QString::fromLocal8Bit("����"));
     button22.setChildText(QString::fromLocal8Bit("����"));
     button22.resize(100,30);
     button22.setGeometry(100,30,100,30);
     button22.setParent(&window);

     button23.setText(QString::fromLocal8Bit("ɽ��"));
     button23.setChildText(QString::fromLocal8Bit("ɽ��"));
     button23.resize(100,30);
     button23.setGeometry(100,60,100,30);
     button23.setParent(&window);

     button24.setText(QString::fromLocal8Bit("����԰"));
     button24.setChildText(QString::fromLocal8Bit("����԰"));
     button24.resize(100,30);
     button24.setGeometry(100,90,100,30);
     button24.setParent(&window);

     button25.setText(QString::fromLocal8Bit("����"));
     button25.setChildText(QString::fromLocal8Bit("����"));
     button25.resize(100,30);
     button25.setGeometry(100,120,100,30);
     button25.setParent(&window);

     button26.setText(QString::fromLocal8Bit("����"));
     button26.setChildText(QString::fromLocal8Bit("����"));
     button26.resize(100,30);
     button26.setGeometry(100,150,100,30);
     button26.setParent(&window);

     button27.setText(QString::fromLocal8Bit("У��"));
     button27.setChildText(QString::fromLocal8Bit("У��"));
     button27.resize(100,30);
     button27.setGeometry(100,180,100,30);
     button27.setParent(&window);

     button28.setText(QString::fromLocal8Bit("ʳ��"));
     button28.setChildText(QString::fromLocal8Bit("ʳ��"));
     button28.resize(100,30);
     button28.setGeometry(100,210,100,30);
     button28.setParent(&window);

     button29.setText(QString::fromLocal8Bit("5��ʵ��"));
     button29.setChildText(QString::fromLocal8Bit("5��ʵ��"));
     button29.resize(100,30);
     button29.setGeometry(100,240,100,30);
     button29.setParent(&window);

     button30.setText(QString::fromLocal8Bit("4��ʵ��"));
     button30.setChildText(QString::fromLocal8Bit("4��ʵ��"));
     button30.resize(100,30);
     button30.setGeometry(100,270,100,30);
     button30.setParent(&window);

     button31.setText(QString::fromLocal8Bit("����ʵ��"));
     button31.setChildText(QString::fromLocal8Bit("����ʵ��"));
     button31.resize(100,30);
     button31.setGeometry(100,300,100,30);
     button31.setParent(&window);

     button32.setText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.setChildText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.resize(100,30);
     button32.setGeometry(100,330,100,30);
     button32.setParent(&window);

     button33.setText(QString::fromLocal8Bit("13��"));
     button33.setChildText(QString::fromLocal8Bit("13��"));
     button33.resize(100,30);
     button33.setGeometry(100,360,100,30);
     button33.setParent(&window);

     button34.setText(QString::fromLocal8Bit("12��"));
     button34.setChildText(QString::fromLocal8Bit("12��"));
     button34.resize(100,30);
     button34.setGeometry(100,390,100,30);
     button34.setParent(&window);

     button35.setText(QString::fromLocal8Bit("5��"));
     button35.setChildText(QString::fromLocal8Bit("5��"));
     button35.resize(100,30);
     button35.setGeometry(100,420,100,30);
     button35.setParent(&window);

     button36.setText(QString::fromLocal8Bit("ͼ���"));
     button36.setChildText(QString::fromLocal8Bit("ͼ���"));
     button36.resize(100,30);
     button36.setGeometry(100,450,100,30);
     button36.setParent(&window);

     button37.setText(QString::fromLocal8Bit("4��"));
     button37.setChildText(QString::fromLocal8Bit("4��"));
     button37.resize(100,30);
     button37.setGeometry(100,480,100,30);
     button37.setParent(&window);

     button38.setText(QString::fromLocal8Bit("2��"));
     button38.setChildText(QString::fromLocal8Bit("2��"));
     button38.resize(100,30);
     button38.setGeometry(100,510,100,30);
     button38.setParent(&window);

     button39.setText(QString::fromLocal8Bit("��԰"));
     button39.setChildText(QString::fromLocal8Bit("��԰"));
     button39.resize(100,30);
     button39.setGeometry(100,540,100,30);
     button39.setParent(&window);

     button40.setText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.setChildText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.resize(100,30);
     button40.setGeometry(100,570,100,30);
     button40.setParent(&window);

     button41.setText(QString::fromLocal8Bit("����"));
     button41.setChildText(QString::fromLocal8Bit("����"));
     button41.resize(100,30);
     button41.setGeometry(100,570,100,30);
     button41.setParent(&window);

     button42.setText(QString::fromLocal8Bit("1��ʵ��"));
     button42.setChildText(QString::fromLocal8Bit("1��ʵ��"));
     button42.resize(100,30);
     button42.setGeometry(200,0,100,30);
     button42.setParent(&window);

     button43.setText(QString::fromLocal8Bit("��Զ¥"));
     button43.setChildText(QString::fromLocal8Bit("��Զ¥"));
     button43.resize(100,30);
     button43.setGeometry(200,30,100,30);
     button43.setParent(&window);

     button44.setText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.setChildText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.resize(100,30);
     button44.setGeometry(200,60,100,30);
     button44.setParent(&window);

     button45.setText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.setChildText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.resize(100,30);
     button45.setGeometry(200,90,100,30);
     button45.setParent(&window);

     button46.setText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.setChildText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.resize(100,30);
     button46.setGeometry(200,120,100,30);
     button46.setParent(&window);

     button47.setText(QString::fromLocal8Bit("2��"));
     button47.setChildText(QString::fromLocal8Bit("2��"));
     button47.resize(100,30);
     button47.setGeometry(200,150,100,30);
     button47.setParent(&window);

     button48.setText(QString::fromLocal8Bit("1��"));
     button48.setChildText(QString::fromLocal8Bit("1��"));
     button48.resize(100,30);
     button48.setGeometry(200,180,100,30);
     button48.setParent(&window);

     button49.setText(QString::fromLocal8Bit("һ��"));
     button49.setChildText(QString::fromLocal8Bit("һ��"));
     button49.resize(100,30);
     button49.setGeometry(200,210,100,30);
     button49.setParent(&window);

     button50.setText(QString::fromLocal8Bit("2��"));
     button50.setChildText(QString::fromLocal8Bit("2��"));
     button50.resize(100,30);
     button50.setGeometry(200,240,100,30);
     button50.setParent(&window);

     button51.setText(QString::fromLocal8Bit("1��"));
     button51.setChildText(QString::fromLocal8Bit("1��"));
     button51.resize(100,30);
     button51.setGeometry(200,270,100,30);
     button51.setParent(&window);

     button52.setText(QString::fromLocal8Bit("����"));
     button52.setChildText(QString::fromLocal8Bit("����"));
     button52.resize(100,30);
     button52.setGeometry(200,300,100,30);
     button52.setParent(&window);

     window.show();
}


/**ѡ���յ�İ�ť*/
class MyButton2 : public QPushButton
{
public :
    QString name;
    QWidget window;
    MyButton12 button1;
    MyButton12 button2;
    MyButton12 button3;
    MyButton12 button4;
    MyButton12 button5;
    MyButton12 button6;
    MyButton12 button7;
    MyButton12 button8;
    MyButton12 button9;
    MyButton12 button10;
    MyButton12 button11;
    MyButton12 button12;
    MyButton12 button13;
    MyButton12 button14;
    MyButton12 button15;
    MyButton12 button16;
    MyButton12 button17;
    MyButton12 button18;
    MyButton12 button19;
    MyButton12 button20;
    MyButton12 button21;
    MyButton12 button22;
    MyButton12 button23;
    MyButton12 button24;
    MyButton12 button25;
    MyButton12 button26;
    MyButton12 button27;
    MyButton12 button28;
    MyButton12 button29;
    MyButton12 button30;
    MyButton12 button31;
    MyButton12 button32;
    MyButton12 button33;
    MyButton12 button34;
    MyButton12 button35;
    MyButton12 button36;
    MyButton12 button37;
    MyButton12 button38;
    MyButton12 button39;
    MyButton12 button40;
    MyButton12 button41;
    MyButton12 button42;
    MyButton12 button43;
    MyButton12 button44;
    MyButton12 button45;
    MyButton12 button46;
    MyButton12 button47;
    MyButton12 button48;
    MyButton12 button49;
    MyButton12 button50;
    MyButton12 button51;
    MyButton12 button52;

    MyButton2(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};

void MyButton2::mousePressEvent(QMouseEvent* event)
{
     window.resize(600,600);
     button1.setText(QString::fromLocal8Bit("����"));
     button1.setChildText(QString::fromLocal8Bit("����"));
     button1.resize(100,30);
     button1.setGeometry(0,0,100,30);
     button1.setParent(&window);

     button2.setText(QString::fromLocal8Bit("�Ĳ�"));
     button2.setChildText(QString::fromLocal8Bit("�Ĳ�"));
     button2.resize(100,30);
     button2.setGeometry(0,30,100,30);
     button2.setParent(&window);

     button3.setText(QString::fromLocal8Bit("15��"));
     button3.setChildText(QString::fromLocal8Bit("15��"));
     button3.resize(100,30);
     button3.setGeometry(0,60,100,30);
     button3.setParent(&window);

     button4.setText(QString::fromLocal8Bit("УҽԺ"));
     button4.setChildText(QString::fromLocal8Bit("УҽԺ"));
     button4.resize(100,30);
     button4.setGeometry(0,90,100,30);
     button4.setParent(&window);

     button5.setText(QString::fromLocal8Bit("21������"));
     button5.setChildText(QString::fromLocal8Bit("21������"));
     button5.resize(100,30);
     button5.setGeometry(0,120,100,30);
     button5.setParent(&window);


     button6.setText(QString::fromLocal8Bit("13������"));
     button6.setChildText(QString::fromLocal8Bit("13������"));
     button6.resize(100,30);
     button6.setGeometry(0,150,100,30);
     button6.setParent(&window);

     button7.setText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.setChildText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.resize(100,30);
     button7.setGeometry(0,180,100,30);
     button7.setParent(&window);

     button8.setText(QString::fromLocal8Bit("����"));
     button8.setChildText(QString::fromLocal8Bit("����"));
     button8.resize(100,30);
     button8.setGeometry(0,210,100,30);
     button8.setParent(&window);

     button9.setText(QString::fromLocal8Bit("����"));
     button9.setChildText(QString::fromLocal8Bit("����"));
     button9.resize(100,30);
     button9.setGeometry(0,240,100,30);
     button9.setParent(&window);

     button10.setText(QString::fromLocal8Bit("ũ��"));
     button10.setChildText(QString::fromLocal8Bit("ũ��"));
     button10.resize(100,30);
     button10.setGeometry(0,270,100,30);
     button10.setParent(&window);

     button11.setText(QString::fromLocal8Bit("��ѧ����������"));
     button11.setChildText(QString::fromLocal8Bit("��ѧ����������"));
     button11.resize(100,30);
     button11.setGeometry(0,300,100,30);
     button11.setParent(&window);

     button12.setText(QString::fromLocal8Bit("ԡ��"));
     button12.setChildText(QString::fromLocal8Bit("ԡ��"));
     button12.resize(100,30);
     button12.setGeometry(0,330,100,30);
     button12.setParent(&window);

     button13.setText(QString::fromLocal8Bit("���³���"));
     button13.setChildText(QString::fromLocal8Bit("���³���"));
     button13.resize(100,30);
     button13.setGeometry(0,360,100,30);
     button13.setParent(&window);

     button14.setText(QString::fromLocal8Bit("���"));
     button14.setChildText(QString::fromLocal8Bit("���"));
     button14.resize(100,30);
     button14.setGeometry(0,390,100,30);
     button14.setParent(&window);

     button15.setText(QString::fromLocal8Bit("��º�"));
     button15.setChildText(QString::fromLocal8Bit("��º�"));
     button15.resize(100,30);
     button15.setGeometry(0,420,100,30);
     button15.setParent(&window);

     button16.setText(QString::fromLocal8Bit("10��"));
     button16.setChildText(QString::fromLocal8Bit("10��"));
     button16.resize(100,30);
     button16.setGeometry(0,450,100,30);
     button16.setParent(&window);

     button17.setText(QString::fromLocal8Bit("8��"));
     button17.setChildText(QString::fromLocal8Bit("8��"));
     button17.resize(100,30);
     button17.setGeometry(0,480,100,30);
     button17.setParent(&window);

     button18.setText(QString::fromLocal8Bit("9��"));
     button18.setChildText(QString::fromLocal8Bit("9��"));
     button18.resize(100,30);
     button18.setGeometry(0,510,100,30);
     button18.setParent(&window);

     button19.setText(QString::fromLocal8Bit("11��"));
     button19.setChildText(QString::fromLocal8Bit("11��"));
     button19.resize(100,30);
     button19.setGeometry(0,540,100,30);
     button19.setParent(&window);

     button20.setText(QString::fromLocal8Bit("6��"));
     button20.setChildText(QString::fromLocal8Bit("6��"));
     button20.resize(100,30);
     button20.setGeometry(0,570,100,30);
     button20.setParent(&window);

     button21.setText(QString::fromLocal8Bit("����"));
     button21.setChildText(QString::fromLocal8Bit("����"));
     button21.resize(100,30);
     button21.setGeometry(100,0,100,30);
     button21.setParent(&window);

     button22.setText(QString::fromLocal8Bit("����"));
     button22.setChildText(QString::fromLocal8Bit("����"));
     button22.resize(100,30);
     button22.setGeometry(100,30,100,30);
     button22.setParent(&window);

     button23.setText(QString::fromLocal8Bit("ɽ��"));
     button23.setChildText(QString::fromLocal8Bit("ɽ��"));
     button23.resize(100,30);
     button23.setGeometry(100,60,100,30);
     button23.setParent(&window);

     button24.setText(QString::fromLocal8Bit("����԰"));
     button24.setChildText(QString::fromLocal8Bit("����԰"));
     button24.resize(100,30);
     button24.setGeometry(100,90,100,30);
     button24.setParent(&window);

     button25.setText(QString::fromLocal8Bit("����"));
     button25.setChildText(QString::fromLocal8Bit("����"));
     button25.resize(100,30);
     button25.setGeometry(100,120,100,30);
     button25.setParent(&window);

     button26.setText(QString::fromLocal8Bit("����"));
     button26.setChildText(QString::fromLocal8Bit("����"));
     button26.resize(100,30);
     button26.setGeometry(100,150,100,30);
     button26.setParent(&window);

     button27.setText(QString::fromLocal8Bit("У��"));
     button27.setChildText(QString::fromLocal8Bit("У��"));
     button27.resize(100,30);
     button27.setGeometry(100,180,100,30);
     button27.setParent(&window);

     button28.setText(QString::fromLocal8Bit("ʳ��"));
     button28.setChildText(QString::fromLocal8Bit("ʳ��"));
     button28.resize(100,30);
     button28.setGeometry(100,210,100,30);
     button28.setParent(&window);

     button29.setText(QString::fromLocal8Bit("5��ʵ��"));
     button29.setChildText(QString::fromLocal8Bit("5��ʵ��"));
     button29.resize(100,30);
     button29.setGeometry(100,240,100,30);
     button29.setParent(&window);

     button30.setText(QString::fromLocal8Bit("4��ʵ��"));
     button30.setChildText(QString::fromLocal8Bit("4��ʵ��"));
     button30.resize(100,30);
     button30.setGeometry(100,270,100,30);
     button30.setParent(&window);

     button31.setText(QString::fromLocal8Bit("����ʵ��"));
     button31.setChildText(QString::fromLocal8Bit("����ʵ��"));
     button31.resize(100,30);
     button31.setGeometry(100,300,100,30);
     button31.setParent(&window);

     button32.setText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.setChildText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.resize(100,30);
     button32.setGeometry(100,330,100,30);
     button32.setParent(&window);

     button33.setText(QString::fromLocal8Bit("13��"));
     button33.setChildText(QString::fromLocal8Bit("13��"));
     button33.resize(100,30);
     button33.setGeometry(100,360,100,30);
     button33.setParent(&window);

     button34.setText(QString::fromLocal8Bit("12��"));
     button34.setChildText(QString::fromLocal8Bit("12��"));
     button34.resize(100,30);
     button34.setGeometry(100,390,100,30);
     button34.setParent(&window);

     button35.setText(QString::fromLocal8Bit("5��"));
     button35.setChildText(QString::fromLocal8Bit("5��"));
     button35.resize(100,30);
     button35.setGeometry(100,420,100,30);
     button35.setParent(&window);

     button36.setText(QString::fromLocal8Bit("ͼ���"));
     button36.setChildText(QString::fromLocal8Bit("ͼ���"));
     button36.resize(100,30);
     button36.setGeometry(100,450,100,30);
     button36.setParent(&window);

     button37.setText(QString::fromLocal8Bit("4��"));
     button37.setChildText(QString::fromLocal8Bit("4��"));
     button37.resize(100,30);
     button37.setGeometry(100,480,100,30);
     button37.setParent(&window);

     button38.setText(QString::fromLocal8Bit("2��"));
     button38.setChildText(QString::fromLocal8Bit("2��"));
     button38.resize(100,30);
     button38.setGeometry(100,510,100,30);
     button38.setParent(&window);

     button39.setText(QString::fromLocal8Bit("��԰"));
     button39.setChildText(QString::fromLocal8Bit("��԰"));
     button39.resize(100,30);
     button39.setGeometry(100,540,100,30);
     button39.setParent(&window);

     button40.setText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.setChildText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.resize(100,30);
     button40.setGeometry(100,570,100,30);
     button40.setParent(&window);

     button41.setText(QString::fromLocal8Bit("����"));
     button41.setChildText(QString::fromLocal8Bit("����"));
     button41.resize(100,30);
     button41.setGeometry(100,570,100,30);
     button41.setParent(&window);

     button42.setText(QString::fromLocal8Bit("1��ʵ��"));
     button42.setChildText(QString::fromLocal8Bit("1��ʵ��"));
     button42.resize(100,30);
     button42.setGeometry(200,0,100,30);
     button42.setParent(&window);

     button43.setText(QString::fromLocal8Bit("��Զ¥"));
     button43.setChildText(QString::fromLocal8Bit("��Զ¥"));
     button43.resize(100,30);
     button43.setGeometry(200,30,100,30);
     button43.setParent(&window);

     button44.setText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.setChildText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.resize(100,30);
     button44.setGeometry(200,60,100,30);
     button44.setParent(&window);

     button45.setText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.setChildText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.resize(100,30);
     button45.setGeometry(200,90,100,30);
     button45.setParent(&window);

     button46.setText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.setChildText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.resize(100,30);
     button46.setGeometry(200,120,100,30);
     button46.setParent(&window);

     button47.setText(QString::fromLocal8Bit("2��"));
     button47.setChildText(QString::fromLocal8Bit("2��"));
     button47.resize(100,30);
     button47.setGeometry(200,150,100,30);
     button47.setParent(&window);

     button48.setText(QString::fromLocal8Bit("1��"));
     button48.setChildText(QString::fromLocal8Bit("1��"));
     button48.resize(100,30);
     button48.setGeometry(200,180,100,30);
     button48.setParent(&window);

     button49.setText(QString::fromLocal8Bit("һ��"));
     button49.setChildText(QString::fromLocal8Bit("һ��"));
     button49.resize(100,30);
     button49.setGeometry(200,210,100,30);
     button49.setParent(&window);

     button50.setText(QString::fromLocal8Bit("2��"));
     button50.setChildText(QString::fromLocal8Bit("2��"));
     button50.resize(100,30);
     button50.setGeometry(200,240,100,30);
     button50.setParent(&window);

     button51.setText(QString::fromLocal8Bit("1��"));
     button51.setChildText(QString::fromLocal8Bit("1��"));
     button51.resize(100,30);
     button51.setGeometry(200,270,100,30);
     button51.setParent(&window);

     button52.setText(QString::fromLocal8Bit("����"));
     button52.setChildText(QString::fromLocal8Bit("����"));
     button52.resize(100,30);
     button52.setGeometry(200,300,100,30);
     button52.setParent(&window);

     window.show();
}

/**�߱�У԰�İ�ť*/
class MyButton3 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;

    MyButton13 button1;
    MyButton13 button2;
    MyButton13 button3;
    MyButton13 button4;
    MyButton13 button5;
    MyButton13 button6;
    MyButton13 button7;
    MyButton13 button8;
    MyButton13 button9;
    MyButton13 button10;
    MyButton13 button11;
    MyButton13 button12;
    MyButton13 button13;
    MyButton13 button14;
    MyButton13 button15;
    MyButton13 button16;
    MyButton13 button17;
    MyButton13 button18;
    MyButton13 button19;
    MyButton13 button20;
    MyButton13 button21;
    MyButton13 button22;
    MyButton13 button23;
    MyButton13 button24;
    MyButton13 button25;
    MyButton13 button26;
    MyButton13 button27;
    MyButton13 button28;
    MyButton13 button29;
    MyButton13 button30;
    MyButton13 button31;
    MyButton13 button32;
    MyButton13 button33;
    MyButton13 button34;
    MyButton13 button35;
    MyButton13 button36;
    MyButton13 button37;
    MyButton13 button38;
    MyButton13 button39;
    MyButton13 button40;
    MyButton13 button41;
    MyButton13 button42;
    MyButton13 button43;
    MyButton13 button44;
    MyButton13 button45;
    MyButton13 button46;
    MyButton13 button47;
    MyButton13 button48;
    MyButton13 button49;
    MyButton13 button50;
    MyButton13 button51;
    MyButton13 button52;

    MyButton3(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton3::mousePressEvent(QMouseEvent* event)
{
     window.resize(600,600);
     label.resize(200,200);
     label.setText(QString::fromLocal8Bit("ѡ��������㣬Ϊ��ѡ��һ��\n��̵��߱�У԰��·��"));
     label.setGeometry(350,100,200,200);
     label.setParent(&window);

     button1.setText(QString::fromLocal8Bit("����"));
     button1.setChildText(QString::fromLocal8Bit("����"));
     button1.resize(100,30);
     button1.setGeometry(0,0,100,30);
     button1.setParent(&window);

     button2.setText(QString::fromLocal8Bit("�Ĳ�"));
     button2.setChildText(QString::fromLocal8Bit("�Ĳ�"));
     button2.resize(100,30);
     button2.setGeometry(0,30,100,30);
     button2.setParent(&window);

     button3.setText(QString::fromLocal8Bit("15��"));
     button3.setChildText(QString::fromLocal8Bit("15��"));
     button3.resize(100,30);
     button3.setGeometry(0,60,100,30);
     button3.setParent(&window);

     button4.setText(QString::fromLocal8Bit("УҽԺ"));
     button4.setChildText(QString::fromLocal8Bit("УҽԺ"));
     button4.resize(100,30);
     button4.setGeometry(0,90,100,30);
     button4.setParent(&window);

     button5.setText(QString::fromLocal8Bit("21������"));
     button5.setChildText(QString::fromLocal8Bit("21������"));
     button5.resize(100,30);
     button5.setGeometry(0,120,100,30);
     button5.setParent(&window);


     button6.setText(QString::fromLocal8Bit("13������"));
     button6.setChildText(QString::fromLocal8Bit("13������"));
     button6.resize(100,30);
     button6.setGeometry(0,150,100,30);
     button6.setParent(&window);

     button7.setText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.setChildText(QString::fromLocal8Bit("ѧ����Ԣ"));
     button7.resize(100,30);
     button7.setGeometry(0,180,100,30);
     button7.setParent(&window);

     button8.setText(QString::fromLocal8Bit("����"));
     button8.setChildText(QString::fromLocal8Bit("����"));
     button8.resize(100,30);
     button8.setGeometry(0,210,100,30);
     button8.setParent(&window);

     button9.setText(QString::fromLocal8Bit("����"));
     button9.setChildText(QString::fromLocal8Bit("����"));
     button9.resize(100,30);
     button9.setGeometry(0,240,100,30);
     button9.setParent(&window);

     button10.setText(QString::fromLocal8Bit("ũ��"));
     button10.setChildText(QString::fromLocal8Bit("ũ��"));
     button10.resize(100,30);
     button10.setGeometry(0,270,100,30);
     button10.setParent(&window);

     button11.setText(QString::fromLocal8Bit("��ѧ����������"));
     button11.setChildText(QString::fromLocal8Bit("��ѧ����������"));
     button11.resize(100,30);
     button11.setGeometry(0,300,100,30);
     button11.setParent(&window);

     button12.setText(QString::fromLocal8Bit("ԡ��"));
     button12.setChildText(QString::fromLocal8Bit("ԡ��"));
     button12.resize(100,30);
     button12.setGeometry(0,330,100,30);
     button12.setParent(&window);

     button13.setText(QString::fromLocal8Bit("���³���"));
     button13.setChildText(QString::fromLocal8Bit("���³���"));
     button13.resize(100,30);
     button13.setGeometry(0,360,100,30);
     button13.setParent(&window);

     button14.setText(QString::fromLocal8Bit("���"));
     button14.setChildText(QString::fromLocal8Bit("���"));
     button14.resize(100,30);
     button14.setGeometry(0,390,100,30);
     button14.setParent(&window);

     button15.setText(QString::fromLocal8Bit("��º�"));
     button15.setChildText(QString::fromLocal8Bit("��º�"));
     button15.resize(100,30);
     button15.setGeometry(0,420,100,30);
     button15.setParent(&window);

     button16.setText(QString::fromLocal8Bit("10��"));
     button16.setChildText(QString::fromLocal8Bit("10��"));
     button16.resize(100,30);
     button16.setGeometry(0,450,100,30);
     button16.setParent(&window);

     button17.setText(QString::fromLocal8Bit("8��"));
     button17.setChildText(QString::fromLocal8Bit("8��"));
     button17.resize(100,30);
     button17.setGeometry(0,480,100,30);
     button17.setParent(&window);

     button18.setText(QString::fromLocal8Bit("9��"));
     button18.setChildText(QString::fromLocal8Bit("9��"));
     button18.resize(100,30);
     button18.setGeometry(0,510,100,30);
     button18.setParent(&window);

     button19.setText(QString::fromLocal8Bit("11��"));
     button19.setChildText(QString::fromLocal8Bit("11��"));
     button19.resize(100,30);
     button19.setGeometry(0,540,100,30);
     button19.setParent(&window);

     button20.setText(QString::fromLocal8Bit("6��"));
     button20.setChildText(QString::fromLocal8Bit("6��"));
     button20.resize(100,30);
     button20.setGeometry(0,570,100,30);
     button20.setParent(&window);

     button21.setText(QString::fromLocal8Bit("����"));
     button21.setChildText(QString::fromLocal8Bit("����"));
     button21.resize(100,30);
     button21.setGeometry(100,0,100,30);
     button21.setParent(&window);

     button22.setText(QString::fromLocal8Bit("����"));
     button22.setChildText(QString::fromLocal8Bit("����"));
     button22.resize(100,30);
     button22.setGeometry(100,30,100,30);
     button22.setParent(&window);

     button23.setText(QString::fromLocal8Bit("ɽ��"));
     button23.setChildText(QString::fromLocal8Bit("ɽ��"));
     button23.resize(100,30);
     button23.setGeometry(100,60,100,30);
     button23.setParent(&window);

     button24.setText(QString::fromLocal8Bit("����԰"));
     button24.setChildText(QString::fromLocal8Bit("����԰"));
     button24.resize(100,30);
     button24.setGeometry(100,90,100,30);
     button24.setParent(&window);

     button25.setText(QString::fromLocal8Bit("����"));
     button25.setChildText(QString::fromLocal8Bit("����"));
     button25.resize(100,30);
     button25.setGeometry(100,120,100,30);
     button25.setParent(&window);

     button26.setText(QString::fromLocal8Bit("����"));
     button26.setChildText(QString::fromLocal8Bit("����"));
     button26.resize(100,30);
     button26.setGeometry(100,150,100,30);
     button26.setParent(&window);

     button27.setText(QString::fromLocal8Bit("У��"));
     button27.setChildText(QString::fromLocal8Bit("У��"));
     button27.resize(100,30);
     button27.setGeometry(100,180,100,30);
     button27.setParent(&window);

     button28.setText(QString::fromLocal8Bit("ʳ��"));
     button28.setChildText(QString::fromLocal8Bit("ʳ��"));
     button28.resize(100,30);
     button28.setGeometry(100,210,100,30);
     button28.setParent(&window);

     button29.setText(QString::fromLocal8Bit("5��ʵ��"));
     button29.setChildText(QString::fromLocal8Bit("5��ʵ��"));
     button29.resize(100,30);
     button29.setGeometry(100,240,100,30);
     button29.setParent(&window);

     button30.setText(QString::fromLocal8Bit("4��ʵ��"));
     button30.setChildText(QString::fromLocal8Bit("4��ʵ��"));
     button30.resize(100,30);
     button30.setGeometry(100,270,100,30);
     button30.setParent(&window);

     button31.setText(QString::fromLocal8Bit("����ʵ��"));
     button31.setChildText(QString::fromLocal8Bit("����ʵ��"));
     button31.resize(100,30);
     button31.setGeometry(100,300,100,30);
     button31.setParent(&window);

     button32.setText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.setChildText(QString::fromLocal8Bit("��ͨʵ��"));
     button32.resize(100,30);
     button32.setGeometry(100,330,100,30);
     button32.setParent(&window);

     button33.setText(QString::fromLocal8Bit("13��"));
     button33.setChildText(QString::fromLocal8Bit("13��"));
     button33.resize(100,30);
     button33.setGeometry(100,360,100,30);
     button33.setParent(&window);

     button34.setText(QString::fromLocal8Bit("12��"));
     button34.setChildText(QString::fromLocal8Bit("12��"));
     button34.resize(100,30);
     button34.setGeometry(100,390,100,30);
     button34.setParent(&window);

     button35.setText(QString::fromLocal8Bit("5��"));
     button35.setChildText(QString::fromLocal8Bit("5��"));
     button35.resize(100,30);
     button35.setGeometry(100,420,100,30);
     button35.setParent(&window);

     button36.setText(QString::fromLocal8Bit("ͼ���"));
     button36.setChildText(QString::fromLocal8Bit("ͼ���"));
     button36.resize(100,30);
     button36.setGeometry(100,450,100,30);
     button36.setParent(&window);

     button37.setText(QString::fromLocal8Bit("4��"));
     button37.setChildText(QString::fromLocal8Bit("4��"));
     button37.resize(100,30);
     button37.setGeometry(100,480,100,30);
     button37.setParent(&window);

     button38.setText(QString::fromLocal8Bit("2��"));
     button38.setChildText(QString::fromLocal8Bit("2��"));
     button38.resize(100,30);
     button38.setGeometry(100,510,100,30);
     button38.setParent(&window);

     button39.setText(QString::fromLocal8Bit("��԰"));
     button39.setChildText(QString::fromLocal8Bit("��԰"));
     button39.resize(100,30);
     button39.setGeometry(100,540,100,30);
     button39.setParent(&window);

     button40.setText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.setChildText(QString::fromLocal8Bit("��Ϣ¥"));
     button40.resize(100,30);
     button40.setGeometry(100,570,100,30);
     button40.setParent(&window);

     button41.setText(QString::fromLocal8Bit("����"));
     button41.setChildText(QString::fromLocal8Bit("����"));
     button41.resize(100,30);
     button41.setGeometry(100,570,100,30);
     button41.setParent(&window);

     button42.setText(QString::fromLocal8Bit("1��ʵ��"));
     button42.setChildText(QString::fromLocal8Bit("1��ʵ��"));
     button42.resize(100,30);
     button42.setGeometry(200,0,100,30);
     button42.setParent(&window);

     button43.setText(QString::fromLocal8Bit("��Զ¥"));
     button43.setChildText(QString::fromLocal8Bit("��Զ¥"));
     button43.resize(100,30);
     button43.setGeometry(200,30,100,30);
     button43.setParent(&window);

     button44.setText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.setChildText(QString::fromLocal8Bit("1�Ź�Ԣ"));
     button44.resize(100,30);
     button44.setGeometry(200,60,100,30);
     button44.setParent(&window);

     button45.setText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.setChildText(QString::fromLocal8Bit("4�Ź�Ԣ"));
     button45.resize(100,30);
     button45.setGeometry(200,90,100,30);
     button45.setParent(&window);

     button46.setText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.setChildText(QString::fromLocal8Bit("2�Ź�Ԣ"));
     button46.resize(100,30);
     button46.setGeometry(200,120,100,30);
     button46.setParent(&window);

     button47.setText(QString::fromLocal8Bit("2��"));
     button47.setChildText(QString::fromLocal8Bit("2��"));
     button47.resize(100,30);
     button47.setGeometry(200,150,100,30);
     button47.setParent(&window);

     button48.setText(QString::fromLocal8Bit("1��"));
     button48.setChildText(QString::fromLocal8Bit("1��"));
     button48.resize(100,30);
     button48.setGeometry(200,180,100,30);
     button48.setParent(&window);

     button49.setText(QString::fromLocal8Bit("һ��"));
     button49.setChildText(QString::fromLocal8Bit("һ��"));
     button49.resize(100,30);
     button49.setGeometry(200,210,100,30);
     button49.setParent(&window);

     button50.setText(QString::fromLocal8Bit("2��"));
     button50.setChildText(QString::fromLocal8Bit("2��"));
     button50.resize(100,30);
     button50.setGeometry(200,240,100,30);
     button50.setParent(&window);

     button51.setText(QString::fromLocal8Bit("1��"));
     button51.setChildText(QString::fromLocal8Bit("1��"));
     button51.resize(100,30);
     button51.setGeometry(200,270,100,30);
     button51.setParent(&window);

     button52.setText(QString::fromLocal8Bit("����"));
     button52.setChildText(QString::fromLocal8Bit("����"));
     button52.resize(100,30);
     button52.setGeometry(200,300,100,30);
     button52.setParent(&window);

     window.show();
}



/**��ӡ�����Ƶ����Ϣ*/
class MyButton4 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton4(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton4::mousePressEvent(QMouseEvent* event)
{
    //label.setText("");
    window.resize(700,700);
    label.resize(500,500);
    label.setGeometry(0,0,500,500);
    label.setWordWrap(true);
    label.setAlignment(Qt::AlignTop);
    /*std::string str[100];
    str[1] = "15��";
    Transform();
    std::string String_path = Init_limit_dijksta(0,4,1,str);
    for(int i=0;i<=index-1;i++)
    {
        cout<<limit[i]<<endl;
    }*/
    ifstream in("obj\\TXT.txt");
     string O,O1;
     while(!in.eof())
     {
         getline(in,O);
         O1+=O;
         O1+="\n";
     }
     cout<<O1<<endl;
     in.close();
     string String_path=O1;
    //String_path = Init_limit_dijksta(x,y,index,limit);
    //index = 0;
    String_path = "Ϊ����ӡ���е�·����\n"+String_path;
    cout<<String_path<<endl;
    //cout<<x<<" "<<y<<endl;
    char a[10000];
    strcpy(a, String_path.c_str());
    label.setText(QString::fromLocal8Bit(a));
    //cout<<String_path<<endl;
    //std::string String_path;

    //QString path1 = QString::fromStdString(path);

    //desLabel.setText(QString::fromLocal8Bit(node.V[i].introduction));
    //label.setText(path1);
    label.setParent(&window);
    window.show();
}



/**�����ӡ�����Ƶ���Ϣ**/
class MyButton7 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton7(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton7::mousePressEvent(QMouseEvent* event)
{
    //label.setText("");
    window.resize(700,700);
    label.resize(500,500);
    label.setWordWrap(true);
    label.setAlignment(Qt::AlignTop);
    /*std::string str[100];
    str[1] = "15��";
    Transform();
    std::string String_path = Init_limit_dijksta(0,4,1,str);
    for(int i=0;i<=index-1;i++)
    {
        cout<<limit[i]<<endl;
    }*/
    Transform();
    int x = Transform2(Data.x);
    int y = Transform2(Data.y);

    string String_path;
    //string Exm[maxn];
    String_path = Init_limit_dijksta(x,y,index,limit);
    index = 0;
    cout<<String_path<<endl;
    cout<<x<<" "<<y<<endl;
    char a[10000];
    strcpy(a, String_path.c_str());
    label.setText(QString::fromLocal8Bit(a));
    //cout<<String_path<<endl;
    //std::string String_path;

    //QString path1 = QString::fromStdString(path);

    //desLabel.setText(QString::fromLocal8Bit(node.V[i].introduction));
    //label.setText(path1);
    label.setParent(&window);
    window.show();
}







class MyButton5 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton5(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton5::mousePressEvent(QMouseEvent* event)
{
    window.resize(100,120);
     MyButton1 *button1 = new MyButton1(QString::fromLocal8Bit("ѡ�����"));
     button1->setGeometry(0,0,100,30);
     button1->setParent(&window);

     MyButton2 *button2 = new MyButton2(QString::fromLocal8Bit("ѡ���յ�"));
     button2->setGeometry(0,30,100,30);
     button2->setParent(&window);

     MyButton17 *button17 = new MyButton17(QString::fromLocal8Bit("���ƾ���"));
     button17->setGeometry(0,60,100,30);
     button17->setParent(&window);
     //MyButton2 button2(QString::fromLocal8Bit("ѡ���յ�"));
     MyButton7 *button7 = new MyButton7(QString::fromLocal8Bit("��ӡ��Ϣ"));
     button7->setGeometry(0,90,100,30);
     button7->setParent(&window);

    window.show();
}


/**��Ҫ����*/
class MyButton6 : public QPushButton
{
    public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton6(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton6::mousePressEvent(QMouseEvent* event)
{
     window.resize(100,90);
     MyButton1 *button1 = new MyButton1(QString::fromLocal8Bit("ѡ�����"));
     button1->setGeometry(0,0,100,30);
     button1->setParent(&window);

     MyButton2 *button2 = new MyButton2(QString::fromLocal8Bit("ѡ���յ�"));
     button2->setGeometry(0,30,100,30);
     button2->setParent(&window);
     //MyButton2 button2(QString::fromLocal8Bit("ѡ���յ�"));
     MyButton4 *button4 = new MyButton4(QString::fromLocal8Bit("��ӡ��Ϣ"));
     button4->setGeometry(0,60,100,30);
     button4->setParent(&window);
     window.show();
}

/**��ӡ��̺ʹζ�·��Ϣ**/
class MyButton10 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;
    QLabel label2;
    QLabel titleLabel1;
    QLabel titleLabel2;
    MyButton10(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton10::mousePressEvent(QMouseEvent* event)
{
    //label.setText("");
    window.resize(700,700);
    label.resize(700,200);
    label2.resize(700,200);
    label.setWordWrap(true);
    label.setGeometry(50,60,700,200);
    label2.setGeometry(50,400,700,200);
    label.setAlignment(Qt::AlignTop);
    titleLabel1.resize(200,50);
    titleLabel2.resize(200,50);
    titleLabel2.setGeometry(0,300,200,50);
    Transform();
    int x = Transform2(Data.x);
    int y = Transform2(Data.y);
    int Graph[5][5]=
    {
        0,inf,inf,inf,inf,
        inf,0,1,2,3,
        inf,inf,0,1,2,
        inf,inf,inf,0,1
    };
    Find_Kth function1;
    //���Ե���
    string temp= function1.Find_kth(Graph,1,x,y,5);
    cout<<temp<<endl;
    cout<<x<<" "<<y<<endl;
    char a[10000];
    char b[10000];
    strcpy(a, temp.c_str());
    titleLabel2.setText(QString::fromLocal8Bit("�����Ƽ������·�ǣ�"));
    titleLabel1.setText(QString::fromLocal8Bit("�����Ƽ��Ĵζ�·�ǣ�"));

    string String_path1  = Init_dijkstra(x,y);//��1��
    //cout<<String_path<<endl;
    string String_path2 = find_Bike_path(x,y);
    string String_path = String_path1 +"\n\n"+ String_path2;
    strcpy(b, String_path.c_str());
    label2.setText(QString::fromLocal8Bit(b));
    label2.setParent(&window);
    cout<<String_path<<endl;


    label.setText(QString::fromLocal8Bit(a));
    //cout<<String_path<<endl;
    //std::string String_path;

    //QString path1 = QString::fromStdString(path);

    //desLabel.setText(QString::fromLocal8Bit(node.V[i].introduction));
    //label.setText(path1);
    titleLabel1.setParent(&window);
    titleLabel2.setParent(&window);
    label.setParent(&window);
    window.show();
}


/**���·�ʹζ�·*/
class MyButton9 : public QPushButton
{
    public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton9(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton9::mousePressEvent(QMouseEvent* event)
{
     window.resize(100,90);
     MyButton1 *button1 = new MyButton1(QString::fromLocal8Bit("ѡ�����"));
     button1->setGeometry(0,0,100,30);
     button1->setParent(&window);

     MyButton2 *button2 = new MyButton2(QString::fromLocal8Bit("ѡ���յ�"));
     button2->setGeometry(0,30,100,30);
     button2->setParent(&window);
     //MyButton2 button2(QString::fromLocal8Bit("ѡ���յ�"));
     MyButton10 *button10 = new MyButton10(QString::fromLocal8Bit("��ӡ��Ϣ"));
     button10->setGeometry(0,60,100,30);
     button10->setParent(&window);
     window.show();
}

/**�������˰�ť*/
class MyButton8 : public QPushButton
{
    public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton8(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton8::mousePressEvent(QMouseEvent* event)
{
     window.resize(100,90);
     MyButton1 *button1 = new MyButton1(QString::fromLocal8Bit("ѡ�����"));
     button1->setGeometry(0,0,100,30);
     button1->setParent(&window);

     MyButton2 *button2 = new MyButton2(QString::fromLocal8Bit("ѡ���յ�"));
     button2->setGeometry(0,30,100,30);
     button2->setParent(&window);

     MyButton14 *button14 = new MyButton14(QString::fromLocal8Bit("��ӡ��Ϣ"));
     button14->setGeometry(0,60,100,30);
     button14->setParent(&window);
     //MyButton2 button2(QString::fromLocal8Bit("ѡ���յ�"));
     window.show();

}

/**��ӡ����������*/
class MyButton18 : public QPushButton
{
public :
    QString name;
    QWidget window;
    QLabel label;
    MyButton18(QString name):QPushButton(name)
    {
        this->name = name;
    };
protected:
   void mousePressEvent(QMouseEvent* event);
};
void MyButton18::mousePressEvent(QMouseEvent* event)
{
    //label.setText("");
    window.resize(700,700);
    label.resize(500,500);
    label.setGeometry(0,0,500,500);
    label.setWordWrap(true);
    label.setAlignment(Qt::AlignTop);
    /*std::string str[100];
    str[1] = "15��";
    Transform();
    std::string String_path = Init_limit_dijksta(0,4,1,str);
    for(int i=0;i<=index-1;i++)
    {
        cout<<limit[i]<<endl;
    }*/
    Transform();

    /*Bike_info real;
    real.n = 2;
    real.m = 2;
    for(int i=0; i<real.n; i++)
    {
        real.num_n[i] = i+1;
        real.In_id[i] = i+1;
    }
    for(int i=0; i<real.m; i++)
    {
        real.num_m[i] = 2-i;
        real.Out_id[i] = 2-i;
    }
    string String_path = Distribute_plan(real);*/
    Bike_info real;
    real.n = 7;
    real.m = 7;
    for(int i=0; i<real.n; i++)
    {
        real.num_n[i] = i+1;
        real.In_id[i] = i+1;
    }
    for(int i=0; i<real.m; i++)
    {
        real.num_m[i] = 7-i;
        real.Out_id[i] = 8+i;
    }
    string String_path = Distribute_plan(real);
//    cout<<String_path<<endl;
    //int x = Transform2(Data.x);
    //int y = Transform2(Data.y);
    //string String_path;
    //String_path = Bus_road(1,7,1);
    //String_path = Init_Print_all_path(x,y);
    //String_path = Init_limit_dijksta(x,y,index,limit);
    //index = 0;
    String_path = "Ϊ����ӡ���������ȵ���Ϣ��\n"+String_path;
    cout<<String_path<<endl;
    //cout<<x<<" "<<y<<endl;
    char a[10000];
    strcpy(a, String_path.c_str());
    label.setText(QString::fromLocal8Bit(a));
    //cout<<String_path<<endl;
    //std::string String_path;

    //QString path1 = QString::fromStdString(path);

    //desLabel.setText(QString::fromLocal8Bit(node.V[i].introduction));
    //label.setText(path1);
    label.setParent(&window);
    window.show();
}


int main( int argc, char **argv )
{
    //initXml();
    //graph gh = initgraph();
    //writeGraph(gh);
    //writeXml(gh);



    QApplication a( argc, argv );
    QWidget window;
    window.resize(1500,1500);
    window.setWindowTitle(QString::fromLocal8Bit("У԰������ͼ"));
    //����һ����ť
    /*MyButton1 button1(QString::fromLocal8Bit("ѡ�����"));
    //���ð�ť�Ĵ�С��λ��
    button1.setGeometry(10,10,100,30);
    //button1.setMouseTracking(true);
    //QObject::connect(&button1, SIGNAL(clicked()), &button1, SLOT(button1Event()));
    //connect(button1,signal(clicked()),this,singal(anothersignal()));
    //����һ����ť
    MyButton2 button2(QString::fromLocal8Bit("ѡ���յ�"));
    //���ð�ť�Ĵ�С��λ��*/

    MyButton6 button6(QString::fromLocal8Bit("��Ҫ����"));
    button6.setGeometry(10,40,100,30);
    //����һ����ť
    MyButton3 button3(QString::fromLocal8Bit("�߱�У԰"));
    //���ð�ť�Ĵ�С��λ��
    button3.setGeometry(10,70,100,30);

    MyButton5 button5(QString::fromLocal8Bit("���Ʒ���"));
    //���ð�ť�Ĵ�С��λ��
    button5.setGeometry(10,130,100,30);
    button5.setParent(&window);

    MyButton9 button9(QString::fromLocal8Bit("�뵽��ȥ"));
    //���ð�ť�Ĵ�С��λ��
    button9.setGeometry(10,160,100,30);
    button9.setParent(&window);

    MyButton8 button8(QString::fromLocal8Bit("��������"));
    //���ð�ť�Ĵ�С��λ��
    button8.setGeometry(10,190,100,30);
    button8.setParent(&window);


    /*MyButton4 button4(QString::fromLocal8Bit("ɾ����Ϣ"));
    //���ð�ť�Ĵ�С��λ��
    button4.setGeometry(10,130,100,30);
    button4.setParent(&window);*/


    /*MyButton8 button8(QString::fromLocal8Bit("������Ϣ"));
    //���ð�ť�Ĵ�С��λ��
    button8.setGeometry(10,160,100,30);
    button8.setParent(&window);*/

    MyButton18 button18(QString::fromLocal8Bit("��������"));
    //���ð�ť�Ĵ�С��λ��
    //button18.setText(QString::fromLocal8Bit("������"));
    button18.setGeometry(10,100,100,30);
    button18.setParent(&window);




    //���ѧУ�ĵ�ͼ


    MyButton button101(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button101.setGeometry( 270,170,50,50);

    MyButton button102(QString::fromLocal8Bit("�Ĳ�"));
    //���ð�ť�Ĵ�С��λ��
    button102.setGeometry( 350, 125,75,75);

    MyButton button103(QString::fromLocal8Bit("15��"));
    //���ð�ť�Ĵ�С��λ��
    button103.setGeometry(270, 250, 50,50);

    MyButton button104(QString::fromLocal8Bit("УҽԺ"));
    //���ð�ť�Ĵ�С��λ��
    button104.setGeometry(350, 210, 50,30);

    MyButton button105(QString::fromLocal8Bit("21������"));
    //���ð�ť�Ĵ�С��λ��
    button105.setGeometry(350, 90, 100,30);

    MyButton button106(QString::fromLocal8Bit("13������"));
    //���ð�ť�Ĵ�С��λ��
    button106.setGeometry(460, 90, 100,30);

    MyButton button107(QString::fromLocal8Bit("ѧ����Ԣ"));
    //���ð�ť�Ĵ�С��λ��
    button107.setGeometry(570, 90, 100,30);

    MyButton button108(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button108.setGeometry(680, 60, 50,30);

    MyButton button109(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button109.setGeometry(600, 130, 75,75);

    MyButton button110(QString::fromLocal8Bit("ũ��"));
    //���ð�ť�Ĵ�С��λ��
    button110.setGeometry(550, 130, 50,30);

    MyButton button111(QString::fromLocal8Bit("��ѧ����������"));
    //���ð�ť�Ĵ�С��λ��
    button111.setGeometry(480, 200, 100,50);

    MyButton button112(QString::fromLocal8Bit("ԡ��"));
    //���ð�ť�Ĵ�С��λ��
    button112.setGeometry(680, 130, 80,30);

    MyButton button113(QString::fromLocal8Bit("���³���"));
    //���ð�ť�Ĵ�С��λ��
    button113.setGeometry( 680, 160, 80,50);

    MyButton button114(QString::fromLocal8Bit("���"));
    //���ð�ť�Ĵ�С��λ��
    button114.setGeometry(480, 250, 100,50);

    MyButton button115(QString::fromLocal8Bit("��º�"));
    //���ð�ť�Ĵ�С��λ��
    button115.setGeometry( 650, 250, 250,100);

    MyButton button116(QString::fromLocal8Bit("10��"));
    //���ð�ť�Ĵ�С��λ��
    button116.setGeometry(550, 320, 50,50);

    MyButton button117(QString::fromLocal8Bit("8��"));
    //���ð�ť�Ĵ�С��λ��
    button117.setGeometry(550, 380, 50,50);

    MyButton button118(QString::fromLocal8Bit("9��"));
    //���ð�ť�Ĵ�С��λ��
    button118.setGeometry(450, 380, 50,50);

    MyButton button119(QString::fromLocal8Bit("11��"));
    //���ð�ť�Ĵ�С��λ��
    button119.setGeometry( 450, 320, 50,50);

    MyButton button120(QString::fromLocal8Bit("6��"));
    //���ð�ť�Ĵ�С��λ��
    button120.setGeometry(400, 210, 50,50);

    MyButton button121(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button121.setGeometry(350, 270, 100,30);

    MyButton button122(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button122.setGeometry(780, 170, 100,50);

    MyButton button123(QString::fromLocal8Bit("ɽ��"));
    //���ð�ť�Ĵ�С��λ��
    button123.setGeometry(780, 100, 130,50);

    MyButton button124(QString::fromLocal8Bit("����԰"));
    //���ð�ť�Ĵ�С��λ��
    button124.setGeometry(950, 100, 150,300);

    MyButton button125(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button125.setGeometry(1070, 410, 50,30);

    MyButton button126(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button126.setGeometry(150, 410, 50,30);

    MyButton button127(QString::fromLocal8Bit("У��"));
    //���ð�ť�Ĵ�С��λ��
    button127.setGeometry(150, 510, 50,30);

    MyButton button128(QString::fromLocal8Bit("ʳ��"));
    //���ð�ť�Ĵ�С��λ��
    button128.setGeometry(150, 580, 50,30);

    MyButton button129(QString::fromLocal8Bit("5��ʵ��"));
    //���ð�ť�Ĵ�С��λ��
    button129.setGeometry( 200, 460, 80,40);

    MyButton button130(QString::fromLocal8Bit("4��ʵ��"));
    //���ð�ť�Ĵ�С��λ��
    button130.setGeometry(200, 530, 80,40);

    MyButton button131(QString::fromLocal8Bit("����ʵ��"));
    //���ð�ť�Ĵ�С��λ��
    button131.setGeometry(200, 580, 80,40);

    MyButton button132(QString::fromLocal8Bit("��ͨʵ��"));
    //���ð�ť�Ĵ�С��λ��
    button132.setGeometry(200, 680, 80,40);

    MyButton button133(QString::fromLocal8Bit("13��"));
    //���ð�ť�Ĵ�С��λ��
    button133.setGeometry(300, 460, 80,60);

    MyButton button134(QString::fromLocal8Bit("12��"));
    //���ð�ť�Ĵ�С��λ��
    button134.setGeometry(300, 530, 80,60);

    MyButton button135(QString::fromLocal8Bit("5��"));
    //���ð�ť�Ĵ�С��λ��
    button135.setGeometry(450, 460, 50,50);

    MyButton button136(QString::fromLocal8Bit("ͼ���"));
    //���ð�ť�Ĵ�С��λ��
    button136.setGeometry(400, 530, 240,80);

    MyButton button137(QString::fromLocal8Bit("4��"));
    //���ð�ť�Ĵ�С��λ��
    button137.setGeometry(550, 460, 50,50);

    MyButton button138(QString::fromLocal8Bit("2��"));
    //���ð�ť�Ĵ�С��λ��
    button138.setGeometry(650, 460, 100,100);

    MyButton button139(QString::fromLocal8Bit("��԰"));
    //���ð�ť�Ĵ�С��λ��
    button139.setGeometry(760, 460, 50,30);

    MyButton button140(QString::fromLocal8Bit("��Ϣ¥"));
    //���ð�ť�Ĵ�С��λ��
    button140.setGeometry(760, 510, 50,30);

    MyButton button141(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button141.setGeometry(680, 580, 50,50);

    MyButton button142(QString::fromLocal8Bit("1��ʵ��"));
    //���ð�ť�Ĵ�С��λ��
    button142.setGeometry(600, 640, 80,40);

    MyButton button143(QString::fromLocal8Bit("��Զ¥"));
    //���ð�ť�Ĵ�С��λ��
    button143.setGeometry(780, 580, 80,80);

    MyButton button144(QString::fromLocal8Bit("1�Ź�Ԣ"));
    //���ð�ť�Ĵ�С��λ��
    button144.setGeometry(830, 530, 100,30);

    MyButton button145(QString::fromLocal8Bit("4�Ź�Ԣ"));
    //���ð�ť�Ĵ�С��λ��
    button145.setGeometry( 830,500, 100,30);

    MyButton button146(QString::fromLocal8Bit("2�Ź�Ԣ"));
    //���ð�ť�Ĵ�С��λ��
    button146.setGeometry(950,450, 100,30);

    MyButton button147(QString::fromLocal8Bit("2��"));
    //���ð�ť�Ĵ�С��λ��
    button147.setGeometry(950,490, 60,60);

    MyButton button148(QString::fromLocal8Bit("1��"));
    //���ð�ť�Ĵ�С��λ��
    button148.setGeometry(950,560, 60,60);

    MyButton button149(QString::fromLocal8Bit("һ��"));
    //���ð�ť�Ĵ�С��λ��
    button149.setGeometry(1070,500,40,150);

    MyButton button150(QString::fromLocal8Bit("2��"));
    //���ð�ť�Ĵ�С��λ��
    button150.setGeometry(970,630,50,25);

    MyButton button151(QString::fromLocal8Bit("1��"));
    //���ð�ť�Ĵ�С��λ��
    button151.setGeometry( 970,655,50,25);

    MyButton button152(QString::fromLocal8Bit("����"));
    //���ð�ť�Ĵ�С��λ��
    button152.setGeometry(795,700,50,30);


    //����ť��ӵ�window��
    button6.setParent(&window);
    //button2.setParent(&window);
    button3.setParent(&window);
    //button100.setParent(&window);
    button101.setParent(&window);
    button102.setParent(&window);
    button103.setParent(&window);
    button104.setParent(&window);
    button105.setParent(&window);
    button106.setParent(&window);
    button107.setParent(&window);
    button108.setParent(&window);
    button109.setParent(&window);
    button110.setParent(&window);
    button111.setParent(&window);
    button112.setParent(&window);
    button113.setParent(&window);
    button114.setParent(&window);
    button115.setParent(&window);
    button116.setParent(&window);
    button117.setParent(&window);
    button118.setParent(&window);
    button119.setParent(&window);
    button120.setParent(&window);
    button121.setParent(&window);
    button122.setParent(&window);
    button123.setParent(&window);
    button124.setParent(&window);
    button125.setParent(&window);
    button126.setParent(&window);
    button127.setParent(&window);
    button128.setParent(&window);
    button129.setParent(&window);
    button130.setParent(&window);
    button131.setParent(&window);
    button132.setParent(&window);
    button133.setParent(&window);
    button134.setParent(&window);
    button135.setParent(&window);
    button136.setParent(&window);
    button137.setParent(&window);
    button138.setParent(&window);
    button139.setParent(&window);
    button140.setParent(&window);
    button141.setParent(&window);
    button142.setParent(&window);
    button143.setParent(&window);
    button144.setParent(&window);
    button145.setParent(&window);
    button146.setParent(&window);
    button147.setParent(&window);
    button148.setParent(&window);
    button149.setParent(&window);
    button151.setParent(&window);
    button152.setParent(&window);
    window.show();
    return a.exec();
}
