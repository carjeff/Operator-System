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
       p[i]=-1;//�ڴ��������ֵ
       for(i=0;i<n;i++)
           {
               cout<<i+1<<" ";
              cout<<Page[i]<<":"<<setw(4);
              for(j=0;j<piece&&p[j]!=Page[i];j++);//�����Ƿ�ȱҳ
               if(p[j]==Page[i])//��ȱҳ����
              {
                  temp=p[j];
                  while(j<piece-1)
                  {
                     p[j]=p[j+1];
                     j++;
                  }
                  p[j]=temp;
              Output1(p,piece);
              cout<<"��ȱҳ"<<endl;
              }
              else//ȱҳ����
              {
              rate++;
              for(j=0;j<piece-1;j++)
                  p[j]=p[j+1];
              p[j]=Page[i];
              Output1(p,piece);
              cout<<"ȱҳ"<<endl;
              }
       }
    cout<<"ȱҳ������"<<rate<<""<<"����"<<n<<endl;
    cout<<"����������û��㷨��LRU��ȱҳ��Ϊ"<<(double)rate/n*100<<"%"<<endl;
    delete[]p;
}