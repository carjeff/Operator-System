#include<iostream>
#include<iomanip>
using namespace std;
void OPT(int Page[],int n,int piece,int total)
{
    int i,number=0,j,position=0,temp;
    int rate=0;
    int*p=new int [piece];
    int*flag=new int[total];
    //���ҳ�����ڴ�������0�������ڴ�飬1�����ڴ�飬2���Ժ���ٴη��ʲ����Ѿ����ڴ���
    for(i=0;i<piece;i++)
       p[i]=-1;//�ڴ��������ֵ
    for(i=0;i<total;i++)
       flag[i]=0;
    for(i=0;i<n;i++)//ȱҳ����
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
       cout<<"ȱҳ"<<endl;
       }  
       else
       {
           cout<<Page[i]<<":"<<setw(4);
           Output1(p,piece);
           cout<<"��ȱҳ"<<endl;
       }
    }
    cout<<"ȱҳ������"<<rate<<""<<"����"<<n<<endl;
    cout<<"����û��㷨��OPT)ȱҳ��Ϊ"<<(double)rate/n*100<<"%"<<endl;
    delete[]p;
    delete[]flag;
}