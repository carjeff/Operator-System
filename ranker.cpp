
#include<iostream>
using namespace std;
/*-----------------------------------------------*/  
/*���뺯��*/  
/*-----------------------------------------------*/
//a-max,b-allocation,c-need,d-available
void input(int a[50][50],int b[50][50],int c[50][50],int d[50], int p, int r)
{
	int i,j;
	cout<<"����Max����: \n";
	for(i=0;i<p;i++)
		for(j=0;j<r;j++)cin>>a[i][j];
	cout<<"����Allocation����: \n";
	for(i=0;i<p;i++)
		for(j=0;j<r;j++)cin>>b[i][j];
    cout<<"����Available����: \n";
	for(j=0;j<r;j++)cin>>d[j];
	cout<<"�����Need����Ϊ: "<<endl;
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
			c[i][j] = a[i][j] - b[i][j];
			cout<<c[i][j]<<" ";
		}
		cout<<endl; 		
	}
}
 
/*-----------------------------------------------*/  
/*�ȽϺ���*/  
/*-----------------------------------------------*/
//�ȽϽ��Ϊm�е�Ԫ��ȫ����n�е�Ԫ�ط���1�����򷵻�0
int com(int m[50],int n[50],int r)
{
	int i,flag=0;
	for(i=0;i<r;i++)
		if(m[i]<n[i])
		{
			flag=1;
		    break;
		}
	if(flag==1)	return(0);
	else return(1);
}
 
 
/*-----------------------------------------------*/  
/*��ȫ�Լ��麯��*/  
/*-----------------------------------------------*/
//b��c��d����ͬ��
int stest(int b[50][50],int c[50][50],int d[50],int p, int r)
{
	int i,j,k,l,flag=0,flag1=0;
	int t[r],finish[p],dd[r];
	for(i=0;i<p;i++)finish[i]=0;//finishΪ1����ʾavailable����ĳһ���̲�����ʵ��
 
	for(i=0;i<r;i++)dd[i]=d[i];
	cout<<"�������У�\n";
	for(k=0;k<p;k++)            //ȫ������ֱ��ʵ�ֻ򲻿���ʵ��
	{
		flag = 0;
		for(i=0;i<p;i++)
		{
			if(finish[i]==1)continue;
			else
			{
				for(j=0;j<r;j++)t[j]=c[i][j];
				if(com(dd,t,r))
				{
					finish[i]=1;
					cout<<i+1<<'\t';
				    flag=1;
					for(l=0;l<r;l++)dd[l]=dd[l]+b[i][l];
					break;
				}
			}
			if(flag==1)break;
		}	
	}
	cout<<'\n';
	for(l=0;l<p;l++)
	{
		//cout<<finish[l]<<endl;
		if(finish[l]==0)flag1=1;
	}
	    //cout<<flag1<<endl;
	if(flag1==0)return(1);    //flag1Ϊ��¼finish�Ƿ���0���ڵı�ǣ���flag1=0ʱ����ȫ
	else return(0);
}
 
 
/*-----------------------------------------------*/  
/*������̺�İ�ȫ�Լ��麯��*/  
/*-----------------------------------------------*/
//req-request,n-��n������������Դ
void rtest(int b[50][50],int c[50][50],int d[50],int req[50],int n, int p, int r)
{
	int i,j;
	int t[r];
	n=n-1;
	for(i=0;i<r;i++)t[i]=c[n][i];
	if(com(d,req,r)&&com(t,req,r))//��available��request���бȽ�
	{
		for(j=0;j<r;j++)
		{
			b[n][j]=b[n][j]+req[j];
			c[n][j]=c[n][j]-req[j];
			d[j]=d[j]-req[j];
		}
	    if(stest(b,c,d,p,r))cout<<"�����"<<n+1<<"������������Դ��\n";
	    else 
		{
		cout<<"�������"<<n+1<<"������������Դ��\n";
 
		cout<<"�ָ���ǰ״̬��\n";
	    for(j=0;j<r;j++)
		{
			b[n][j]=b[n][j]-req[j];
			c[n][j]=c[n][j]+req[j];
			d[j]=d[j]+req[j];
		}
		}
	}
 
	else cout<<"������Դ������\n";
}
 
 
/*-----------------------------------------------*/  
/*������*/  
/*-----------------------------------------------*/
int main()
{
	int j,n;
	int p, r;                   //n-��n����Դ����
	cout<<"�����������: "<<endl;
	cin>>p;
	cout<<"��������Դ��: "<<endl;
	cin>>r;
	int max[50][50],allocation[50][50],need[50][50];
	int available[50],request[50];
	input(max,allocation,need,available,p,r);
 
	if(stest(allocation,need,available,p,r)==1)cout<<"��ʼ״̬��ȫ��\n";
	else cout<<"��ʼ״̬����ȫ��\n";
 
	cout<<" input request data:\n";
	for(j=0;j<r;j++)cin>>request[j];
 
	cout<<"��n������������Դ����n��ֵ\n";
	cin>>n;
 
	rtest(allocation,need,available,request,n,p,r);

    return 0;
}