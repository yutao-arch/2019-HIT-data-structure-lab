#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

#define chang 12
#define bian 39

typedef struct
{
	char verlist[20]; //顶点表
	int edge[20][20]; //边表
	int n, e; //图的顶点数和边数
}mtgraph;
//图的邻接矩阵

typedef struct edge
{
	int bgn;
	int end;
	int wet;
}EGDE;
//边的节点

int c[chang+1][chang+1];  //构造Prim算法需要的长度数组c

void prim(mtgraph *g)
{
	int lowcost[chang+1], closset[chang+1], i, j, k, min,m=0,n=0;
	for (i = 2; i <= chang; i++)   //初始化数组lowcost和closset
	{
		lowcost[i] = c[1][i];
		closset[i] = 1;
	}
	for (i = 2; i <= chang; i++)
	{
		min = lowcost[i];
		k = i;
		for (j = 2; j <= chang; j++)  //在lowcost中选最短边，记下closset中对应的顶点序号k
		{
			if (lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
		}
		lowcost[k] = 10000;     //把访问过得点距离设为10000
		for (j = 2; j <= chang; j++)
		{
			if (c[k][j] < lowcost[j]&& lowcost[j]!=10000)
			{
				lowcost[j] = c[k][j];
				closset[j] = k;
			}
		}
	}
	printf("Prim算法最小生成树的各边的连接点为：\n");
	for (i = 2; i <= chang; i++)   //将最小生成树的边的链接的两个点的信息储存在数组point中
	{
		printf("(%c,%c)\n", g->verlist[i-1], g->verlist[closset[i]-1]);
	}
}
//Prim算法的最小生成树

void createmgraph(mtgraph* g)
{
	int i, j, m, n,o;
	FILE* fp;
	fp = fopen("read_mini_picture.txt", "r");
	if (fp == NULL)
	{
		printf("打开文件夹失败\n");
		exit(0);
	}
	fscanf(fp, "%d", &g->n);
	fscanf(fp, "%d", &g->e);
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			g->edge[i][j] = INT_MAX;
		}
	}
	for (i = 0; i < g->n; i++)
	{
		fscanf(fp, " %c", &g->verlist[i]);
	}
	for (i = 0; i < g->e; i++)
	{
		fscanf(fp, "%d,%d,%d", &m, &n, &o);
		g->edge[m - 1][n - 1] = o;
		g->edge[n - 1][m - 1] = o;
	}
}
//从文件中读入无向图的邻接矩阵存储

void create_c(mtgraph* g)
{
	int i,j;
	for (i = 1; i <= g->n; i++)   //行点的初始化
	{
		c[0][i] = i;
	}
	for (i = 1; i <= g->n; i++)   //列点的初始化
	{
		c[i][0] = i;
	}
	for (i = 1; i <= g->n; i++)
	{
		for (j = 1; j <= g->n; j++)
		{
			c[i][j] = g->edge[i - 1][j - 1];  //读入邻接矩阵中的信息
		}
	}
}
//用读入的邻接矩阵构造Prim算法需要的长度数组c

int find(int father[], int v)
{
	int f = v;
	while (father[f] > 0)
	{
		f = father[f];
	}
	return f;
}
//寻找祖先

void sort(EGDE edge[],int e)
{
	int i, j, temp1,temp2,temp3;
	for (i = 0; i < e; i++)
	{
		for (j = 0; j <e - i; j++)
		{
			if (edge[j].wet > edge[j + 1].wet)
			{
				temp1 = edge[j + 1].bgn;
				edge[j + 1].bgn = edge[j].bgn;
				edge[j].bgn = temp1;
				temp2 = edge[j + 1].end;
				edge[j + 1].end = edge[j].end;
				edge[j].end = temp2;
				temp3 = edge[j + 1].wet;
				edge[j + 1].wet = edge[j].wet;
				edge[j].wet = temp3;
			}
		}
	}
}
//对EGDE数组的排序算法

void kruskal(EGDE edge[], int e,mtgraph *g)
{
	printf("Kruskal算法最小生成树的各边的连接点为：\n");
	int father[bian-chang+1], bnf, edf, i;
	for (i = 1; i <= e; i++)
	{
		father[i] = 0;
	}
	for (i = 1; i <= e; i++)
	{
		bnf = find(father, edge[i-1].bgn);   //判断任意一条边的是否连接相同的连通分量
		edf = find(father, edge[i-1].end);
		if (bnf != edf)   //若是两个不同的连通分量，则连接成一个连通分量
		{
			father[bnf] = edf;
			printf("(%c,%c)\n", g->verlist[edge[i-1].bgn-1], g->verlist[edge[i-1].end-1]);
		}
	}
}
//Kruskal算法的最小生成树

void getedges(EGDE edge[],mtgraph *g)
{
	int i, j, k=0,m=0;
	for (i = 0; i < g->n; i++)
	{
		for (j = m; j < g->n; j++)
		{
			if (g->edge[i][j] != INT_MAX && g->edge[i][j] != 0)
			{
				edge[k].bgn = i + 1;
				edge[k].end = j + 1;
				edge[k].wet = g->edge[i][j];
				//printf("%d %d %d\n", edge[k].bgn, edge[k].end, edge[k].wet);
				k++;
			}
		}
		m++;
	}

}
//从已经读入的邻接矩阵中得到边数组的值

int main()
{
	mtgraph* p;
	p = (mtgraph*)malloc(sizeof(mtgraph));
	createmgraph(p);
	create_c(p);
	prim(p);
	//
	printf("\n");
	mtgraph* k;
	EGDE edges[bian-chang];
	int e;
	k = (mtgraph*)malloc(sizeof(mtgraph));
	createmgraph(k);
	getedges(edges, k);
	e = bian - chang;
	sort(edges, e);
	kruskal(edges, e,k);
	return 0;
}
