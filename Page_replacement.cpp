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
    int a[320]; //���320��ָ��
    int i = 1;
    int p;          //���ҳ��С
    int page[320];  //��źϲ���Ҫʹ�õ�ҳ��
    int PageNumber; //���ҳ������
    int piece;      //��ſ���
    bool flag = true;
    cout<<"=================ҳ���û�ģ�����================"<<endl;
    cout<<"=================���ӽ� 2017040314================"<<endl;
    while (flag)
    {
        switch (i)
        {
        case 1:
            Random(a, 320);
        case 2:
            cout << "������ҳ��С��1K��2K��4K��8K��16K������";
            cin >> p;
            PageNumber = Translate(a, page, 320, p);
            cout << "��������ͬ��ҳ�źϲ�Ϊһ����Ҫʹ�õ���ҳ����Ϊ" << PageNumber << "��" << endl;
        case 3:
            cout << "�����������1~" << 32 / p << "����";
            cin >> piece;
        case 4:
            cout << "��ѡ��ҳ���û��㷨(1~3)" << endl;
            cout << "1.����û��㷨��OPT)" << endl;
            cout << "2.�Ƚ��ȳ��û��㷨��FIFO��" << endl;
            cout << "3.����������û��㷨��LRU��" << endl;
            cout << "4.����ʹ���û��㷨��LFU��" << endl;
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
                cout << "��������" << endl;
                break;
            }
            cout << "*****************************" << endl;
            cout << "*****1.���¿�ʼ" << endl;
            cout << "*****2.������������ҳ��С" << endl;
            cout << "*****3.���������������" << endl;
            cout << "*****4.��������ѡ��ҳ���û��㷨" << endl;
            cout << "*****5.��������" << endl;
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
    cout << "ָ�����£�" << endl;
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
    cout << "ҳ������������£�" << endl;
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