#define MaxVnum 60
#define Max 40

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string.h>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;
void shouye();
void denglu();
void cishouye();
void xiugai();
void hongbo1();
void erchou1();
void erchou2();
void color(short x);
struct node
{
    string name;
    string key;
} stu[100000];

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
    doc->SaveFile("./main2/bin/Debug/buildings.xml");
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
        itoa((b.V[i].id) , string, 10);
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
    doc->SaveFile("../main2/bin/Debug/buildings.xml");
    doc->SaveFile("../main2/buildings.xml");
    doc->SaveFile("buildings.xml");
}


int we=0,yanzheng,count1=0,count2=0;
const int inf = 0x3f3f3f3f;
void add_node()
{
    color(16);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                ";
    color(14);
    cout<<"���ӽڵ���Ϣ";
    color(16);
    cout<<"                                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    int n,tu[99][99];
    color(16);
    cout<<"                       ";
    color(13);
    ifstream infile("Graph_data.txt");
    infile>>n;
    printf("�ýڵ�IDΪ:%d",n+1);
    printf("\n������øýڵ���ʣ��%d���ڵ���·��������֮���ÿո���������س�����������\n",n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            infile>>tu[i][j];
        }
    }
    n++;
    int u;
    for(int i=0;i<n-1;i++)
    {
        scanf("%d",&u);
        tu[n-1][i] = u;
        tu[i][n-1] = u;
    }
    tu[n-1][n-1] = 0;
    infile.close();
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
    printf("***���ӽڵ�ɹ�***\n");
    cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"����1������һ��:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        hongbo1();
    }
}
void delete_node()
{
    color(16);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                ";
    color(14);
    cout<<"ɾ���ڵ���Ϣ";
    color(16);
    cout<<"                                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    color(16);
    cout<<"                       ";
    color(13);
    int n,tu[99][99],i,x;
    printf("������Ҫɾ���Ľڵ�id:");
    scanf("%d",&x);
   // printf("\n");
    ifstream infile("Graph_data.txt");
    infile>>n;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            infile>>tu[i][j];
        }
    }

    for(int i=0;i<n;i++)
    {
       tu[x][i] = inf;
       tu[i][x] = inf;
    }
    infile.close();
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
    printf("***ɾ�����***\n");
    cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"����1������һ��:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        hongbo1();
    }
}
void change_node()
{cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"����1������һ��:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        hongbo1();
    }
    color(16);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                ";
    color(14);
    cout<<"�޸�·����Ϣ";
    color(16);
    cout<<"                                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    int n,tu[99][99],i,x;
    color(16);
    cout<<"                       ";
    color(13);
    printf("������Ҫ�޸ĵĽڵ�id:");
    scanf("%d",&x);
   // printf("\n");
    ifstream infile("Graph_data.txt");
    infile>>n;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            infile>>tu[i][j];
        }
    }
    infile.close();
    printf("\n������øýڵ���ʣ��%d���ڵ���·��������֮���ÿո���������س�����������\n",n);
    int u;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&u);
        tu[x][i] = u;
        tu[i][x] = u;
    }


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
    printf("***�޸����***\n");
    cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"����1������һ��:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        hongbo1();
    }
}
void print_graph()
{
    color(16);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                ";
    color(14);
    cout<<"�����ͼ��Ϣ";
    color(16);
    cout<<"                                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    int n,tu[99][99];
    color(16);
    cout<<"                       ";
    color(13);
    ifstream infile("Graph_data.txt");
    infile>>n;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            infile>>tu[i][j];
        }
    }
    infile.close();
    printf("ͼ�Ľڵ���:%d\n",n);
    printf("������ͼ���ٽӾ���:\n");
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n;j++)
       {
           printf("%d ",tu[i][j]);
       }
       printf("\n");
    }
     cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"����1������һ��:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        hongbo1();
    }

}
void update_bus_road()
{
    color(16);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                ";
    color(14);
    cout<<"¼�빫��·��";
    color(16);
    cout<<"                                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    color(16);
    cout<<"                       ";
    color(13);
    int m,k,kk;
//    freopen("Bus_data.txt","w",stdin);
    ofstream outfile("Bus_data.txt");
    printf("�����빫��·������:");
    scanf("%d",&m);
    outfile<<m;
    outfile<<"\n";
    for(int i=1;i<=m;i++)
    {
        printf("\n������%d����·վ������",i);
        scanf("%d",&k);
            outfile<<k;
            outfile<<" ";
            printf("\n����������%d����·վ���ţ��ÿո���������н�������",i);
            for(int j=0;j<k;j++)
            {
               scanf("%d",&kk);
               outfile<<kk;
               outfile<<" ";

            }
               outfile<<"\n";
    }
    outfile.close();
    cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"����1������һ��:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        hongbo1();
    }
}
void color(short x) //�Զ��庯���ݲ����ı���ɫ
{
    if(x>=0 && x<=15)//������0-15�ķ�Χ��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //ֻ��һ���������ı�������ɫ
    else//Ĭ�ϵ���ɫ��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void xiugai()
{
    string name1,key,key1;
    count1=0;count2=0;
    int sum=0;
    color(16);
    system("cls");
    ifstream inf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"�����޸�";
    color(16);
    cout<<"                                  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"������ѧ��(3�δ����Զ�������ҳ):";
    while(1)
    {

        cin>>name1;
        int m=0;
        we =0 ;
        inf.open("��¼ע��.txt");
        while(inf>>stu[we].name)
        {
            inf>>stu[we].key;
            we++;
        }
        for(int i=0; i<we; i++)
        {
            if(name1==stu[i].name)
            {
                yanzheng=i;
                m=1;
                break;
            }
        }
        if(m==0)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"�޸�ѧ�ţ�����������:";
            count1++;
        }
        if(count1==3) shouye();
        if(m==1)
        {
            sum++;
            break;
        }
    }
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"����������(3�δ����Զ�������ҳ):";
    while(1)
    {
        cin>>key;
        int n=0;
        if(key==stu[yanzheng].key) n=1;
        if(key!=stu[yanzheng].key)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"���벻��ȷ������������:";
            count2++;
            if(count2==3) shouye();
        }
        if(n==1)
        {
            sum++;
            break;
        }
    }
    color(16);
    cout<<"                          ";
    color(14);
    cout<<"������������(������6��11֮��):";
    while(1)
    {
        cin>>key1;
        int z=0;
        for(int i=0; i<(int)key1.length(); i++)
        {
            if(key1[i]<'0'||key1[i]>'z')
            {
                z=1;
                break;
            }
        }
        if(z==1)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"���벻�Ϸ�������������:";
        }
        else if((int)key1.length()>=11||(int)key1.length()<6)
        {
            color(16);
            cout<<"                           ";
            color(14);
            cout<<"���볤�Ȳ��Ϸ�������������:";
        }
        else
        {
            sum++;
            break;
        }
    }
    if(sum==3)
    {
        color(16);
        cout<<endl<<"                                  ";
        color(14);
        cout<<"����޸ĳɹ����"<<endl<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
        for(int i=0; i<40; i++)
        {
            Sleep(20);
            cout<<"��";
        }
        stu[yanzheng].key=key1;
        ofstream out("��¼ע��.txt");
        for(int i=0; i<we; i++)
        {
            out<<stu[i].name;
            out<<"\n";
            out<<stu[i].key;
            out<<"\n";
        }
        out.close();
    }
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"1���û���¼";
    color(16);
    cout<<"                               ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";

    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"2��������ҳ";
    color(16);
    cout<<"                               ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                                 ";
    color(14);
    cout<<"��ѡ����һ������:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1"&&xuanze!="2")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        {
            color(16);
            denglu();
        }
        if(xuanze=="2")
        {
            color(16);
            shouye();
        }
    }
}
void zhuxiao()
{
    string xuanze;
    string name1,key,key1;
    int sum=0;
    color(16);
    system("cls");
    ifstream inf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"�û�ע��";
    color(16);
    cout<<"                                  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"������ѧ��(3�δ����Զ�������ҳ):";
    while(1)
    {
        cin>>name1;
        int m=0;
        we =0 ;
        inf.open("��¼ע��.txt");
        while(inf>>stu[we].name)
        {
            inf>>stu[we].key;
            we++;
        }
        inf.close();
        for(int i=0; i<we; i++)
        {
            if(name1==stu[i].name)
            {
                yanzheng=i;
                m=1;
                break;
            }
        }
        if(m==0)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"�޸�ѧ�ţ�����������:";
            count1++;
        }
        if(count1==3) {count1=count2=0;shouye();}
        if(m==1)
        {
            sum++;
            break;
        }
    }
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"����������(3�δ����Զ�������ҳ):";
    while(1)
    {
        cin>>key;
        int n=0;
        if(key==stu[yanzheng].key) n=1;
        if(key!=stu[yanzheng].key)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"���벻��ȷ������������:";
            count2++;
            if(count2==3) {count1=count2=0;shouye();}
        }
        if(n==1)
        {
            sum++;
            break;
        }
    }
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"�Ƿ�ȷ��ע��(1��ȷ��2��ȡ��):";
       while(1)
    {
        string k;
        cin>>k;
        if(k!="1"&&k!="2")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(k=="1") {sum++;break;}
        if(k=="2") shouye();
    }
    if(sum==3)
    {
        color(16);
        cout<<endl<<"                                  ";
        color(14);
        cout<<"���ע���ɹ����"<<endl<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
        for(int i=0; i<40; i++)
        {
            Sleep(20);
            cout<<"��";
        }
        ofstream out("��¼ע��.txt");
        for(int i=0; i<we; i++)
        {
            if(i==yanzheng) i++;
            out<<stu[i].name;
            out<<"\n";
            out<<stu[i].key;
            out<<"\n";
        }
        out.close();
    }
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"1���û���¼";
    color(16);
    cout<<"                               ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";

    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"2��������ҳ";
    color(16);
    cout<<"                               ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                                 ";
    color(14);
    cout<<"��ѡ����һ������:";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1"&&xuanze!="2")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        {
            color(16);
            denglu();
        }
        if(xuanze=="2")
        {
            color(16);
            shouye();
        }
    }
}
void denglu()
{
    string name1,key;
    color(16);
    system("cls");
    ifstream inf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"�û���¼";
    color(16);
    cout<<"                                  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"������ѧ��(3�δ����Զ�������ҳ):";
    while(1)
    {
        cin>>name1;
        int m=0;
        we = 0;
        inf.open("��¼ע��.txt");
        while(inf>>stu[we].name)
        {
            inf>>stu[we].key;
            we++;
        }
        inf.close();
        for(int i=0; i<we; i++)
        {
            if(name1==stu[i].name)
            {
                yanzheng=i;
                m=1;
                break;
            }
        }
        if(m==1) break;
        if(m==0)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"�޸�ѧ�ţ�����������:";
            count1++;
        }
        if(count1==3) {count1=0;
    count2=0;shouye();}
    }
    color(16);
    cout<<"                       ";
    color(14);
    cout<<"����������(3�δ����Զ�������ҳ):";
    while(1)
    {
        cin>>key;
        if(key!=stu[yanzheng].key)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"���벻��ȷ������������:";
            count2++;
            if(count2==3) {count1=0;
    count2=0;shouye();}
        }
        else
        {
            color(16);
            cout<<endl<<"                                  ";
            color(14);
            cout<<"����¼�ɹ����"<<endl<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
            for(int i=0; i<40; i++)
            {
                Sleep(20);
                cout<<"��";
            }
            cishouye();
        }
    }
}
void cishouye()
{
    color(16);
    system("cls");
    ofstream outfile;
    ifstream inf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"�û�ѡ��";
    color(16);
    cout<<"                                  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��   1��������ҳ   ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 2���޸�·����Ϣ ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 3��¼�뾰����Ϣ ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 4��  ������ҳ   ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                                   ";
    color(14);
    cout<<"������ѡ��";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1"&&xuanze!="2"&&xuanze!="3"&&xuanze!="4")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        /*if(xuanze=="1")
        {
            char cc[30];
            sprintf(cc,"%s","../main2/bin/Debug/ererchou.exe meta");
            system(cc);
            //system("");
        }*/
        if(xuanze=="2")
        hongbo1();
        if(xuanze=="3")
        {
        graph gh= initgraph();
        writeXml(gh);
        cout<<"��ʼ���ɹ���"<<endl;
        }

        if(xuanze=="4")
            shouye();
    }
}
void hongbo1()
{
    color(16);
    system("cls");
    ofstream outfile;
    ifstream inf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                ";
    color(14);
    cout<<"�޸�·����Ϣ";
    color(16);
    cout<<"                                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������";
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 1���޸Ľڵ���Ϣ ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 2��¼�빫��·�� ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 3�������ͼ��Ϣ ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 4��ɾ���ڵ���Ϣ ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 5�����ӽڵ���Ϣ ��"<<endl;
    color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"�� 6�� ������һ��  ��"<<endl;
     color(16);
    cout<<"                             ";
    color(14);
    cout<<"��                 ��"<<endl;
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                                   ";
    color(14);
    cout<<"������ѡ��";
    while(1)
    {
        string xuanze;
        cin>>xuanze;
        if(xuanze!="1"&&xuanze!="2"&&xuanze!="3"&&xuanze!="4"&&xuanze!="5"&&xuanze!="6")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        change_node();
        if(xuanze=="2")
        update_bus_road();
        if(xuanze=="3")
         print_graph();
        if(xuanze=="4")
         delete_node();
        if(xuanze=="5")
          add_node();
        if(xuanze=="6")
            cishouye();
    }
}
void zhuce()
{
    string name,key,key2;
    string xuanze;
    int sum=0;
    color(16);
    system("cls");
    ofstream outfile;
    ifstream inf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��������������������������������������������������������������������������������";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"�û�ע��";
    color(16);
    cout<<"                                  ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��";
    color(16);
    cout<<"                                                                            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                                 ";
    color(14);
    cout<<"������ѧ��:";
    while(1)
    {
        cin>>name;
        int n=0,m=0;
        we=0;
        for(int i=0; i<(int)name.length(); i++)
        {
            if(name[i]<'0'||name[i]>'9')
            {
                n=1;
                break;
            }
        }
        inf.open("��¼ע��.txt");
        while(inf>>stu[we].name)
        {
            inf>>stu[we].key;
            we++;
        }
        inf.close();
        for(int i=0; i<we; i++)
        {
            if(name==stu[i].name)
                m=1;
        }
         if(m==1)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"����ѧ�ţ�����������:";
        }
        if(m==0)
        {
            if(n==1)
            {
                color(16);
                cout<<"                             ";
                color(14);
                cout<<"���벻�Ϸ�������������:";
            }
            else if(n==0&&(int)name.length()!=11)
            {
                color(16);
                cout<<"                           ";
                color(14);
                cout<<"���볤�Ȳ��Ϸ�������������:";
            }
            else
            {
                sum++;
                break;
            }
        }
    }
    color(16);
    cout<<"                          ";
    color(14);
    cout<<"����������(������6��11֮��):";
    while(1)
    {
        cin>>key;
        int n=0;
        for(int i=0; i<(int)key.length(); i++)
        {
            if(key[i]<'0'||key[i]>'z')
            {
                n=1;
                break;
            }
        }
        if(n==1)
        {
            color(16);
            cout<<"                             ";
            color(14);
            cout<<"���벻�Ϸ�������������:";
        }
        else if(n==0&&((int)key.length()>=11||(int)key.length()<6))
        {
            color(16);
            cout<<"                           ";
            color(14);
            cout<<"���볤�Ȳ��Ϸ�������������:";
        }
        else
        {
            sum++;
            break;
        }
    }
    color(16);
    cout<<"                                 ";
    color(14);
    cout<<"���ٴ���������:";
    while(1)
    {
        cin>>key2;
        if(key!=key2)
        {
            color(16);
            cout<<"                           ";
            color(14);
            cout<<"���벻һ�£�����������:";
        }
        else
        {
            sum++;
            break;
        }
    }
    if(sum==3)
    {
        outfile.open("��¼ע��.txt",ios::app);//(������) ��������������ļ�����
        if(!outfile) cout<<"error"<<endl;
        outfile<<name;
        outfile<<"\r\n";
        outfile<<key;
        outfile<<"\r\n";
        outfile.close();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<endl;
    for(int i=0; i<40; i++)
    {
        Sleep(20);
        cout<<"��";
    }
    color(16);
    cout<<endl<<"                                  ";
    color(14);
    cout<<"���ע��ɹ����"<<endl<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    for(int i=0; i<40; i++)
    {
        Sleep(20);
        cout<<"��";
    }
    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"1���û���¼";
    color(16);
    cout<<"                               ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";

    cout<<"��";
    color(16);
    cout<<"                                  ";
    color(14);
    cout<<"2��������ҳ";
    color(16);
    cout<<"                               ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"��";
    cout<<"��������������������������������������������������������������������������������"<<endl;
    color(16);
    cout<<"                                 ";
    color(14);
    cout<<"��ѡ����һ������:";
    while(1)
    {
        cin>>xuanze;
        if(xuanze!="1"&&xuanze!="2")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        {
            color(16);
            denglu();
        }
        if(xuanze=="2")
        {
            color(16);
            shouye();
        }
    }
}
void shouye()
{
    color(16);
    system("cls");
    string xuanze;
    color(13);
    cout<<"                                   ��"<<endl;
    color(13);
    cout<<"                                 ��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                             ��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                         ��";
    color(11);
    cout<<"����";
    color(13);
    cout<<"�";
    color(11);
    cout<<"��";
    color(13);
    cout<<"����";
    color(11);
    cout<<"����";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                     ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"�";
    color(11);
    cout<<"������";
    color(13);
    cout<<"����";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                   ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"�";
    color(11);
    cout<<"��";
    color(14);
    cout<<"����ͼ";
    color(11);
    cout<<"��";
    color(13);
    cout<<"����";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"              ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"����";
    color(11);
    cout<<"����";
    color(14);
    cout<<"����ѡ�����";
    color(11);
    cout<<"����";
    color(13);
    cout<<"����";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��";
    color(11);
    cout<<"�X�T�T�T�T�T�T�T�T�[";
    color(13);
    cout<<"��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                  ��";
    color(11);
    cout<<"����";
    color(13);
    cout<<"��";
    color(11);
    cout<<"�U";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"  1������ע��   ";
    color(11);
    cout<<"�U";
    color(13);
    cout<<"��";
    color(11);
    cout<<"����";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                    �����";
    color(11);
    cout<<"�U                �U";
    color(13);
    cout<<"������"<<endl;
    color(13);
    cout<<"                      ���";
    color(11);
    cout<<"�U";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"  2��������¼   ";
    color(11);
    cout<<"�U";
    color(13);
    cout<<"����"<<endl;
    color(13);
    cout<<"                        ��";
    color(11);
    cout<<"�U                �U";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                      ���";
    color(11);
    cout<<"�U";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"  3���޸�����   ";
    color(11);
    cout<<"�U";
    color(13);
    cout<<"����"<<endl;
    color(13);
    cout<<"                    �����";
    color(11);
    cout<<"�U                �U";
    color(13);
    cout<<"������"<<endl;
    color(13);
    cout<<"                  ��";
    color(11);
    cout<<"����";
    color(13);
    cout<<"��";
    color(11);
    cout<<"�U";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 | 8 | 128 | 64);
    cout<<"  4����Ϣע��   ";
    color(11);
    cout<<"�U";
    color(13);
    cout<<"��";
    color(11);
    cout<<"����";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��";
    color(11);
    cout<<"�^�T�T�T�T�T�T�T�T�a";
    color(13);
    cout<<"��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"              ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"����";
    color(11);
    cout<<"����";
    color(11);
    cout<<"�������";
    color(11);
    cout<<"����";
    color(13);
    cout<<"����";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                   ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"�";
    color(11);
    cout<<"��";
    color(11);
    cout<<"����";
    color(11);
    cout<<"��";
    color(13);
    cout<<"����";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                     ��";
    color(11);
    cout<<"������";
    color(13);
    cout<<"�";
    color(11);
    cout<<"������";
    color(13);
    cout<<"����";
    color(11);
    cout<<"������";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                         ��";
    color(11);
    cout<<"����";
    color(13);
    cout<<"�";
    color(11);
    cout<<"��";
    color(13);
    cout<<"����";
    color(11);
    cout<<"����";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                             ��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                                 ��";
    color(11);
    cout<<"��";
    color(13);
    cout<<"��"<<endl;
    color(13);
    cout<<"                                   ��"<<endl;
    cout<<"                             ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout<<"��������ѡ��:";
    while(1)
    {
        cin>>xuanze;
        if(xuanze!="1"&&xuanze!="2"&&xuanze!="3"&&xuanze!="4")
        {
            color(16);
            cout<<"                             ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            cout<<"���벻�Ϸ����������룺";
        }
        if(xuanze=="1")
        zhuce();
        if(xuanze=="2")
        denglu();
        if(xuanze=="3")
        xiugai();
        if(xuanze=="4")
        zhuxiao();
    }
}
int main()
{
    shouye();
    return 0;
}
