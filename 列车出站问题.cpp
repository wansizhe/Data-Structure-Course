#include<iostream>
#include<string>
using namespace std;
int n = 0;

/*判断是否可以是出站序列*/
int is_order(char* a,int len)
{
	for(int i=0;i<len;i++)
	{
		char b = a[i];

				/*当前字母之后的序列里，*/
				/*如果出现若干比当前字母小的字母，*/
				/*它们必须按字母由大到小的顺序出现*/
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

/*求序列全排列函数，递归法*/
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
	char list[10];	//最多10辆车
	cin >> list;

	cout << endl;
	perm(list, 0, strlen(list) - 1,strlen(list));
	cout << endl;
	return 0;
}