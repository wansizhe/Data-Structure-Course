#include<iostream>
#include <stdio.h>
using namespace std;

struct list
{
	int length;
	int* first;
};

//打印
void display(list &l)
{
	if (l.length <= 0 || l.first == 0)
	{
		//cout << "无法打印！" << endl;
		return;
	}
	for (int i = 0; i <= l.length - 1; i++)
		cout << l.first[i] << '\t';
	cout << endl;
	return;
}

//初始化
void initialize(list& l)
{
	if (l.length <= 0 || l.first == NULL)
	{
		//cout << "无法初始化！" << endl;
		return;
	}
	cout << "请输入" << l.length << "个数：" << endl;
	for (int i = 0; i <= l.length - 1; i++)
		cin >> l.first[i];
	//cout << endl << "初始化成功！" << endl;
	return;
}

//创建
void creatlist(list& intlist, int len)
{
	intlist.length = len;
	intlist.first = new int[len];
	//cout << "创建成功！" << endl;
	return;
}

//插入
void listinsert(list& l, int i, int e)
{
	if (i<1 || i>l.length + 1 || l.length <= 0 || l.first == NULL)
	{
		//cout << "插入失败！" << endl;
		return;
	}
	l.length++;
	int* p = l.first;
	l.first = new int[l.length];
	int j;
	for (j = 0; j <= i - 2; j++)
		l.first[j] = p[j];
	int k = j;
	l.first[j] = e;
	j++;
	for (; j <= l.length - 1;)
	{
		l.first[j] = p[k];
		j++;
		k++;
	}
	delete p;
	//cout << "插入成功！" << endl;
	return;
}

//非递减插入
void ilistinsert(list& l, int e)
{
	if ( l.length <= 0 || l.first == NULL)
	{
		//cout << "插入失败！" << endl;
		return;
	}
	int i = -1, j = 0;
	while (i == -1)
	{
		if (j + 1 <= l.length - 1 && l.first[j] <= e&&l.first[j + 1] > e)
			i = j + 1;
		else if (j == l.length - 1)
			i = j + 1;
		j++;
	}
	listinsert(l, i + 1, e);
	return;
}

//删除
void listdelete(list& l, int i, int& e)
{
	if (l.first == 0 || l.length <= 0 || i<1 || i>l.length)
	{
		//cout << "删除失败！" << endl;
		return;
	}
	l.length--;
	int j = i;
	e = l.first[i - 1];
	for (; j <= l.length; j++)
		l.first[j - 1] = l.first[j];
	//delete &l.first[l.length];
	//cout << "删除成功！" << endl;
	return;
}

//销毁
void destroylist(list& l)
{
	if (l.first != 0)
		delete l.first;
	l.length = 0;
	//cout << "销毁成功！" << endl;
	return;
}

//查找
int locateelem(list l, int e)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "查找失败！" << endl;
		return 0;
	}
	bool get = false;
	int i = 0;
	for (; i <= l.length - 1; i++)
	{
		if (l.first[i] == e)
			get = true;
		if (get)
			break;
	}
	if (get)
	{
		//cout << "查找成功！是第" << i + 1 << "个元素。" << endl;
		return i + 1;
	}
	else
	{
		//cout << "未查找到相应元素！" << endl;
		return 0;
	}
}

//非递减 合并
void mergelists(list &l1, list& l2)
{
	if (l1.first == 0 && l2.first == 0 || l1.length == 0 && l2.length == 0)
	{
		//cout << "合并失败！" << endl;
		return;
	}
	else if (l1.first == 0 || l1.length == 0)
	{
		int *p, t;
		t = l1.length;
		p = l1.first;
		l1.first = l2.first;
		l1.length = l2.length;
		l2.first = p;
		l2.length = t;
	}
	else if (l2.first == 0 || l2.length == 0)
	{
		return;
	}
	else
	{
		int i = 0, j = 0, k = 0;
		int *p = new int[l1.length + l2.length];
		while (i<=l1.length-1&&j<=l2.length-1)
		{
			if (l1.first[i] <= l2.first[j])
			{
				p[k] = l1.first[i];
				if (i <= l1.length - 1)
					i++;
				k++;
			}
			else
			{
				p[k] = l2.first[j];
				if (j <= l2.length - 1)
					j++;
				k++;
			}
		}
		if (i == l1.length)
		{
			for (; k <= l1.length + l2.length - 1; k++)
			{
				p[k] = l2.first[j];
				j++;
			}
		}
		else
		{
			for (; k <= l1.length + l2.length - 1; k++)
			{
				p[k] = l1.first[i];
				i++;
			}
		}
		l1.length = l1.length + l2.length;
		delete l1.first;
		l1.first = p;
	}
	return;
}

//清空
void clearlist(list& l)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "清空失败！" << endl;
		return;
	}
	l.length = 0;
	//cout << "清空成功！" << endl;
	return;
}

//逆置
void reverselist(list& l)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "逆置失败！" << endl;
		return;
	}
	int *p = l.first;
	l.first = new int[l.length];
	int j = l.length - 1;
	for (int i = 0; i <= l.length - 1; i++)
		l.first[i] = p[j - i];
	//cout << "逆置成功！" << endl;
	return;
}

//删除第一个e
void delete_e(list& l,int e)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "删除成功！" << endl;
		return;
	}
	int de;
	listdelete(l, locateelem(l, e), de);
	return;
}

//删除所有e
void delete_alle(list& l, int e)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "删除成功！" << endl;
		return;
	}
	int de;
	while (locateelem(l, e) != 0)
	{
		listdelete(l, locateelem(l, e), de);
	}
	return;
}

//删除多余e
void delete_spr(list& l)
{
	for (int i = 0; i <= l.length - 2; )
	{
		if (l.first[i] != l.first[i + 1])
			i++;
		else
			delete_e(l, l.first[i]);
	}
	return;
}


//测试
int main()
{
	list l;
	cout << "创建顺序表L1，Enter键继续..." << endl;
	getchar();
	creatlist(l, 10);
	cout << "创建成功！" << endl;
	cout << endl;

	cout << "初始化顺序表L1，Enter键继续..." << endl;
	getchar();
	initialize(l);
	cout << endl << "初始化成功！" << endl;
	display(l);
	cout << endl;

	cout << "删除顺序表L1中多余元素，Enter键继续..." << endl;
	getchar();
	delete_spr(l);
	cout << endl << "删除成功！" << endl;
	display(l);
	cout << endl;
	
	cout << "在顺序表L1中插入元素，Enter键继续..." << endl;
	getchar();
	getchar();
	int a, b;
	cout << "请输入插入的位置（前插入，1-"<<l.length+1<<"）和插入的元素：";
	cin >> a >> b;
	listinsert(l, a, b);
	cout << "插入成功！" << endl;
	display(l);
	cout << endl;

	int e;
	cout << "在顺序表L1中删除元素，Enter键继续..." << endl;
	getchar();
	cout << "请输入要删除的元素的位置（前删除，1-"<<l.length<<"）：";
	cin >> a ;
	listdelete(l, a, e);
	cout << endl << "删除成功！" << endl;
	display(l);
	cout << endl;

	cout << "在顺序表L1中查找元素，Enter键继续..." << endl;
	getchar();
	cout << "请输入要查找的元素：";
	cin >> a;
	int k=locateelem(l, a);
	if (k!=0)
	{
		cout << "查找成功！是第" << k<< "个元素。" << endl;
	}
	else
	{
		cout << "未查找到相应元素！" << endl;
	}
	cout << endl;

	cout << "在顺序表L1中查找元素，Enter键继续..." << endl;
	getchar();
	cout << "请输入要查找的元素：";
	cin >> a;
	k=locateelem(l, a);
	if (k != 0)
	{
		cout << "查找成功！是第" << k + 1 << "个元素。" << endl;
	}
	else
	{
		cout << "未查找到相应元素！" << endl;
	}
	cout << endl;

	list ll;
	cout << "创建顺序表L2，Enter键继续..." << endl;
	getchar();
	creatlist(ll, 3);
	cout << "创建成功！" << endl;
	cout << endl;

	cout << "初始化顺序表L2，Enter键继续..." << endl;
	getchar();
	initialize(ll);
	cout << endl << "初始化成功！" << endl;
	display(ll);
	cout << endl;

	cout << "合并顺序表L1、L2为L1，Enter键继续..." << endl;
	getchar();
	mergelists(l, ll);
	cout << "合并成功！" << endl;
	display(l);
	cout << endl;

	cout << "逆置顺序表L1，Enter键继续..." << endl;
	getchar();
	reverselist(l);
	cout << "逆置成功！" << endl;
	display(l);
	cout << endl;

	cout << "删除L1中元素e，Enter键继续..." << endl;
	getchar();
	getchar();
	cout << "请输入要删除的元素：";
	cin >> a;
	delete_e(l, a);
	cout << endl << "删除成功！" << endl;
	display(l);
	cout<< endl;

	cout << "删除L1中所有元素e，Enter键继续..." << endl;
	getchar();
	cout << "请输入要删除的元素：";
	cin >> a;
	delete_alle(l, a);
	cout << endl << "删除成功！" << endl;
	display(l);
	cout << endl;

	cout << "清空顺序表L1，Enter键继续..." << endl;
	getchar();
	clearlist(l);
	cout << "清空成功！" << endl;
	cout << endl;


	cout << "销毁顺序表L1、L2，Enter键继续..." << endl;
	getchar();
	destroylist(l);
	destroylist(ll);
	cout << "清空成功！" << endl;

	getchar();
	return 0;
}