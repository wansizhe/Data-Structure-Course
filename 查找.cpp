#include<iostream>
using namespace std;



/*静态查找*/
/*顺序表*/
typedef int ktype;
typedef struct
{
	int key;
} etype;

typedef struct
{
	etype *elem;		//0号不存储
	int len;
} SSTab;

		/*顺序查找*/
int Search_Seq(SSTab ST, ktype key)
{
	int i;
		/*0号为监视哨*/
	ST.elem[0].key = key;
	for (i = ST.len; ST.elem[i].key != key; i--);
	return i;		//=0则没找到，>0找到了对应标号
}

		/*折半查找		基于有序表*/
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



/*动态查找*/
/*二叉排序树*/
typedef struct BiTNode
{
	etype data;
	BiTNode *right, *left;
} *BiTree;

/*将指针S插入二叉排序树*/
void Insert_BST(BiTree &T, BiTree S)
{
	BiTree p, q=NULL;

		/*如果T不存在，直接成为S*/
	if (T == NULL)
		T = S;

		/*否则插入到某个结点下*/
	else
	{
		p = T;

			/*找到应当插入到哪个结点下，用q表示*/
		while (p != NULL)
		{
			q = p;
			if (S->data.key < p->data.key)
				p = p->left;
			else
				p = p->right;
		}

			/*按照二叉排序树规则插入到q结点下*/
		if (S->data.key < q->data.key)
			q->left = S;
		else
			q->right = S;
	}
	return;
}

/*创建二叉排序树*/
void CreatBST(BiTree &T)
{
	int x;
	BiTree S;
	T = NULL;		//初为null

		/*循环读入数据，进行结点构建并插入*/
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

/*在二叉排序树中查找		已经存在返回1，不存在则插入并返回0*/
int Search_BST(BiTree T, etype e)
{
	BiTree q=NULL, S, p = T;

		/*寻找e*/
	while (p)
	{
		if (p->data.key == e.key)
			return 1;			//找到，则返回1
		else if (p->data.key > e.key)
		{
			q = p;
			p = p->left;		//小向左
		}
		else
		{
			q = p;
			p = p->right;		//大向右
		}
	}

		/*未找到，构建新结点，插入*/
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

/*删除找到的结点*/
void delNode(BiTree &T, BiTree p, BiTree f)
{
	BiTree s, q;
	int tag = 0;

	if (!p->left)
		s = p->right;		//左子树不存在
	else if (!p->right)
		s = p->left;			//右子树不存在

			/*左右子树都存在*/
	else
	{
		q = p;

				/*在左子树中一直向右找找到最大值*/
		s = p->left;
		while (s->right)
		{
			q = s;			//q记录最大值结点的父结点
			s = s->right;		//s记录左子树最大值结点
		}
				
		p->data = s->data;		//将左子树的最大值赋到要删除的结点上，成为新的结点
		if (p == q)
			q->left = s->left;		//最大值结点的父结点与被删除结点相同，
												//说明被删除结点的左孩子结点没有右子树，即其右指针为null
												//那么只要将最大值结点的左子树接到其父结点上
		else
			q->right = s->left;		//否则说明被删除结点的左孩子有右子树
												//最大值结点的左子树（若有子树则只可能有左子树）应该都比最大值结点的父结点要大
												//将左子树接到其父结点的右指针上
		delete s;		//释放最大值结点，之前已经将它移到要删除的结点上了
		tag = 1;		//左右子树都在，标志记为1
	}

			/*左右子树至少一个不存在，跳出后要进行如下操作*/
	if (!tag)
	{
		if (!f)
			T = s;		//如果被删除结点为根结点，
							//且最多一个孩子，则让它的孩子成为根结点
		else if (f->left == p)
			f->left = s;			//如果被删除结点是其父结点的左孩子
										//被删除结点引出的子树都比父结点小，
										//将被删除结点的子树（最多一个）接到父结点的左指针上
		else
			f->right = s;		//如果被删除结点是其父结点的右孩子
										//被删除结点引出的子树都比父结点大
										//将被删除结点的子树（最多一个）接到父结点的右指针上
		delete p;		//释放被删除结点
	}

	/*结束*/
	return;
}


/*在二叉排序树中寻找要删除一个元素并删除*/
int Delete_BST(BiTree &T, int key)
{
	BiTree p, f;
	p = T;
	f = NULL;

			/*寻找要删除的结点*/
	while (p)
	{
				/*在当前结点找到则删除*/
		if (p->data.key == key)
		{
			delNode(T, p, f);
			return 1;
		}

				/*比当前结点小则向左找*/
		else if (p->data.key > key)
		{
			f = p;
			p = p->left;
		}

				/*比当前结点大则向右找*/
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
	cout << "查找11，结果：";
	cout << t.elem[Search_Bin(t, 11)].key << endl;			//0
	cout << "查找2，结果：";
	cout << t.elem[Search_Bin(t, 2)].key << endl;			//2

	BiTree bt;
	etype temp;
	cout << "输入一串数，建立二叉排序树，以0结束" << endl;
	CreatBST(bt);
	cout << "查找："<<endl;
	cin >> temp.key;
	cout << "结果：" << Search_BST(bt, temp) << endl;
	cin >> temp.key;
	cout << "结果：" << Search_BST(bt, temp) << endl;

	cout << endl << "删除：" << endl;
	cin >> temp.key;
	Delete_BST(bt, temp.key);
	cout<<"查找该元素，结果："<< Search_BST(bt, temp) << endl;

	return 0;
}

