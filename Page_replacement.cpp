#include <iostream>
#include <time.h>
#include <iomanip>
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include "LFU.h"
using namespace std;
void Random(int a[], int n);
int Translate(int a[], int Page[], int n, int p);
int main()
{
    int a[320]; //存放320条指令
    int i = 1;
    int p;          //存放页大小
    int page[320];  //存放合并后要使用的页号
    int PageNumber; //存放页号数量
    int piece;      //存放块数
    bool flag = true;
    cout<<"=================页面置换模拟程序================"<<endl;
    cout<<"=================车子杰 2017040314================"<<endl;
    while (flag)
    {
        switch (i)
        {
        case 1:
            Random(a, 320);
        case 2:
            cout << "请输入页大小（1K、2K、4K、8K、16K、）：";
            cin >> p;
            PageNumber = Translate(a, page, 320, p);
            cout << "将相邻相同的页号合并为一个后要使用到的页号数为" << PageNumber << "个" << endl;
        case 3:
            cout << "请输入块数（1~" << 32 / p << "）：";
            cin >> piece;
        case 4:
            cout << "请选择页面置换算法(1~3)" << endl;
            cout << "1.最佳置换算法（OPT)" << endl;
            cout << "2.先进先出置换算法（FIFO）" << endl;
            cout << "3.最近最少用置换算法（LRU）" << endl;
            cout << "4.最少使用置换算法（LFU）" << endl;
            cin >> i;
            switch (i)
            {
            case 1:
                OPT(page, PageNumber, piece, 32 / p);
                break;
            case 2:
                FIFO(page, PageNumber, piece, 32 / p);
                break;
            case 3:
                LRU(page, PageNumber, piece, 32 / p);
                break;
            case 4:
                LFU(page, PageNumber, piece, 32 / p);
                break;
            default:
                cout << "输入有误" << endl;
                break;
            }
            cout << "*****************************" << endl;
            cout << "*****1.重新开始" << endl;
            cout << "*****2.返回重新输入页大小" << endl;
            cout << "*****3.返回重新输入块数" << endl;
            cout << "*****4.返回重新选择页面置换算法" << endl;
            cout << "*****5.结束程序" << endl;
            cin >> i;
            break;
        default:
            flag = false;
        }
    }
    return 0;
}
void Random(int a[], int n)
{
    cout << "指令如下：" << endl;
    int m, i = 0;
    srand((unsigned)(time(NULL)));
    while (i < n)
    {
        a[i++] = rand() % n;
        m = a[i] = a[i - 1] + 1;
        a[++i] = rand() % (m + 1);
        i++;
        m = a[i] = a[i - 1] + 1;
        a[++i] = rand() % (n - m + 1) + m + 1;
        i++;
    }
    for (i = 0; i < n; i++)
    {
        cout << a[i] << setw(4);
        if ((i + 1) % 10 == 0)
            cout << endl;
    }
    cout << endl;
}
int Translate(int a[], int Page[], int n, int p)
{
    cout << "页面调度序列如下：" << endl;
    int i, j = 0;
    int temp = -1, result;
    for (i = 0; i < n; i++)
    {
        result = a[i] / (p * 10);
        if (result != temp)
            temp = Page[j++] = result;
    }
    for (i = 0; i < j; i++)
    {
        cout << Page[i] << setw(4);
        if ((i + 1) % 10 == 0)
            cout << endl;
    }
    cout << endl;
    return j;
}