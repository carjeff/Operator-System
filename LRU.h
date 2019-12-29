#include<iostream>
#include<iomanip>
using namespace std;
void LRU(int Page[],int n,int piece,int total)
{
    int i,number=0,j,position=0;
    int rate=0;
    int temp;
    int*p=new int [piece];
    for(i=0;i<piece;i++)
       p[i]=-1;//内存块数赋初值
       for(i=0;i<n;i++)
           {
               cout<<i+1<<" ";
              cout<<Page[i]<<":"<<setw(4);
              for(j=0;j<piece&&p[j]!=Page[i];j++);//查找是否缺页
               if(p[j]==Page[i])//不缺页处理
              {
                  temp=p[j];
                  while(j<piece-1)
                  {
                     p[j]=p[j+1];
                     j++;
                  }
                  p[j]=temp;
              Output1(p,piece);
              cout<<"不缺页"<<endl;
              }
              else//缺页处理
              {
              rate++;
              for(j=0;j<piece-1;j++)
                  p[j]=p[j+1];
              p[j]=Page[i];
              Output1(p,piece);
              cout<<"缺页"<<endl;
              }
       }
    cout<<"缺页次数："<<rate<<""<<"总数"<<n<<endl;
    cout<<"最近最少用置换算法（LRU）缺页率为"<<(double)rate/n*100<<"%"<<endl;
    delete[]p;
}