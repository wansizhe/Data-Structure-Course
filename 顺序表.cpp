#include<iostream>
#include <stdio.h>
using namespace std;

struct list
{
	int length;
	int* first;
};

//��ӡ
void display(list &l)
{
	if (l.length <= 0 || l.first == 0)
	{
		//cout << "�޷���ӡ��" << endl;
		return;
	}
	for (int i = 0; i <= l.length - 1; i++)
		cout << l.first[i] << '\t';
	cout << endl;
	return;
}

//��ʼ��
void initialize(list& l)
{
	if (l.length <= 0 || l.first == NULL)
	{
		//cout << "�޷���ʼ����" << endl;
		return;
	}
	cout << "������" << l.length << "������" << endl;
	for (int i = 0; i <= l.length - 1; i++)
		cin >> l.first[i];
	//cout << endl << "��ʼ���ɹ���" << endl;
	return;
}

//����
void creatlist(list& intlist, int len)
{
	intlist.length = len;
	intlist.first = new int[len];
	//cout << "�����ɹ���" << endl;
	return;
}

//����
void listinsert(list& l, int i, int e)
{
	if (i<1 || i>l.length + 1 || l.length <= 0 || l.first == NULL)
	{
		//cout << "����ʧ�ܣ�" << endl;
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
	//cout << "����ɹ���" << endl;
	return;
}

//�ǵݼ�����
void ilistinsert(list& l, int e)
{
	if ( l.length <= 0 || l.first == NULL)
	{
		//cout << "����ʧ�ܣ�" << endl;
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

//ɾ��
void listdelete(list& l, int i, int& e)
{
	if (l.first == 0 || l.length <= 0 || i<1 || i>l.length)
	{
		//cout << "ɾ��ʧ�ܣ�" << endl;
		return;
	}
	l.length--;
	int j = i;
	e = l.first[i - 1];
	for (; j <= l.length; j++)
		l.first[j - 1] = l.first[j];
	//delete &l.first[l.length];
	//cout << "ɾ���ɹ���" << endl;
	return;
}

//����
void destroylist(list& l)
{
	if (l.first != 0)
		delete l.first;
	l.length = 0;
	//cout << "���ٳɹ���" << endl;
	return;
}

//����
int locateelem(list l, int e)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "����ʧ�ܣ�" << endl;
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
		//cout << "���ҳɹ����ǵ�" << i + 1 << "��Ԫ�ء�" << endl;
		return i + 1;
	}
	else
	{
		//cout << "δ���ҵ���ӦԪ�أ�" << endl;
		return 0;
	}
}

//�ǵݼ� �ϲ�
void mergelists(list &l1, list& l2)
{
	if (l1.first == 0 && l2.first == 0 || l1.length == 0 && l2.length == 0)
	{
		//cout << "�ϲ�ʧ�ܣ�" << endl;
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

//���
void clearlist(list& l)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "���ʧ�ܣ�" << endl;
		return;
	}
	l.length = 0;
	//cout << "��ճɹ���" << endl;
	return;
}

//����
void reverselist(list& l)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "����ʧ�ܣ�" << endl;
		return;
	}
	int *p = l.first;
	l.first = new int[l.length];
	int j = l.length - 1;
	for (int i = 0; i <= l.length - 1; i++)
		l.first[i] = p[j - i];
	//cout << "���óɹ���" << endl;
	return;
}

//ɾ����һ��e
void delete_e(list& l,int e)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "ɾ���ɹ���" << endl;
		return;
	}
	int de;
	listdelete(l, locateelem(l, e), de);
	return;
}

//ɾ������e
void delete_alle(list& l, int e)
{
	if (l.first == 0 || l.length <= 0)
	{
		//cout << "ɾ���ɹ���" << endl;
		return;
	}
	int de;
	while (locateelem(l, e) != 0)
	{
		listdelete(l, locateelem(l, e), de);
	}
	return;
}

//ɾ������e
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


//����
int main()
{
	list l;
	cout << "����˳���L1��Enter������..." << endl;
	getchar();
	creatlist(l, 10);
	cout << "�����ɹ���" << endl;
	cout << endl;

	cout << "��ʼ��˳���L1��Enter������..." << endl;
	getchar();
	initialize(l);
	cout << endl << "��ʼ���ɹ���" << endl;
	display(l);
	cout << endl;

	cout << "ɾ��˳���L1�ж���Ԫ�أ�Enter������..." << endl;
	getchar();
	delete_spr(l);
	cout << endl << "ɾ���ɹ���" << endl;
	display(l);
	cout << endl;
	
	cout << "��˳���L1�в���Ԫ�أ�Enter������..." << endl;
	getchar();
	getchar();
	int a, b;
	cout << "����������λ�ã�ǰ���룬1-"<<l.length+1<<"���Ͳ����Ԫ�أ�";
	cin >> a >> b;
	listinsert(l, a, b);
	cout << "����ɹ���" << endl;
	display(l);
	cout << endl;

	int e;
	cout << "��˳���L1��ɾ��Ԫ�أ�Enter������..." << endl;
	getchar();
	cout << "������Ҫɾ����Ԫ�ص�λ�ã�ǰɾ����1-"<<l.length<<"����";
	cin >> a ;
	listdelete(l, a, e);
	cout << endl << "ɾ���ɹ���" << endl;
	display(l);
	cout << endl;

	cout << "��˳���L1�в���Ԫ�أ�Enter������..." << endl;
	getchar();
	cout << "������Ҫ���ҵ�Ԫ�أ�";
	cin >> a;
	int k=locateelem(l, a);
	if (k!=0)
	{
		cout << "���ҳɹ����ǵ�" << k<< "��Ԫ�ء�" << endl;
	}
	else
	{
		cout << "δ���ҵ���ӦԪ�أ�" << endl;
	}
	cout << endl;

	cout << "��˳���L1�в���Ԫ�أ�Enter������..." << endl;
	getchar();
	cout << "������Ҫ���ҵ�Ԫ�أ�";
	cin >> a;
	k=locateelem(l, a);
	if (k != 0)
	{
		cout << "���ҳɹ����ǵ�" << k + 1 << "��Ԫ�ء�" << endl;
	}
	else
	{
		cout << "δ���ҵ���ӦԪ�أ�" << endl;
	}
	cout << endl;

	list ll;
	cout << "����˳���L2��Enter������..." << endl;
	getchar();
	creatlist(ll, 3);
	cout << "�����ɹ���" << endl;
	cout << endl;

	cout << "��ʼ��˳���L2��Enter������..." << endl;
	getchar();
	initialize(ll);
	cout << endl << "��ʼ���ɹ���" << endl;
	display(ll);
	cout << endl;

	cout << "�ϲ�˳���L1��L2ΪL1��Enter������..." << endl;
	getchar();
	mergelists(l, ll);
	cout << "�ϲ��ɹ���" << endl;
	display(l);
	cout << endl;

	cout << "����˳���L1��Enter������..." << endl;
	getchar();
	reverselist(l);
	cout << "���óɹ���" << endl;
	display(l);
	cout << endl;

	cout << "ɾ��L1��Ԫ��e��Enter������..." << endl;
	getchar();
	getchar();
	cout << "������Ҫɾ����Ԫ�أ�";
	cin >> a;
	delete_e(l, a);
	cout << endl << "ɾ���ɹ���" << endl;
	display(l);
	cout<< endl;

	cout << "ɾ��L1������Ԫ��e��Enter������..." << endl;
	getchar();
	cout << "������Ҫɾ����Ԫ�أ�";
	cin >> a;
	delete_alle(l, a);
	cout << endl << "ɾ���ɹ���" << endl;
	display(l);
	cout << endl;

	cout << "���˳���L1��Enter������..." << endl;
	getchar();
	clearlist(l);
	cout << "��ճɹ���" << endl;
	cout << endl;


	cout << "����˳���L1��L2��Enter������..." << endl;
	getchar();
	destroylist(l);
	destroylist(ll);
	cout << "��ճɹ���" << endl;

	getchar();
	return 0;
}