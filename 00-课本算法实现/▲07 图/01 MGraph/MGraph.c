/***********************************
 *						           *
 * 文件夹: ▲07 图\01 MGraph       *
 * 						           *
 * 文件名: MGraph.c                *
 *    	    			           *
 * 算  法: 7.1、7.2、7.4、7.5、7.6 * 
 *    	    					   *
 ***********************************/

#ifndef MGRAPH_C
#define MGRAPH_C

#include "MGraph.h" 								//**▲07 图**//

/*════╗
║ 算法7.1║ 
╚════*/
//从文件fp里读出图的信息，并构造图G;
Status CreateGraph_M(FILE *fp, MGraph *G)      		//MGraph *G 定义了一个MGraph类型的指针变量，此时分配存储空间； 
{	
	Scanf(fp, "%d", &((*G).kind));					//如第一行 图类型→0（有向图）

	switch((*G).kind)								//随机创建有向图、网或无向图网的一种。 
	{
		case DG:
			return CreateDG_M(fp, G);
		case DN:
			return CreateDN_M(fp, G);
		case UDG:
			return CreateUDG_M(fp, G);
		case UDN:
			return CreateUDN_M(fp, G);
		default:
			return ERROR;
	}
}

Status CreateDG_M(FILE *fp, MGraph *G)
{
	int i, j, k;
	VertexType_M v1, v2;
	char tmp;
	
	Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo)); 
	
	Scanf(fp, "%c", &tmp);						//跳过换行符, 因为换行符也属于字符类型； 

	for(i=1; i<=(*G).vexnum; i++)				//存储顶点信息；
		Scanf(fp, "%c", &((*G).vexs[i]));
	
	Scanf(fp, "%c", &tmp);						//跳过换行符

	for(i=1; i<=(*G).vexnum; i++)				//初始化邻接矩阵, 即零矩阵；
	{
		for(j=1; j<=(*G).vexnum; j++)
			(*G).arcs[i][j].adj = 0;		
	}
	
	for(k=1; k<=(*G).arcnum; k++)				//存储有向图的弧信息；
	{
		Scanf(fp, "%c%c", &v1, &v2);			//弧的集合→◤A，B◢◤B，C◢◤C，A◢◤A，D◢两个两个的字符一起读；
		
		i = LocateVex_M(*G, v1);				//寻找顶点 v1 的位置；
		j = LocateVex_M(*G, v2);
		
		if(!i || !j)
			return ERROR;
		
		(*G).arcs[i][j].adj = 1;
		if((*G).IncInfo==1)						//若有弧的其他信息，则录入; 
			Input(fp, &((*G).arcs[i][j].info));
	}
	
	return OK;	
}


Status CreateDN_M(FILE *fp, MGraph *G)
{
	int i, j, k;
	VertexType_M v1, v2;
	VRType w;
	char tmp;
	
	Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	Scanf(fp, "%c", &tmp);						//跳过换行符 
	
	for(i=1; i<=(*G).vexnum; i++)				//存储顶点信息；
		Scanf(fp, "%c", &((*G).vexs[i]));

	Scanf(fp, "%c", &tmp);						//跳过换行符
	
	for(i=1; i<=(*G).vexnum; i++)				//初始化邻接矩阵, 全部初始化为无穷大；
	{
		for(j=1; j<=(*G).vexnum; j++)
			(*G).arcs[i][j].adj = INFINITY;			
	}
	
	for(k=1; k<=(*G).arcnum; k++)				//存储有向网的弧和权的信息；
	{
		Scanf(fp, "%c%c%d", &v1, &v2, &w);		//弧的集合→◤A，B，1◢◤A，F，3◢◤B，C，5◢◤C，A，6◢◤C，D，5◢◤D，A，9◢◤D，F，8◢◤E，D，4◢◤F，C，7◢◤F，E，5◢
		
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		
		if(!i || !j)
			return ERROR;
		
		(*G).arcs[i][j].adj = w;
		if((*G).IncInfo==1)						//若有弧的其他信息，则录入 
			Input(fp, &((*G).arcs[i][j].info));
	}
	
	return OK;
}

Status CreateUDG_M(FILE *fp, MGraph *G)
{
	int i, j, k;
	VertexType_M v1, v2;
	char tmp;
	
	Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	Scanf(fp, "%c", &tmp);							//跳过换行符 
	
	for(i=1; i<=(*G).vexnum; i++)
		Scanf(fp, "%c", &((*G).vexs[i]));

	Scanf(fp, "%c", &tmp);							//跳过换行符
	
	for(i=1; i<=(*G).vexnum; i++)					//初始化邻接矩阵 
	{
		for(j=1; j<=(*G).vexnum; j++)
			(*G).arcs[i][j].adj = 0;		
	}
	
	for(k=1; k<=(*G).arcnum; k++)
	{
		Scanf(fp, "%c%c", &v1, &v2);
		
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		
		if(!i || !j)
			return ERROR;
		
		(*G).arcs[i][j].adj = 1;
		if((*G).IncInfo==1)							//若有弧的其他信息，则录入 
			Input(fp, &((*G).arcs[i][j].info));
		
		(*G).arcs[j][i] = (*G).arcs[i][j];			//填充对称点 
	}
	
	return OK;
}

/*════╗
║ 算法7.2║ 
╚════*/
Status CreateUDN_M(FILE *fp, MGraph *G)
{
	int i, j, k;
	VertexType_M v1, v2;
	VRType w;
	char tmp;
	
	Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	Scanf(fp, "%c", &tmp);							//跳过换行符 
	
	for(i=1; i<=(*G).vexnum; i++)
		Scanf(fp, "%c", &((*G).vexs[i]));
	Scanf(fp, "%c", &tmp);							//跳过换行符
	
	for(i=1; i<=(*G).vexnum; i++)					//初始化邻接矩阵 
	{
		for(j=1; j<=(*G).vexnum; j++)
			(*G).arcs[i][j].adj = INFINITY;		
	}
	
	for(k=1; k<=(*G).arcnum; k++)
	{
		Scanf(fp, "%c%c%d", &v1, &v2, &w);
		
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		
		if(!i || !j)
			return ERROR;
		
		(*G).arcs[i][j].adj = w;

		if((*G).IncInfo==1)							//若有弧的其他信息，则录入 
			Input(fp, &((*G).arcs[i][j].info));
		
		(*G).arcs[j][i] = (*G).arcs[i][j];			//填充对称点 
	}
	
	return OK;
}

void ClearGraph_M(MGraph *G)
{
	(*G).vexnum = 0;
	(*G).arcnum = 0;
	(*G).IncInfo = 0;
}
 
//寻找顶点 u 的位置； 
int LocateVex_M(MGraph G, VertexType_M u)
{
	int i;
	
	for(i=1; i<=G.vexnum; i++)
	{
		if(G.vexs[i]==u)
			return i;
	}
	
	return 0;
}

VertexType_M GetVex_M(MGraph G, int order)
{
	if(order>=1 && order<=G.vexnum)
		return G.vexs[order];
	else
		return '\0';
} 

Status PutVex_M(MGraph *G, VertexType_M v, VertexType_M value)
{
	int k;
	
	k = LocateVex_M(*G, v);
	
	if(k)
	{
		(*G).vexs[k] = value;
		return OK;	
	}
	else
		return ERROR;
} 

int FirstAdjVex_M(MGraph G, VertexType_M v)
{
	int k, j, t;
	
	k = LocateVex_M(G, v);
	
	if(k)
	{	
		if(G.kind%2)				//网
			t = INFINITY;
		else						//图 
			t = 0;

		for(j=1; j<=G.vexnum; j++)
		{
			if(G.arcs[k][j].adj!=t)
				return j;
		}
	}
	
	return 0;
} 

int NextAdjVex_M(MGraph G, VertexType_M v, VertexType_M w)
{
	int k1, k2, j, t;
	
	k1 = LocateVex_M(G, v);
	k2 = LocateVex_M(G, w);
	
	if(k1 && k2)
	{
		if(G.kind%2)				//网
			t = INFINITY;
		else						//图 
			t = 0;

		for(j=k2+1; j<=G.vexnum; j++)
		{
			if(G.arcs[k1][j].adj!=t)
				return j;
		}
	}
	
	return 0;
} 

//插入顶点，图有变化，所以用 *G;
Status InsertVex_M(MGraph *G, VertexType_M v)
{
	int i, k, t;
	
	if((*G).vexnum==MAX_VERTEX_NUM)
		return ERROR;				//顶点数已满 
	
	if((*G).kind%2)					//网
		t = INFINITY;
	else							//图 
		t = 0;
	
	k = (*G).vexnum + 1;
	(*G).vexs[k] = v;
	
	for(i=1; i<=k; i++)
	{
		(*G).arcs[i][k].adj = t;	
		(*G).arcs[k][i].adj = t;
	}
	
	(*G).vexnum++;
	
	return OK;	
} 

//删除顶点，图有变化，所以用 *G;
Status DeleteVex_M(MGraph *G, VertexType_M v)
{
	int i, j, k, t;
	
	k = LocateVex_M(*G, v);
	
	if(!k)
		return ERROR;

	if((*G).kind%2)							//网
		t = INFINITY;
	else									//图 
		t = 0;	
		
	for(i=1; i<=k; i++)
	{
		if((*G).arcs[k][i].adj!=t)			//计算新的弧数 
			(*G).arcnum--;
		
		if((*G).kind==DG || (*G).kind==DN)	//有向，矩阵不对称，行和列都要遍历计算；
		{
			if((*G).arcs[i][k].adj!=t)
				(*G).arcnum--;			
		} 
	}
	
	for(i=1; i<=(*G).vexnum; i++)			//一行一行的移动；
	{
		for(j=k+1; j<=(*G).vexnum; j++)		//其中一行的移动操作；
			(*G).arcs[i][j-1] = (*G).arcs[i][j];
	}
	
	for(i=k+1; i<=(*G).vexnum; i++)			//一列一列的移动；
	{
		for(j=1; j<=(*G).vexnum-1; j++)		//其中一列的移动操作；
			(*G).arcs[i-1][j] = (*G).arcs[i][j];
	}
	
	(*G).vexnum--;
	
	return OK;	
} 

Status InsertArc_M(MGraph *G, VertexType_M v, VertexType_M w, VRType adj, ...)
{
	int k1, k2;
	
	k1 = LocateVex_M(*G, v);
	k2 = LocateVex_M(*G, w);
	
	if(!k1 || !k2)
		return ERROR;
		
	(*G).arcs[k1][k2].adj = adj;					//弧的信息（相邻？权值？） 

	va_list ap;										//ap 是参数指针；存在弧的其他信息，则录入；
	va_start(ap, adj);								//指针指向 adj 参数后面的那个参数；
	(*G).arcs[k1][k2].info = va_arg(ap, InfoType);	//在可变参数列表里"...", 找到 InfoType 类型的参数；结构可直接复制；	
	va_end(ap);										//关闭参数指针；
	
	if((*G).kind==UDG || (*G).kind==UDN)			//无向	
		(*G).arcs[k2][k1] = (*G).arcs[k1][k2];
	
	(*G).arcnum++;									//弧数增一 
		
	return OK;	
} 

Status DeleteArc_M(MGraph *G, VertexType_M v, VertexType_M w)
{
	int k1, k2;
	
	k1 = LocateVex_M(*G, v);
	k2 = LocateVex_M(*G, w);
	
	if(!k1 || !k2)
		return ERROR;
	
	if((*G).kind%2)							//网
		(*G).arcs[k1][k2].adj = INFINITY;	
	else									//图 
		(*G).arcs[k1][k2].adj = 0;
	
	if((*G).kind==UDG || (*G).kind==UDN)	//无向	
		(*G).arcs[k2][k1] = (*G).arcs[k1][k2];	

	(*G).arcnum--;							//弧数减一 
		
	return OK;
}

/*════╗
║ 算法7.4║ 
╚════*/
//深度优先搜索；
void DFSTraverse_M(MGraph G, void(Visit)(VertexType_M))
{
	int v;
	
	VisitFunc = Visit;
	
	for(v=1; v<=G.vexnum; v++)
		visited[v] = FALSE;					//所有的顶点都初始化为未访问
	
	for(v=1; v<=G.vexnum; v++)
	{
		if(!visited[v])						//对未访问的顶点进行递归深度遍历；
			DFS_M(G, v); 
	} 
}

/*════╗
║ 算法7.5║ 
╚════*/
//从第 v 个顶点出发，递归地深度遍历图 G；
void DFS_M(MGraph G, int v)
{
	int w;

	visited[v] = TRUE;				//对正在访问的顶点设置标志位为已访问；

	VisitFunc(G.vexs[v]);			//访问第 v 个顶点；

	for(w=FirstAdjVex_M(G, G.vexs[v]); w; w=NextAdjVex_M(G, G.vexs[v], G.vexs[w]))	//判断条件是顶点 w 存在；
	{
		if(!visited[w])
			DFS_M(G, w);
	}
}

/*════╗
║ 算法7.6║ 
╚════*/
//按广度优先搜索非递归遍历图 G; 使用辅助队列 Q 和访问标志数组 visited;
void BFSTraverse_M(MGraph G, void(Visit)(VertexType_M))
{
	int v, w;
	LinkQueue Q;
	QElemType_L e;
	
	for(v=1; v<=G.vexnum; v++)
		visited[v] = FALSE;					//所有的顶点都初始化为未访问
	
	InitQueue_L(&Q);						//置空辅助队列 Q;		
	
	for(v=1; v<=G.vexnum; v++)				//过程遍历所有顶点；
	{
		if(!visited[v])						//索引为 v 的顶点尚未被访问；
		{
			visited[v] = TRUE;				//首先改变访问标志；
			Visit(G.vexs[v]);				//访问索引为 v 的顶点；
			EnQueue_L(&Q, v);				//索引为 v 的顶点入队；
			while(!QueueEmpty_L(Q))			//while 循环条件，队列不空；
			{
				DeQueue_L(&Q, &e);			//用 e 接收出队列的元素值;
				for(w=FirstAdjVex_M(G, G.vexs[e]); w; w=NextAdjVex_M(G, G.vexs[e], G.vexs[w]))
				{
					if(!visited[w])
					{
						visited[w] = TRUE;
						Visit(G.vexs[w]);
						EnQueue_L(&Q, w);
					}
				}//for 循环依次访问 e 的未被访问的邻接点，并且入队列；
			}//while 循环
		}
	}
}


void OutputMGraph(MGraph G)
{
	int i, j;
	
	if(!G.vexnum && !G.arcnum)
		printf("空图（表）！\n");
	else
	{
		printf("  ");
		for(i=1; i<=G.vexnum; i++)
			printf("%2c ", G.vexs[i]);
		printf("\n");
		
		for(i=1; i<=G.vexnum; i++)
		{
			printf("%c ", G.vexs[i]);
			for(j=1; j<=G.vexnum; j++)
			{
				if(G.arcs[i][j].adj==INFINITY)
					printf("∞ ");
				else
					printf("%2d ", G.arcs[i][j]);
			}
		
			printf("\n");
		}
	}
}

void Input(FILE *fp, InfoType *info)
{
	//录入弧的信息，本文档涉及到的弧默认无其他信息 
}

#endif
