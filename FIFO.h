#include<iostream>
#include<iomanip>
using namespace std;
//输出函数
void Output1(int *p,int n)
{
    for(int i=0;i<n;i++)
       cout<<p[i]<<setw(4);
}
void FIFO(int Page[],int n,int piece,int total)
{
    int i,number=0,j,position=0;
    int rate=0;
    int*p=new int [piece];
    for(i=0;i<piece;i++)
       p[i]=-1;//内存块数赋初值
       for(i=0;i<n;i++)
       {
           cout<<i+1<<"";
           cout<<Page[i]<<":"<<setw(4);
           for(j=0;j<piece&&p[j]!=Page[i];j++)//查找是否缺页
              ;
           if(p[j]==Page[i])
           {
              Output1(p,piece);
              cout<<"不缺页"<<endl;
           }
           else
           {
              rate++;
              for(j=0;j<piece-1;j++)//缺页处理
                  p[j]=p[j+1];
              p[j]=Page[i];
              Output1(p,piece);
              cout<<"缺页"<<endl;
           }
       }
       cout<<"缺页次数："<<rate<<""<<"总数"<<n<<endl;
    cout<<"先进先出置换算法（FIFO）缺页率为"<<(double)rate/n*100<<"%"<<endl;
    delete[]p;
}