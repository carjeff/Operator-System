
#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>//setw
#include <cstdlib>//malloc
#include <queue>
using namespace std;
struct FCFS_SJF_r//�����ȷ���FCFS������ҵ�����㷨SJF�����ȼ��㷨r�Ľṹ��
{
	char name;			//������
	float arrivetime;	//����ʱ��
	float servetime;	//����ʱ��
	float finishtime;	//���ʱ��
	int priority;
	float roundtime;	//��תʱ��
	float daiquantime;	//��Ȩ��תʱ��
	struct FCFS_SJF_r *link;//�ṹ��ָ��
};
FCFS_SJF_r *head = NULL;
struct FCFS_SJF_r a[100];//��ʼ��ָ�������
struct FCFS_SJF_r *sortarrivetime(struct FCFS_SJF_r a[], int n);	//��������ʱ��ð��������
struct FCFS_SJF_r *sortservetime(struct FCFS_SJF_r a[], int n);//��������ʱ��ð��������
void FCFS(struct FCFS_SJF_r a[], int n, float &t1, float &t2);//�����ȷ����㷨
void SJF(struct FCFS_SJF_r a[], int n, float &t1, float &t2);//����ҵ���ȵ����㷨
void r(struct FCFS_SJF_r a[], int n, float &t1, float &t2);//���ȼ��㷨
struct FCFS_SJF_r *sortarrivetime(struct FCFS_SJF_r a[], int n)//������ʱ�����ð������
{
	int i, j;
	struct FCFS_SJF_r t;
	int flag;
	for (i = 1; i<n; i++)
	{
		flag = 0;
		for (j = 0; j<n - i; j++)
		{
			if (a[j].arrivetime>a[j + 1].arrivetime)	//������ʱ��̵Ľ�����ǰ��
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;//����
			}
		}
		if (flag == 0)//���һ��������û�����κν��������������	
		{
			break;
		}
	}
	return a;	//����������������
}
//�����ȼ�����
struct FCFS_SJF_r *sortpriority(struct FCFS_SJF_r a[], int n){
	int i, j;
	struct FCFS_SJF_r t;
	int flag;
	for (i = 1; i<n; i++)
	{
		flag = 0;
		for (j = 0; j<n - i; j++)
		{
			if (a[j].arrivetime>a[j + 1].arrivetime)	//������ʱ��̵Ľ�����ǰ��
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;//����
			}
		}
		for (j = 0; j<n - i; j++)
		{
			if ((a[j].priority<a[j + 1].priority)&&(a[j].arrivetime>=a[j + 1].arrivetime))//������ʱ��̵Ľ�����ǰ��
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				flag = 1;//����
			}
		}
		if (flag == 0)//���һ��������û�����κν��������������
		{
			break;
		}
	}
	return a;	//����������������
}
//���ȼ��㷨
void r(struct FCFS_SJF_r a[], int n, float &t1, float &t2)
{
	int i;
	struct FCFS_SJF_r t;
	a[0].finishtime = a[0].arrivetime + a[0].servetime;	//���ʱ��=����ʱ��+����ʱ��
	a[0].roundtime = a[0].finishtime - a[0].arrivetime;	//��תʱ��=���ʱ��-�ύʱ��
	a[0].daiquantime = a[0].roundtime / a[0].servetime;	//��Ȩʱ��=��תʱ��/����ʱ��
	for (i = 1; i < n; i++)
	{
 
		for (int c = i; c < n - 1; c++)
		{
			for (int d = i + 1; d<n; d++)
				if ((a[i - 1].finishtime >= a[c].arrivetime) && (a[i - 1].finishtime >= a[d].arrivetime) && (a[c].servetime > a[d].servetime))
				{
					t = a[c];
					a[c] = a[d];
					a[d] = t;
				}
		}
 
		if (a[i].arrivetime<a[i - 1].finishtime)	//��ǰ����ʱ������һ����ҵ����ʱ��֮ǰ
		{
			a[i].finishtime = a[i - 1].finishtime + a[i].servetime;	//���ʱ��=��һ�����ʱ��+����ʱ��
			a[i].roundtime = a[i].finishtime - a[i].arrivetime;		//��תʱ��=���ʱ��-����ʱ��
			a[i].daiquantime = a[i].roundtime / a[i].servetime;		//��Ȩʱ��=��תʱ��/����ʱ��
		}
		else	//��ǰ����ʱ������һ����ҵ����ʱ��֮��
		{
			a[i].finishtime = a[i].arrivetime + a[i].servetime;
			a[i].roundtime = a[i].finishtime - a[i].arrivetime;
			a[i].daiquantime = a[i].roundtime / a[i].servetime;
		}
 
	}
	for (int i = 0; i<n; i++)
	{
		printf("\n------------------------------------------------------\n");
		cout << setw(2) << "��������" << a[i].name << endl;
		cout << setw(2) << "����ʱ�䣺" << a[i].arrivetime << endl;
		cout << setw(2) << "����ʱ�䣺" << a[i].servetime << endl;
		cout << setw(2) << "���ȼ�: " << a[i].priority << endl;
		cout << setw(2) << "���ʱ�䣺" << a[i].finishtime << endl;
		cout << setw(2) << "��תʱ�䣺" << a[i].roundtime << endl;
		cout << setw(2) << "��Ȩ��תʱ��" << a[i].daiquantime << endl;
		t1 += a[i].roundtime;
		t2 += a[i].daiquantime;
	}
}
class RR1//��ת�����㷨�Ľṹ��
{   public:
	char name;		//������
	float arrive;	//���̵���ʱ��
	float run;		//��������ʱ��
	float rest;		//���н���ʣ��ʱ��
	float finish;   //���ʱ��
	float zhouzhuan = 0.0f;	//��תʱ�䣬
    float daiquan = 0.0f;//��Ȩ��תʱ��
	string state;	//����״̬
};
void RR(int &a)//ʱ��Ƭ��ת�㷨
{
	RR1 b[100];
	queue<RR1*>buffer;
	int i, j, flag;
	RR1 t;
	float temp = 0.0f;	//�������һ������rest
	float nowtime = 0.0f;
	float sum_zhouzhuan = 0.0f, sum_daiquan = 0.0f;	//���н�������תʱ�䣬���н����ܴ�Ȩ��תʱ��
	float avr_zhouzhuan = 0.0f, avr_daiquan = 0.0f;
	for (i = 0; i < a; i++)
	{
		printf("%d ������: ", i + 1);
		scanf("%s", &b[i].name);
		printf("����ʱ�䣺");
		scanf("%f", &b[i].arrive);
		printf("����ʱ�䣺");
		scanf("%f",&b[i].run);
		b[i].rest = b[i].run;
		b[i].state = "δ����";
	}
	float slice = 0.0f;
	printf("������ʱ����С: ");
	scanf("%f", &slice);
	flag = 0;
	for (i = 1; i < a; i++)//������ʱ������
	{
		for (j = 0; j < a - i; j++)
		{
			if (b[j].arrive > b[j + 1].arrive)	//������ʱ��̵Ľ�����ǰ��
			{
				t = b[j];
				b[j] = b[j + 1];
				b[j + 1] = t;
				flag ++;//����
			}
		}
		if (flag == 0)//���һ��������û�����κν��������������	
		{
			break;
		}
 
	}
	cout << "������ʱ�����򹲽���" << flag << "��"<<endl;
	buffer.push(&b[0]);
	b[0].state = "����";
	int round = 1;
	nowtime = b[0].arrive;//��һ�ο�ʼʱ�伴Ϊ����ʱ��������һ�Ľ��̵ĵ���ʱ��
	int n = 1;
	while (!buffer.empty())
	{
		for (int m = n; m< a; m++)//����������һ�Ľ��̺ͺ���ͬʱ��������
		{
			if (nowtime >= b[m].arrive)
			{
				b[m].state = "����";
				buffer.push(&b[m]);
				n++;
			}
		}
		temp = buffer.front()->rest;
		nowtime += slice;
		buffer.front()->rest = buffer.front()->rest - slice;
		buffer.front()->state = "������";
		cout << "\n-----------------------------------------------\n";
		cout << "��" << round<<"��"<<" "<<buffer.front()->name<<" ������" << endl;
		if (buffer.front()->rest <= 0)
		{
			buffer.front()->finish = nowtime - slice + temp;
			nowtime = buffer.front()->finish;
			buffer.front()->zhouzhuan = nowtime - buffer.front()->arrive;
			buffer.front()->daiquan = buffer.front()->zhouzhuan / buffer.front()->run;
			sum_zhouzhuan += buffer.front()->zhouzhuan;
			sum_daiquan += buffer.front()->daiquan;
			buffer.front()->rest = 0;
			buffer.front()->state = "�������";
			cout << "���: ����  " << buffer.front()->name << "  " << "�ڵ�" << buffer.front()->finish <<"��ʱ��Ƭ�������"<< "  ��תʱ��=" << buffer.front()->zhouzhuan <<"  ��Ȩ��תʱ��="<< buffer.front()->daiquan <<" ����="<<round<< endl;
			cout << "\n-----------------------------------------------\n";
			buffer.pop();
			for (int m = n; m< a; m++)//���ǽ��̻�δ����������Լ��������ǰ�������������������ʱ��������
			{
				if (nowtime >= b[m].arrive)
				{
					b[m].state = "����";
					buffer.push(&b[m]);
					n++;
				}
				if ((nowtime < b[m].arrive) && (buffer.empty()))
				{
					cout << "\n---------------����״̬--------------\n";
					cout << "|"<<" ������ ";
					cout << "|"<< setw(2) << " ����ʱ�� ";
					cout << "|"<< setw(2) << " ����ʱ�� ";
					cout << "|"<< setw(2) << " ʣ��ʱ�� ";
					cout << "|"<< "      ״̬        "<<"|"<< endl;
					for (int p = 0; p < a; p++)
					{
						cout << setw(5)<< b[p].name <<" ";
						cout << setw(10)<< b[p].arrive << " ";
						cout << setw(10)<< b[p].run << " ";
						cout << setw(10)<< b[p].rest << "      ";
						cout << b[p].state;
						cout << endl;
					}
					cout << "�п������" << endl;
					cout << "��" << b[m].arrive - nowtime << "������ʱ���ڵȴ�" << endl;
					cout << "\n---------------�ȴ����--------------\n";
					cout << "������" << b[m].name << " ����ʱ" << endl << "ʱ��Ϊ��" << b[m].arrive << endl;
					b[m].state = "����";
					nowtime = b[m].arrive;
					buffer.push(&b[m]);
					n++;
				}
			}
		}
		else
		{
			for (int m = n; m< a; m++)//���ǽ�����ʱ��Ƭ����ǰ��������
			{
				if (nowtime >= b[m].arrive)
				{
					b[m].state = "����";
					buffer.push(&b[m]);
					n++;
				}
			}
			buffer.front()->state = "�ȴ���һ��ʱ��Ƭ";
			buffer.push(buffer.front());
			buffer.pop();
		}
		cout << "|"<<" ������ ";
		cout << "|"<< setw(2) << " ����ʱ�� ";
		cout << "|"<< setw(2) << " ����ʱ�� ";
		cout << "|"<< setw(2) << " ʣ��ʱ�� ";
		cout << "|"<< "      ״̬        "<<"|"<< endl;
		for (int p = 0; p < a; p++)
		{
			cout << setw(5)<< b[p].name <<" ";
			cout << setw(10)<< b[p].arrive << " ";
			cout << setw(10)<< b[p].run << " ";
			cout << setw(10)<< b[p].rest << "      ";
			cout << setiosflags(ios::left)<<b[p].state;
			cout << endl;
		}
		round++;
	}
	printf("\n����תʱ�䣺 ");
	printf("%f", sum_zhouzhuan);
	printf("\n�ܴ�Ȩ��תʱ�䣺 ");
	printf("%f\n", sum_daiquan);
	avr_zhouzhuan = sum_zhouzhuan / a;
	avr_daiquan = sum_daiquan / a;
	printf("\nƽ����תʱ�䣺 ");
	printf("%f", avr_zhouzhuan);
	printf("\nƽ����Ȩ��תʱ�䣺 ");
	printf("%f\n", avr_daiquan);
}
 
int main()
{
	float t1 = 0.0f;	//����תʱ��
	float t2 = 0.0f;	//�ܴ�Ȩ��תʱ��
	float avr_t1 = 0.0f;	//ƽ����תʱ��
	float avr_t2 = 0.0f;	//ƽ����Ȩ��תʱ��
	int n, i;
	char select = ' ';	//ѡ���㷨������ʶ
	while (select != 'e' && select != 'E')	//��Ϊ�˳���ʶ������ѭ��
	{
		system("cls");
		cout<<"=================���̵����㷨================"<<endl;;
		cout<<"=================���ӽ� 2017040314================"<<endl;
		printf("��ѡ���㷨��\na.ʱ��Ƭ��ת�㷨\nb.���ȼ��㷨\nc.�˳�����\n����ѡ���ַ����:  ");
		scanf("%c", &select);
		if (select == 'a' || select == 'A')	//ʱ��Ƭ��ת�㷨
		{
			printf("\n\n=================ʱ��Ƭ��ת�㷨RR================\n\n");
			int a;
			printf("�����������: ");
			scanf("%d", &a);
			RR(a);
			system("pause");
		}
		else if (select == 'b' || select == 'B')	//���ȼ��㷨r
		{
			printf("\n\n=================���ȼ��㷨r================\n\n");
			printf("�������������");
			scanf("%d", &n);
			for (i = 0; i<n; i++)
			{
				printf("%d ������:", i + 1);
				scanf("%s", &a[i].name);
				printf("����ʱ��: ");
				scanf("%f", &a[i].arrivetime);
				printf("����ʱ�䣺");
				scanf("%f", &a[i].servetime);
				printf("���ȼ�:");
				scanf("%d", &a[i].priority);
			}
			sortpriority(a, n);	//ð������
			r(a, n, t1, t2);	//���ȼ��㷨r
			avr_t1 = t1 / n;
			avr_t2 = t2 / n;
			printf("\n");
			printf("ƽ����תʱ��Ϊ��%f \n", avr_t1);
			printf("ƽ����Ȩ��תʱ��Ϊ��%f \n", avr_t2);
			system("pause");
		}
		else if (select == 'c' || select == 'C')
		{
			exit(0);
		}
		else {
			cout<< "please inter right choose!" << endl;
			system("pause");
		}
 
	}
	system("pause");
}
 
