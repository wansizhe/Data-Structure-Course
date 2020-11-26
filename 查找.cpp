#include<iostream>
using namespace std;



/*��̬����*/
/*˳���*/
typedef int ktype;
typedef struct
{
	int key;
} etype;

typedef struct
{
	etype *elem;		//0�Ų��洢
	int len;
} SSTab;

		/*˳�����*/
int Search_Seq(SSTab ST, ktype key)
{
	int i;
		/*0��Ϊ������*/
	ST.elem[0].key = key;
	for (i = ST.len; ST.elem[i].key != key; i--);
	return i;		//=0��û�ҵ���>0�ҵ��˶�Ӧ���
}

		/*�۰����		���������*/
int Search_Bin(SSTab ST, ktype key)
{
	int low, high, mid;
	low = 1;
	high = ST.len;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (key == ST.elem[mid].key)
			return mid;
		else if (key < ST.elem[mid].key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}



/*��̬����*/
/*����������*/
typedef struct BiTNode
{
	etype data;
	BiTNode *right, *left;
} *BiTree;

/*��ָ��S�������������*/
void Insert_BST(BiTree &T, BiTree S)
{
	BiTree p, q=NULL;

		/*���T�����ڣ�ֱ�ӳ�ΪS*/
	if (T == NULL)
		T = S;

		/*������뵽ĳ�������*/
	else
	{
		p = T;

			/*�ҵ�Ӧ�����뵽�ĸ�����£���q��ʾ*/
		while (p != NULL)
		{
			q = p;
			if (S->data.key < p->data.key)
				p = p->left;
			else
				p = p->right;
		}

			/*���ն���������������뵽q�����*/
		if (S->data.key < q->data.key)
			q->left = S;
		else
			q->right = S;
	}
	return;
}

/*��������������*/
void CreatBST(BiTree &T)
{
	int x;
	BiTree S;
	T = NULL;		//��Ϊnull

		/*ѭ���������ݣ����н�㹹��������*/
	cin >> x;
	while (x != 0)
	{
		S = new BiTNode;
		S->data.key = x;
		S->left = NULL;
		S->right = NULL;
		Insert_BST(T, S);
		cin >> x;
	}
	//delete s;
	return;
}

/*�ڶ����������в���		�Ѿ����ڷ���1������������벢����0*/
int Search_BST(BiTree T, etype e)
{
	BiTree q=NULL, S, p = T;

		/*Ѱ��e*/
	while (p)
	{
		if (p->data.key == e.key)
			return 1;			//�ҵ����򷵻�1
		else if (p->data.key > e.key)
		{
			q = p;
			p = p->left;		//С����
		}
		else
		{
			q = p;
			p = p->right;		//������
		}
	}

		/*δ�ҵ��������½�㣬����*/
	S = new BiTNode;
	S->data = e;
	S->left = NULL;
	S->right = NULL;
	if (T == NULL)
		T = S;
	else if (q->data.key > e.key)
		q->left = S;	
	else
		q->right = S;

	delete S;
	return 0;	
}

/*ɾ���ҵ��Ľ��*/
void delNode(BiTree &T, BiTree p, BiTree f)
{
	BiTree s, q;
	int tag = 0;

	if (!p->left)
		s = p->right;		//������������
	else if (!p->right)
		s = p->left;			//������������

			/*��������������*/
	else
	{
		q = p;

				/*����������һֱ�������ҵ����ֵ*/
		s = p->left;
		while (s->right)
		{
			q = s;			//q��¼���ֵ���ĸ����
			s = s->right;		//s��¼���������ֵ���
		}
				
		p->data = s->data;		//�������������ֵ����Ҫɾ���Ľ���ϣ���Ϊ�µĽ��
		if (p == q)
			q->left = s->left;		//���ֵ���ĸ�����뱻ɾ�������ͬ��
												//˵����ɾ���������ӽ��û����������������ָ��Ϊnull
												//��ôֻҪ�����ֵ�����������ӵ��丸�����
		else
			q->right = s->left;		//����˵����ɾ������������������
												//���ֵ����������������������ֻ��������������Ӧ�ö������ֵ���ĸ����Ҫ��
												//���������ӵ��丸������ָ����
		delete s;		//�ͷ����ֵ��㣬֮ǰ�Ѿ������Ƶ�Ҫɾ���Ľ������
		tag = 1;		//�����������ڣ���־��Ϊ1
	}

			/*������������һ�������ڣ�������Ҫ�������²���*/
	if (!tag)
	{
		if (!f)
			T = s;		//�����ɾ�����Ϊ����㣬
							//�����һ�����ӣ��������ĺ��ӳ�Ϊ�����
		else if (f->left == p)
			f->left = s;			//�����ɾ��������丸��������
										//��ɾ������������������ȸ����С��
										//����ɾ���������������һ�����ӵ���������ָ����
		else
			f->right = s;		//�����ɾ��������丸�����Һ���
										//��ɾ������������������ȸ�����
										//����ɾ���������������һ�����ӵ���������ָ����
		delete p;		//�ͷű�ɾ�����
	}

	/*����*/
	return;
}


/*�ڶ�����������Ѱ��Ҫɾ��һ��Ԫ�ز�ɾ��*/
int Delete_BST(BiTree &T, int key)
{
	BiTree p, f;
	p = T;
	f = NULL;

			/*Ѱ��Ҫɾ���Ľ��*/
	while (p)
	{
				/*�ڵ�ǰ����ҵ���ɾ��*/
		if (p->data.key == key)
		{
			delNode(T, p, f);
			return 1;
		}

				/*�ȵ�ǰ���С��������*/
		else if (p->data.key > key)
		{
			f = p;
			p = p->left;
		}

				/*�ȵ�ǰ������������*/
		else
		{
			f = p;
			p = p->right;
		}
	}
	return 0;
}

int main()
{
	etype stab[10];
	for (int i = 0; i < 10; i++)
	{
		stab[i].key = i;
		cout << i << ' ';
	}
	cout << endl;
	SSTab t;
	t.elem = stab;
	t.len = 9;
	cout << "����11�������";
	cout << t.elem[Search_Bin(t, 11)].key << endl;			//0
	cout << "����2�������";
	cout << t.elem[Search_Bin(t, 2)].key << endl;			//2

	BiTree bt;
	etype temp;
	cout << "����һ������������������������0����" << endl;
	CreatBST(bt);
	cout << "���ң�"<<endl;
	cin >> temp.key;
	cout << "�����" << Search_BST(bt, temp) << endl;
	cin >> temp.key;
	cout << "�����" << Search_BST(bt, temp) << endl;

	cout << endl << "ɾ����" << endl;
	cin >> temp.key;
	Delete_BST(bt, temp.key);
	cout<<"���Ҹ�Ԫ�أ������"<< Search_BST(bt, temp) << endl;

	return 0;
}

