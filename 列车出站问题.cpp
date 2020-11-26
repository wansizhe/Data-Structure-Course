#include<iostream>
#include<string>
using namespace std;
int n = 0;

/*�ж��Ƿ�����ǳ�վ����*/
int is_order(char* a,int len)
{
	for(int i=0;i<len;i++)
	{
		char b = a[i];

				/*��ǰ��ĸ֮��������*/
				/*����������ɱȵ�ǰ��ĸС����ĸ��*/
				/*���Ǳ��밴��ĸ�ɴ�С��˳�����*/
		for (int j = i + 1; j < len; j++)
		{
			if (a[j] < a[i])
			{
				if (a[j] >= b)
					return 0;
				else
					b = a[j];
			}
		}
	}
	return 1;
}

/*������ȫ���к������ݹ鷨*/
void swap(char* a, char *b)
{
	int m;
	m = *a;
	*a = *b;
	*b = m;
	return;
}
void perm(char* list, int k, int m,const int len)
{
	int i;
	if (k > m)
	{
		if (is_order(list, len))
		{
			for (i = 0; i <= m; i++)
				cout << ' ' << list[i];
			cout << endl;
			n++;
		}
	}
	else
	{
		for (i = k; i <= m; i++)
		{
			swap(&list[k], &list[i]);
			perm(list, k + 1, m, len);
			swap(&list[k], &list[i]);
		}
	}
	return;
}

int main()
{
	char list[10];	//���10����
	cin >> list;

	cout << endl;
	perm(list, 0, strlen(list) - 1,strlen(list));
	cout << endl;
	return 0;
}