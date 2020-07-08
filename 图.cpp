#include<iostream>
#include<iomanip>
using namespace std;
#define	INFINITY 2147483647

#define MAX 10	//最大顶点数
typedef int AdjMatrix[MAX][MAX];	//定义邻接矩阵类型
typedef char vtype;

/*队列类*/
#define max 21
typedef int atype;
class cyc_queue
{
public:
	int front;
	int rear;
	atype* base;

	cyc_queue();
	~cyc_queue();
	void initial();
	int getlen();
	void enqueue(atype e);
	void dequeue(atype &e);
	int is_empty();
	void gethead(atype &e);
	void display();
};
cyc_queue::cyc_queue()
{
	front = 0;
	rear = 0;
	base = NULL;
}
cyc_queue::~cyc_queue()
{
	if (base != NULL)
		delete base;
}
void cyc_queue::initial()
{
	base = new atype[max];
	front = 0;
	rear = 0;
	return;
}
int cyc_queue::getlen()
{
	return (rear - front + max) % max;
}
void cyc_queue::enqueue(atype e)
{
	if ((rear + 1) % max == front)
		return;
	base[rear] = e;
	rear = (rear + 1) % max;
	return;
}
void cyc_queue::dequeue(atype &e)
{
	if (rear == front)
		return;
	e = base[front];
	front = (front + 1) % max;
	return;
}
int cyc_queue::is_empty()
{
	if (rear == front)
		return 1;
	else
		return 0;
}
void cyc_queue::gethead(atype &e)
{
	if (rear == front)
		return;
	e = base[front];
	return;
}
void cyc_queue::display()
{
	for (int i = front; i < rear;)
	{
		cout << base[i] << "  ";
		i = (i + 1) % max;
	}
	cout << endl;
	return;
}


/*邻接矩阵-图*/
struct MGraph
{
	vtype vexs[MAX];	//所有顶点构成顶点表
	AdjMatrix arcs;	//邻接矩阵
					//INFINITY 表示不连通，非负数表示权值
	int vnum, anum;	//边数，顶点数
};
MGraph G1, G2;

/*确定某一顶点在顶点表中的位置*/
int LocateVex(MGraph G, vtype u)
{
	int i;
	for (i = 0; i<G.vnum; i++)
		if (u == G.vexs[i])
			break;
	if (i == G.vnum)
		i = -1;
	return i;
}

/*建立邻接矩阵*/
void CreateMG(MGraph &G)
{
	int i, j, k, w;	//i、j、k为计数器，w保存权值的中间变量
	vtype v1, v2;	//保存顶点的中间变量

	cout << "依次输入顶点数和边数：";
	cin >> G.vnum >> G.anum;
	cout << "依次输入所有顶点：";
	for (i = 0; i<G.vnum; i++)
		cin >> G.vexs[i];

	/*初始化矩阵*/
	for (i = 0; i<G.vnum; i++)
		for (j = 0; j<G.vnum; j++)
			G.arcs[i][j] = INFINITY;

	/*构建过程*/
	for (k = 0; k<G.anum; k++)
	{
		cout << "输入第" << k << "对相连顶点及边的权值" << endl;
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j] = w;
		//G.arcs[j][i]=w;	//无向图加此句
	}
	return;
}

/*打印邻接矩阵*/
void PrintMG(MGraph G)
{
	int i, j;
	cout << endl;
	cout << "  ";
	for (i = 0; i<G.vnum; i++)
		cout <<setw(2)<< G.vexs[i] << ' ';
	cout << endl;
	for (i = 0; i<G.vnum; i++)
	{
		cout << ' ' << G.vexs[i];
		for (j = 0; j<G.vnum; j++)
			cout << setw(2)<< G.arcs[i][j] << ' ';
		cout << endl;
	}
	return;
}

/*边结点*/
struct ANode	
{
	int adjvex;	//在图中指向的下一个顶点，用其在头结点数组里的标号表示
	ANode* next;	//链表中指向下一个结点的指针
	int info;	//边的权值
};
/*邻接表头结点*/
struct VNode	
{
	vtype data;
	int indegree;
	ANode* first/*=NULL*/;
};
typedef VNode AdjList[MAX];	//邻接表头结点数组 类型

							/*邻接表-图*/
struct LGraph
{
	AdjList vert;
	int vnum, anum;
	//int kind;
};
LGraph G3,G4;

/*确定某一顶点在顶点表中的位置*/
int LocateVex(LGraph G, vtype u)
{
	int i;
	for (i = 0; i<G.vnum; i++)
		if (u == G.vert[i].data)
			break;
	if (i == G.vnum)
		i = -1;
	return i;
}

/*建立邻接表*/
void CreateLG(LGraph &G)
{
	int i, j, k, w;
	char v1, v2;
	ANode* p;
	cout << "依次输入顶点数和边数：";
	cin >> G.vnum >> G.anum;
	cout << "依次输入所有顶点：";
	for (i = 0; i<G.vnum; i++)
	{
		cin >> G.vert[i].data;	//初始化头结点数组，即得到图中所有顶点
		G.vert[i].first = NULL;	//头结点最初指向null
	}

	cout << "输入第对相连顶点及边的权值" << endl;
	for (k = 0; k<G.vnum; k++)
	{
		cin >> v1 >> v2 >> w;
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);	//得到边两端顶点在头结点数组里的标号
		p = new ANode;
		p->adjvex = j;
		p->info = w;
		p->next = G.vert[i].first;
		G.vert[i].first = p;		//头插法加入结点
	}
	return;
}

/*打印邻接表*/
void PrintLG(LGraph G)
{
	int i;
	ANode* p;
	for (i = 0; i<G.vnum; i++)
	{
		cout << G.vert[i].data << " |-> ";
		p = G.vert[i].first;
		while (p != NULL)
		{
			cout << '(' << p->info << ')' << p->adjvex << " ->";
			p = p->next;
		}
		cout << endl;
	}
	return;
}


int visited[MAX];	//标记是否已经访问过

					/*从一个顶点出发点深度优先遍历*/
void DFS(LGraph G, int v)	//v是起始顶点的标号
{
	ANode *p;
	cout << G.vert[v].data << ' ';
	visited[v] = 1;
	p = G.vert[v].first;
	while (p != NULL)
	{
		if (visited[p->adjvex] == 0)
			DFS(G, p->adjvex);
		p = p->next;
	}
	return;
}

/*对全图的深度优先遍历*/
void DFST(LGraph G)
{
	for (int i = 0; i<G.vnum; i++)
		visited[i] = 0;
	for (int i = 0; i<G.vnum; i++)
		if (visited[i] == 0)
			DFS(G, i);
	return;
}

/*从一个顶点出发点广度优先遍历*/
void BFS(LGraph G, int v)
{
	ANode *p;
	cyc_queue Q;	//队列Q
	Q.initial();	//队列初始化
	cout << G.vert[v].data << ' ';
	visited[v] = 1;
	Q.enqueue(v);	//起始点入队
	while (Q.is_empty())
	{
		Q.dequeue(v);	//出队一个顶点标号,赋给v
		p = G.vert[v].first;
		while (p != NULL)
		{
			if (visited[p->adjvex])
			{
				cout << G.vert[p->adjvex].data << ' ';
				visited[p->adjvex] = 1;
				Q.enqueue(p->adjvex);		//当前顶点入队；
			}
			p = p->next;
		}
	}
	return;
}

/*对全图的广度优先遍历*/
void BFST(LGraph G)
{
	for (int i = 0; i<G.vnum; i++)
		visited[i] = 0;
	for (int i = 0; i<G.vnum; i++)
		if (visited[i] == 0)
			BFS(G, i);
	return;
}


/*Prim算法实现最小生成树		用邻接矩阵*/
struct
{
	vtype adj;
	int lowcost;
} closedge[MAX];

void MinSpanTree_Prim(MGraph G, vtype u)
{
	int k, j, i, mincost;
	k = LocateVex(G, u);

	/*初始化辅助数组*/
	for (j=0;j<G.vnum;j++)
		if (j != k)
		{
			closedge[j].adj = u;		//连接点初始为起始点u
			closedge[j].lowcost = G.arcs[k][j];		//最小权值为 到起始点u最小距离
		}
	closedge[k].lowcost = 0;

	/*构造最小生成树*/
	for (i = 1; i < G.vnum; i++)
	{
		
		/*找到到u点的最小距离点*/
		mincost = INFINITY;
		for (j = 0; j < G.vnum; j++)		//遍历所有点，找到最小权值
			if (closedge[j].lowcost < mincost&&closedge[j].lowcost != 0)
			{
				mincost = closedge[j].lowcost;
				k = j;
			}
		/*标号为k的点是到u点距离最短的*/

		cout << closedge[k].adj << G.vexs[k] << ' ';

		/*将该点归入最小生成树点集，对辅助数组进行调整*/
		closedge[k].lowcost = 0;
		for(j=0;j<G.vnum;j++)	
			if (G.arcs[k][j] < closedge[j].lowcost)		//如果辅助数组中存的权值 比 到刚加入集合的点的距离 大
			{
				closedge[j].adj = G.vexs[k];		//将连接点改为刚刚加入的点
				closedge[j].lowcost = G.arcs[k][j];		//保存较小的权值
			}
	}
	return;
}

/*拓扑排序		用邻接表*/
int TopSort(LGraph G)
{
	ANode  *p;
	int k;
	//FindIndegree(G,indegree);

			/*在入度数组中灵活操作，完成栈的功能，达到节省空间的目的，技巧性强*/
	int top = -1;
	for (int i = 0; i < G.vnum; i++)
		if (G.vert[i].indegree == 0)
		{
			G.vert[i].indegree = top;		//将最初的入度为0的点“入栈”
			top = i;
		}
	int count = 0;		//记录访问点的个数，判断是否有环的依据
	while (top + 1 != 0)
	{
		int i = top;
		top = G.vert[top].indegree;		//“出栈”一个入度为0的点，访问它
		cout << " (" << i << G.vert[i].data << ") ";
		count++;
		for (p=G.vert[i].first;p!=NULL;p=p->next)
		{
			k = p->adjvex;
			G.vert[k].indegree--;		//“删去”已访问的点，“删去”以该点为弧尾的边，弧头点入度减一
			if (G.vert[k].indegree == 0)
			{
				G.vert[k].indegree = top;		//将新产生的入度为0的点“入栈”
				top = k;
			}
		}
	}
	if (count < G.vnum)
		return 0;		//存在环，排序未完成
	else
		return 1;
}

/*关键路径		用邻接表，基于拓扑排序*/
void CriPath(LGraph G)
{
	int i, j, k,e, l;
	int *ve, *vl;		//ve：最早可能开始时间；vl：最迟允许开始时间
	ANode *p;
	ve=new int [G.vnum];
	vl = new int[G.vnum];

	/*操作ve数组*/
	for (i = 0; i < G.vnum; i++)
		ve[i] = 0;
	for (i = 0; i < G.vnum; i++)
	{
		p = G.vert[i].first;
		while (p != NULL)
		{
			k = p->adjvex;
			/*正向找到最大路径*/
			if (ve[i] + p->info > ve[k])
				ve[k] = ve[i] + p->info;
			p = p->next;
		}
	}


	/*操作vl数组*/
	for (i = 0; i < G.vnum; i++)
		vl[i] = ve[G.vnum - 1];
	for (i = G.vnum - 2; i != 0; i--)
	{
		p = G.vert[i].first;
		while (p != NULL)
		{
			k = p->adjvex;
			/*逆向找到最短路径*/
			if (vl[k] - p->info < vl[i])
				vl[i] = vl[k] - p->info;
			p = p->next;
		}
	}


	/*打印关键活动*/
	for (i = 0; i < G.vnum; i++)
	{
		p = G.vert[i].first;
		while (p != NULL)
		{
			k = p->adjvex;
			e = ve[i];
			l = vl[k] - p->info;
			/*以vl和ve之差作为判断是否是关键活动的依据*/
			char tag = (e == l) ? '*' : ' ';
			cout << G.vert[i].data << ' ' << G.vert[k].data << ' ' << e << ' ' << l << ' ' << tag << endl;
			p = p->next;
		}
	}
	delete ve;
	delete vl;
	return;
}

/*最短路径		用邻接矩阵*/
typedef int PathM[MAX][MAX];		//最短路径数组，值为0 or 1，矩阵中的元素代表的边是最短路径的一边则置1
typedef int ShPath_Tab[MAX];			//最短路径长度，D[V0]......D[Vn]

void ShorPath_Dij(MGraph G, int v0, PathM &P, ShPath_Tab &D)
{
	int final[MAX];		//用于记录该点是否进入了已求得的最短路径终点集合S
	int w,v;

	/*各状态初始化*/
	for (v = 0; v < G.vnum; v++)
	{
		final[v] = 0;		//所有点不在集合S
		D[v] = G.arcs[v0][v];		//起点到各点的距离按邻接矩阵所记录的复制
		for (w = 0; w < G.vnum; w++)
			P[v][w] = 0;		//标记最短路径的矩阵清零
		if (D[v] < INFINITY)
		{
			P[v][v0] = 1;		//若与起点相连，该边是最短路径
			P[v][v] = 1;			//任一点到自己的最短路径都存在
		}
	}
	D[v0] = 0;		//起点到自己的最短距离为0
	final[v0] = 1;		//起点进入集合S


	/*开始求最短路径，D[v1]—D[vn]*/
	for (int i = 1; i < G.vnum; i++)
	{

			/*求起点到vi点的最短路径和最短距离*/
		int min = INFINITY;		//最小距离初始为无穷大

					/*遍历所有不在集合S中的点*/
		for (w = 0; w < G.vnum; w++)
			if(final[w]==0)		//如果当前点不在集合S中
				if (D[w] < min)		//且起点到该点的距离比已记录的最短距离小
				{
					v = w;		//获取当前点的标号
					min = D[w];		//最小距离更新
				}
		final[v] = 1;		//最后得到的点进入集合S

					/*min为v0到v的最短距离*/
					/*更新D[i]， 以刚才得到的最短距离和对应终点v为准*/
		for (w = 0; w < G.vnum; w++)
			if (final[w] == 0 && (min + G.arcs[v][w] < D[w]))		//如果v0->w的距离比v0->v->w的距离长
			{
							/*更新D*/
				D[w] = min + G.arcs[v][w];
							/*记录最短路径*/
				for (int j = 0; j < G.vnum; j++)
					P[w][j] = P[v][j];
				P[w][w] = 1;
			}
	}

	/*结束*/
	return;
}

int main()
{
	while(1)
	{
		system.cls();
		cout<<"图及其相关操作"<<endl;
		cout<<"1. 邻接矩阵"<<endl;
		cout<<"2. 邻接表"<<endl;
		cout<<"3. 深度优先遍历"<<endl;
		cout<<"4. 广度优先遍历"<<endl;
		cout<<"5. 求最小生成树"<<endl;
		cout<<"6. 求拓扑排序"<<endl;
		cout<<"7. 求关键路径"<<endl;
		cout<<"8. 求最短路径"<<endl;
		cout<<"[请选择 1-8    按Q/q退出...]"<<endl;
		char choice;
		cin>>choice;
		switch(choice)
		{
		case '1':
			MGraph G;
			CreateMG(G);
			PrintMG(G);	
			break;
		case '2':
			LGraph G;
			CreateLG(G);
			PrintLG(G);
			break;
		case '3':
			LGraph G;
			CreateLG(G);
			DFST(G);
			break;
		case '4':
			LGraph G;
			CreateLG(G);
			BFST(G);
			break;
		case '5':
			MGraph G;
			CreateMG(G);
			cout<<endl;
			vtype c;
			cin>>c
			MinSpanTree_Prim(G, c);
			break;
		case '6':
			LGraph G;
			CreateLG(G);
			TopSort(G);
			break;
		case '7':
			LGraph G;
			CreateLG(G);
			CriPath(G);
			break;
		case '8':
			MGraph G;
			CreateMG(G);
			ShorPath_Dij(G, int v0, PathM &P, ShPath_Tab &D);
			break;
		case 'Q':
			break;
		case 'q':
			return 0;
		default:
			break;
		}
	}

	return 0;
}