
#include<iostream>
using namespace std;
/*-----------------------------------------------*/  
/*输入函数*/  
/*-----------------------------------------------*/
//a-max,b-allocation,c-need,d-available
void input(int a[50][50],int b[50][50],int c[50][50],int d[50], int p, int r)
{
	int i,j;
	cout<<"输入Max数组: \n";
	for(i=0;i<p;i++)
		for(j=0;j<r;j++)cin>>a[i][j];
	cout<<"输入Allocation数组: \n";
	for(i=0;i<p;i++)
		for(j=0;j<r;j++)cin>>b[i][j];
    cout<<"输入Available数组: \n";
	for(j=0;j<r;j++)cin>>d[j];
	cout<<"计算得Need数组为: "<<endl;
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
			c[i][j] = a[i][j] - b[i][j];
			cout<<c[i][j]<<" ";
		}
		cout<<endl; 		
	}
}
 
/*-----------------------------------------------*/  
/*比较函数*/  
/*-----------------------------------------------*/
//比较结果为m中的元素全大于n中的元素返回1，否则返回0
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
/*安全性检验函数*/  
/*-----------------------------------------------*/
//b、c、d意义同上
int stest(int b[50][50],int c[50][50],int d[50],int p, int r)
{
	int i,j,k,l,flag=0,flag1=0;
	int t[r],finish[p],dd[r];
	for(i=0;i<p;i++)finish[i]=0;//finish为1即表示available满足某一进程并让其实现
 
	for(i=0;i<r;i++)dd[i]=d[i];
	cout<<"分配序列：\n";
	for(k=0;k<p;k++)            //全搜索，直至实现或不可能实现
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
	if(flag1==0)return(1);    //flag1为记录finish是否有0存在的标记，当flag1=0时，安全
	else return(0);
}
 
 
/*-----------------------------------------------*/  
/*申请进程后的安全性检验函数*/  
/*-----------------------------------------------*/
//req-request,n-第n个进程申请资源
void rtest(int b[50][50],int c[50][50],int d[50],int req[50],int n, int p, int r)
{
	int i,j;
	int t[r];
	n=n-1;
	for(i=0;i<r;i++)t[i]=c[n][i];
	if(com(d,req,r)&&com(t,req,r))//对available，request进行比较
	{
		for(j=0;j<r;j++)
		{
			b[n][j]=b[n][j]+req[j];
			c[n][j]=c[n][j]-req[j];
			d[j]=d[j]-req[j];
		}
	    if(stest(b,c,d,p,r))cout<<"允许第"<<n+1<<"个进程申请资源！\n";
	    else 
		{
		cout<<"不允许第"<<n+1<<"个进程申请资源！\n";
 
		cout<<"恢复以前状态！\n";
	    for(j=0;j<r;j++)
		{
			b[n][j]=b[n][j]-req[j];
			c[n][j]=c[n][j]+req[j];
			d[j]=d[j]+req[j];
		}
		}
	}
 
	else cout<<"申请资源量出错！\n";
}
 
 
/*-----------------------------------------------*/  
/*主函数*/  
/*-----------------------------------------------*/
int main()
{
	int j,n;
	int p, r;                   //n-第n个资源申请
	cout<<"请输入进程数: "<<endl;
	cin>>p;
	cout<<"请输入资源数: "<<endl;
	cin>>r;
	int max[50][50],allocation[50][50],need[50][50];
	int available[50],request[50];
	input(max,allocation,need,available,p,r);
 
	if(stest(allocation,need,available,p,r)==1)cout<<"初始状态安全！\n";
	else cout<<"初始状态不安全！\n";
 
	cout<<" input request data:\n";
	for(j=0;j<r;j++)cin>>request[j];
 
	cout<<"第n个进程申请资源——n的值\n";
	cin>>n;
 
	rtest(allocation,need,available,request,n,p,r);

    return 0;
}