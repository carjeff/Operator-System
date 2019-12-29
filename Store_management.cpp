#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <pthread.h>
#include <malloc.h>
#include <semaphore.h>
using namespace std;
struct node
{
    string name;
    int address;
    int length;
    struct node* next;
};
struct node* free_list;
struct node* used_list;
struct node* built(struct node* p,int address=0,int length=0,string name="")
{
    p->next=new(node);
    struct node* q=p->next;
    q->name=name;
    q->address=address;
    q->length=length;
    q->next=NULL;
    return q;
}
void delete_node(node* p,node* q)
{
    p->next=q->next;
    free(q);
}
void insert_node(node* p)
{
    p->next=used_list->next;
    used_list->next=p;
}
void init()
{
    free_list=new(node);
    free_list->address=free_list->length=0;
    free_list->next=NULL;
    used_list=new(node);
    used_list->address=used_list->length=0;
    used_list->next=NULL;
    printf("请输入主存容量: ");
    int x;scanf("%d",&x);
    built(free_list,0,x);
    printf("初始化成功!\n");
}
void show()
{
    struct node *p=free_list->next;
    printf("未分配:\n");
    if(p==NULL)
        printf("无\n");
    else
    {
        while(p!=NULL)
        {
            printf("起始位置:%d 容量:%d\n",p->address,p->length);
            p=p->next;
        }
    }
    p=used_list->next;
    printf("已分配:\n");
    if(p==NULL)
        printf("无\n");
    else
    {
        while(p!=NULL)
        {
            printf("进程名:");
            cout<<p->name;
            printf(" 起始位置:%d 容量:%d\n",p->address,p->length);
            p=p->next;
        }
    }
}
void First_Fit(node* p)
{
    node* now=free_list->next;
    node* pre=free_list;
    bool flag=false;
    while(now!=NULL)
    {
        if(now->length>=p->length)
        {
            flag=true;
            now->length-=p->length;
            p->address=now->address;
            now->address+=p->length;
            if(now->length==0)
            delete_node(pre,now);
            insert_node(p);
            break;
        }
        now=now->next;
        pre=pre->next;
    }
    if(flag)
    printf("分配成功 地址为:%d\n",p->address);
    else
    printf("内存不足 分配失败\n");
}
void Best_Fist(node* p)
{
    node* now=free_list->next;
    node* pre=free_list;
    node* bestnow=now;
    node* bestpre=pre;
    bool flag=false;
    while(now!=NULL)
    {
        if(now->length>=bestnow->length&&now->length>=p->length)
        {
            flag=true;
            bestnow=now;
            bestpre=pre;
        }
        now=now->next;
        pre=pre->next;
    }
    if(!flag)
    {
        printf("内存不足 分配失败\n");
        return;
    }
    bestnow->length-=p->length;
    p->address=bestnow->address;
    bestnow->address+=p->length;
    if(bestnow->length==0)
    delete_node(bestpre,bestnow);
    insert_node(p);
    printf("分配成功 地址为:%d\n",p->address);
}
void allocate()
{
    struct node* p=new(node);
    p->next=NULL;
    printf("请输入进程名: ");
    cin>>p->name;
    printf("请输入进程容量: ");
    cin>>p->length;
    printf("1.First_Fit\n");
    printf("2.Best_Fist\n");
    printf("请选择需要使用的分配算法: ");
    int ti;
    cin>>ti;
    if(ti==1)
    First_Fit(p);
    else
    Best_Fist(p);
}
void fixpre(node* pre,node* p,node* now)
{
    pre->length+=p->length;
    if(pre->address+pre->length==now->address)
    {
        pre->length+=now->length;
        delete_node(pre,now);
    }
}
void fixback(node* p,node* now)
{
    now->address=p->address;
    now->length+=p->length;
}
void fixmid(node* pre,node* p,node* now)
{
    p->next=now;
    pre->next=p;
}
void recovery_find(node* p)
{
    node* now=free_list->next;
    node* pre=free_list;
    if(p->address+p->length<=now->address)
    {
        p->next=pre->next;
        pre->next=p;
        return;
    }
    while(now!=NULL)
    {
        if((pre->address+pre->length<=p->address)&&(p->address+p->length<=now->address))
        {
            if(pre->address+pre->length==p->address)
            fixpre(pre,p,now);
            else if(p->address+p->length==now->address)
            fixback(p,now);
            else
            fixmid(pre,p,now);
            return;
        }
        now=now->next;
        pre=pre->next;
    }
    if(pre->address+pre->length<p->address)
    {
        pre->next=p;
        p->next=NULL;
    }
}
void recovery()
{
    string process_name;
    printf("请输入进程名: ");
    cin>>process_name;
    node* now=used_list->next;
    node* pre=used_list;
    bool flag=false;
    while(now!=NULL)
    {
        if(now->name==process_name)
        {
            flag=true;
            pre->next=now->next;
            // show();
            recovery_find(now);
            break;
        }
        now=now->next;
        pre=pre->next;
    }
    if(flag)
    printf("回收成功\n");
    else
    printf("回收失败 未查找到\n");
}
int main(int argc, char const *argv[]) {
    printf("\033c");
    printf("----------------------------------------\n");
    printf("-        动态多分区存储管理模拟系统    -\n");
    printf("-                                      -\n");
    printf("-                                      -\n");
    printf("-             1.初始化                 -\n");
    printf("-             2.显示主存使用情况       -\n");
    printf("-             3.模拟分配               -\n");
    printf("-             4.模拟回收               -\n");
    printf("-             0.退出                   -\n");
    printf("-                                      -\n");
    printf("----------------------------------------\n");
    int ti;
    while(1)
    {
        printf("--请选择功能选项:  ");
        scanf("%d",&ti);
        if(ti==1)
        init();
        else if(ti==2)
        show();
        else if(ti==3)
        allocate();
        else if(ti==4)
        recovery();
        else if(ti==0)
        {
            delete(free_list),delete(used_list);
            break;
        }
    }
    return 0;
}
