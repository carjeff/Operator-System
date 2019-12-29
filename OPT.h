#include<iostream>
#include<iomanip>
using namespace std;
void OPT(int Page[],int n,int piece,int total)
{
    int i,number=0,j,position=0,temp;
    int rate=0;
    int*p=new int [piece];
    int*flag=new int[total];
    //标记页数在内存的情况，0：不在内存块，1：在内存块，2：以后会再次访问并且已经在内存块的
    for(i=0;i<piece;i++)
       p[i]=-1;//内存块数赋初值
    for(i=0;i<total;i++)
       flag[i]=0;
    for(i=0;i<n;i++)//缺页处理
    {
       cout<<i+1<<"";
       if(flag[Page[i]]!=1)
       {
           rate++;
           j=i+1;
           temp=piece;
           while(temp!=1&&j<n)
           {
              if(flag[Page[j]]==1)
              {
                  flag[Page[j]]=2;
                  temp--;
              }
              j++;
           }
           for(j=0;j<piece;j++)
              if(flag[p[j]]==1)
                  temp=j;
              else flag[p[j]]=1;
           flag[p[temp]]=0;
           flag[Page[i]]=1;
           p[temp]=Page[i];
       cout<<Page[i]<<":"<<setw(4);
       Output1(p,piece);
       cout<<"缺页"<<endl;
       }  
       else
       {
           cout<<Page[i]<<":"<<setw(4);
           Output1(p,piece);
           cout<<"不缺页"<<endl;
       }
    }
    cout<<"缺页次数："<<rate<<""<<"总数"<<n<<endl;
    cout<<"最佳置换算法（OPT)缺页率为"<<(double)rate/n*100<<"%"<<endl;
    delete[]p;
    delete[]flag;
}