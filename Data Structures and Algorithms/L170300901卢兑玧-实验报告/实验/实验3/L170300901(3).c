#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumMax 50
#include <windows.h>

#define FileAddress "D://shiyan3.txt"

typedef struct
{
    char VData[NumMax];
    int EData[NumMax][NumMax];
    int v,e;
}MGraph;

typedef struct node
{
    int adjvex,cost;
    struct node* next;
}EdgeNode;
typedef struct
{
    char vertax;
    EdgeNode* firstedge;
}VertexNode;
typedef struct
{
    VertexNode vexlist[NumMax];
    int v,e;
}AdjGraph;

typedef struct EBox
{
    int ivex,jvex,cost;
    struct EBox *ilink,*jlink;
    char *info;
}EBox;
typedef struct VexBox
{
    char Vertex;
    EBox *firstedge;
}VexBox;
typedef struct
{
    VexBox adjmulist[NumMax];
    int v,e;
}AmlGraph;

typedef struct struct_* stack_0;
typedef struct struct_* queue_0;
typedef struct struct_
{
    int dat;
    struct struct_* next;
}struct_;
stack_0 stack_h;
queue_0 queue_h;

typedef enum {visited,unvisited}VisitIf;
VisitIf Visit[NumMax];


void Select(MGraph*,AdjGraph*,AmlGraph*);   //选择项目界面
void PrintMGraph(MGraph*);  //打印邻接矩阵
void PrintAdjGraph(AdjGraph*);  //打印邻接表
void PrintAmlGraph(AmlGraph*);  //打印邻接多重表
void CreateMGraph(MGraph*); //从文件读数据生成邻接矩阵
void CreateAdjGraph(AdjGraph*); //从文件读数据生成邻接表
void CreateAmlGraph(AmlGraph*); //从文件读数据生成邻接多重表
int LocateVex(AmlGraph*,char);  //找输入字符的位置
void MtoAdj(MGraph*,AdjGraph*); //把邻接矩阵转换成邻接表
void MtoAml(MGraph*,AmlGraph*); //把邻接矩阵转换成邻多重接表
void AdjtoM(AdjGraph*,MGraph*); //把邻接表转换成邻接矩阵
void AdjtoAml(AdjGraph*,AmlGraph*); //把邻接表转换成邻接多重表
void AmltoM(AmlGraph*,MGraph*); //把邻接多重表转换成邻接矩阵
void AmltoAdj(AmlGraph*,AdjGraph*); //把邻接多重表转换成邻接表
void pushst(int);   //进栈
int popst();    //出栈
void MGraphLoop(MGraph*);   //用循环遍历深度优先搜索邻接矩阵
void AdjGraphLoop(AdjGraph*);   //用循环遍历深度优先搜索邻接表
void AmlGraphLoop(AmlGraph*);   //用循环遍历深度优先搜索邻接多重表
void MGraphRecursive(MGraph*);  //利用递归函数深度优先搜索邻接矩阵
void DFSM(MGraph*,int); //递归型深度优先搜索邻接矩阵
void AdjGraphRecursive(AdjGraph*);  //利用递归函数深度优先搜索邻接表
void DFSAdj(AdjGraph*,int); //递归型深度优先搜索邻接表
void AmlGraphRecursive(AmlGraph*);  //利用递归函数深度优先搜索邻接多重表
void DFSAml(AmlGraph*,int); //递归型深度优先搜索邻接多重表
void ENQUEUE(int);  //进队列
int DEQUEUE();  //出队列
int EmptyQ();   //判断队列是不是空
void BFSM(MGraph*); //广度搜索邻接矩阵
void BFSAdj(AdjGraph*); //广度搜索邻接表
void BFSAml(AmlGraph*); //广度搜索邻接多重表
void gotoxy(int,int);


void gotoxy(int x,int y)
{
    COORD pos = { x - 1, y - 1 };//커서가 X좌표에서 -1 한값. Y좌표에서 -1한 값으로 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void BFSAml(AmlGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have AmlGraph!\n");
        return;
    }
    int i,p,j;
    EBox* m;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0,p=i; i<G->v; i++,p=i)
    {
        if(!Visit[i])
            continue;
        ENQUEUE(i);
        printf("%c",G->adjmulist[i].Vertex);
        Visit[i]=0;
        while(EmptyQ()!=-1)
        {
            p=DEQUEUE();
            m=G->adjmulist[p].firstedge;
            while(m)
            {
                if(p==m->ivex)
                {
                    if(Visit[m->jvex])
                    {
                        j=m->jvex;
                        ENQUEUE(j);
                        printf(" %c",G->adjmulist[j].Vertex);
                        Visit[j]=0;
                    }
                    m=m->ilink;
                }
                else
                {
                    if(Visit[m->ivex])
                    {
                        j=m->ivex;
                        ENQUEUE(j);
                        printf(" %c",G->adjmulist[j].Vertex);
                        Visit[j]=0;
                    }
                    m=m->jlink;
                }
            }
        }
    }
}

void BFSAdj(AdjGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have AdjGraph!\n");
        return;
    }
    int i,p,j;
    EdgeNode* m;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0,p=i; i<G->v; i++,p=i)
    {
        if(!Visit[i])
            continue;
        ENQUEUE(i);
        printf("%c",G->vexlist[i].vertax);
        Visit[i]=0;
        while(EmptyQ()!=-1)
        {
            p=DEQUEUE();
            m=G->vexlist[p].firstedge;
            while(m)
            {
                if(Visit[m->adjvex]&&m->cost!=0)
                {
                    j=m->adjvex;
                    ENQUEUE(j);
                    printf(" %c",G->vexlist[j].vertax);
                    Visit[j]=0;
                }
                m=m->next;
            }
        }
    }
}

void BFSM(MGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have MGraph!\n");
        return;
    }
    int i,p,j;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0,p=i; i<G->v; i++,p=i)
    {
        if(!Visit[i])
            continue;
        ENQUEUE(i);
        printf("%c",G->VData[i]);
        Visit[i]=0;
        while(EmptyQ()!=-1)
        {
            p=DEQUEUE();
            for(j=0; j<G->v; j++)
            {
                if(G->EData[p][j]!=0&&Visit[j])
                {
                    ENQUEUE(j);
                    printf(" %c",G->VData[j]);
                    Visit[j]=0;
                }
            }
        }
    }
}

int EmptyQ()
{
    if(!queue_h->next)
        return -1;
    else
        return 1;
}

int DEQUEUE()
{
    if(!queue_h->next)
        return -1;
    else
    {
        int i;
        queue_0 p=queue_h->next;
        i=p->dat;
        queue_h->next=p->next;
        free(p);
        return i;
    }

}

void ENQUEUE(int i)
{
    queue_0 p=(queue_0)malloc(sizeof(struct_));
    p->dat=i;
    p->next=NULL;
    queue_0 q=queue_h;
    while(q->next)
    {
        q=q->next;
    }
    q->next=p;
}

void DFSAml(AmlGraph* G,int i)
{
    int j;
    Visit[i]=0;
    printf("%c ",G->adjmulist[i].Vertex);
    EBox* m;
    m=G->adjmulist[i].firstedge;
    while(m)
    {
        if(i==m->ivex)
        {
            j=m->jvex;
            if(Visit[j]&&m->cost!=0)
                DFSAml(G,j);
            m=m->ilink;
        }
        else
        {
            j=m->ivex;
            if(Visit[j]&&m->cost!=0)
                DFSAml(G,j);
            m=m->jlink;
        }
    }
}

void AmlGraphRecursive(AmlGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have AmlGraph!\n");
        return;
    }
    int i;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0; i<G->v; i++)
        if(Visit[i])
            DFSAml(G,i);
}

void DFSAdj(AdjGraph* G,int i)
{
    int j;
    Visit[i]=0;
    printf("%c ",G->vexlist[i].vertax);
    EdgeNode* m;
    m=G->vexlist[i].firstedge;
    while(m)
    {
        j=m->adjvex;
        if(Visit[j]&&m->cost!=0)
            DFSAdj(G,j);
        m=m->next;
    }
}

void AdjGraphRecursive(AdjGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have AdjGraph!\n");
        return;
    }
    int i;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0; i<G->v; i++)
        if(Visit[i])
            DFSAdj(G,i);
}

void DFSM(MGraph* G,int i)
{
    int j;
    Visit[i]=0;
    printf("%c ",G->VData[i]);
    for(j=0; j<G->v; j++)
        if(G->EData[i][j]!=0&&Visit[j])
            DFSM(G,j);
}

void MGraphRecursive(MGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have MGraph!\n");
        return;
    }
    int i;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0; i<G->v; i++)
        if(Visit[i])
            DFSM(G,i);
}

void AmlGraphLoop(AmlGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have AmlGraph!\n");
        return;
    }
    int i,j,p,flag;
    EBox* m;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0,p=i; i<G->v; i++,p=i)
    {
        if(!Visit[i])
            continue;
        Visit[i]=0;
        printf("%c",G->adjmulist[i].Vertex);
        while(p!=-1)
        {
            flag=1;
            m = G->adjmulist[p].firstedge;
            while(m)
            {
                if(m->ivex==p)
                {
                    j=m->jvex;
                    if(Visit[j])
                    {
                        pushst(p);
                        Visit[j]=0;
                        printf(" %c",G->adjmulist[j].Vertex);
                        flag=0; p=j;
                        break;
                    }
                    m=m->ilink;
                }
                else
                {
                    j=m->ivex;
                    if(Visit[j])
                    {
                        pushst(p);
                        Visit[j]=0;
                        printf(" %c",G->adjmulist[j].Vertex);
                        flag=0; p=j;
                        break;
                    }
                    m=m->jlink;
                }
            }
            if(flag)
                p=popst();
        }
    }
}

void AdjGraphLoop(AdjGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have AdjGraph!\n");
        return;
    }
    int i,j,p,flag;
    EdgeNode* m;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0,p=i; i<G->v; i++,p=i)
    {
        if(!Visit[i])
            continue;
        Visit[i]=0;
        printf("%c",G->vexlist[i].vertax);
        while(p!=-1)
        {
            flag=1;
            m = G->vexlist[p].firstedge;
            while(m)
            {
                j=m->adjvex;
                if(Visit[j])
                {
                    pushst(p);
                    Visit[j]=0;
                    printf(" %c",G->vexlist[j].vertax);
                    flag=0; p=j;
                    break;
                }
                m=m->next;
            }
            if(flag)
                p=popst();
        }
    }
}

void MGraphLoop(MGraph* G)
{
    if(G->v==-1)
    {
        printf("No Have MGraph!\n");
        return;
    }
    int i,j,p,flag;
    for(i=0; i<G->v; i++)
        Visit[i]=1;
    for(i=0,p=i; i<G->v; i++,p=i)
    {
        if(!Visit[i])
            continue;
        Visit[i]=0;
        printf("%c",G->VData[i]);
        while(p!=-1)
        {
            flag=1;
            for(j=0; j<G->v; j++)
            {
                if(Visit[j]&&G->EData[p][j]!=0)
                {
                    pushst(p);
                    Visit[j]=0;
                    printf(" %c",G->VData[j]);
                    flag=0; p=j;
                    break;
                }
            }
            if(flag)
                p=popst();
        }
    }
}

int popst()
{
    int i;
    if(!stack_h->next)
        return -1;
    else
    {
        stack_0 p=stack_h->next;
        i=p->dat;
        stack_h->next=p->next;
        free(p);
        return i;
    }
}

void pushst(int i)
{
    stack_0 p=(stack_0)malloc(sizeof(struct_));
    p->dat=i;
    p->next=stack_h->next;
    stack_h->next=p;
}

void AmltoAdj(AmlGraph* x,AdjGraph* y)
{
    int i,j;
    if(x->v==-1)
    {
        printf("No Have AmlGraph!\n");
        return;
    }
    y->v=x->v; y->e=x->e;
    EdgeNode* m;
    for(i=0; i<y->v; i++)
    {
        y->vexlist[i].vertax=x->adjmulist[i].Vertex;
        while(y->vexlist[i].firstedge)
        {
            m=y->vexlist[i].firstedge;
            y->vexlist[i].firstedge=y->vexlist[i].firstedge->next;
            free(m);
        }
    }
    EBox* s;
    for(i=0; i<x->v; i++)
    {
        s=x->adjmulist[i].firstedge;
        while(s)
        {
            EdgeNode* p=(EdgeNode*)malloc(sizeof(EdgeNode));
            if(s->ivex==i)
            {
                if(y->vexlist[i].firstedge)
                {
                    EdgeNode* m=y->vexlist[i].firstedge;
                    while(m->next)
                        m=m->next;
                    p->adjvex=s->jvex;
                    p->cost=s->cost;
                    p->next=NULL;
                    m->next=p;
                }
                else
                {
                    p->adjvex=s->jvex;
                    p->cost=s->cost;
                    p->next=NULL;
                    y->vexlist[i].firstedge=p;
                }
                s=s->ilink;
            }
            else
            {
                if(y->vexlist[i].firstedge)
                {
                    EdgeNode* m=y->vexlist[i].firstedge;
                    while(m->next)
                        m=m->next;
                    p->adjvex=s->ivex;
                    p->cost=s->cost;
                    p->next=NULL;
                    m->next=p;
                }
                else
                {
                    p->adjvex=s->ivex;
                    p->cost=s->cost;
                    p->next=NULL;
                    y->vexlist[i].firstedge=p;
                }
                s=s->jlink;
            }
        }
    }
    printf("Change Completed");
}

void AmltoM(AmlGraph* x,MGraph* y)
{
    int i,j;
    if(x->v==-1)
    {
        printf("No Have AmlGraph!\n");
        return;
    }
    y->v=x->v; y->e=x->e;
    for(i=0; i<y->v; i++)
    {
        y->VData[i]=x->adjmulist[i].Vertex;
        for(j=0; j<y->v; j++)
            y->EData[i][j]=0;
    }
    EBox* s;
    for(i=0; i<x->v; i++)
    {
        s=x->adjmulist[i].firstedge;
        while(s)
        {
            if(s->ivex==i)
            {
                y->EData[i][s->jvex]=s->cost;
                y->EData[s->jvex][i]=s->cost;
                s=s->ilink;
            }
            else
            {
                y->EData[i][s->ivex]=s->cost;
                y->EData[s->ivex][i]=s->cost;
                s=s->jlink;
            }
        }
    }
    printf("Change Completed");
}

void AdjtoAml(AdjGraph* x,AmlGraph* y)
{
    int i,j;
    if(x->v==-1)
    {
        printf("No Have AdjGraph!\n");
        return;
    }
    y->v=x->v; y->e=x->e;
    for(i=0; i<y->v; i++)
    {
        y->adjmulist[i].Vertex=x->vexlist[i].vertax;
        y->adjmulist[i].firstedge=NULL;
    }
    for(i=0; i<y->v; i++)
    {
        EdgeNode* s=x->vexlist[i].firstedge;
        while(s)
        {
            j=s->adjvex;
            EBox* p=(EBox*)malloc(sizeof(EBox));
            p->ivex=i; p->jvex=j; p->cost=s->cost;
            p->ilink=y->adjmulist[i].firstedge;
            p->jlink=y->adjmulist[j].firstedge;
            y->adjmulist[i].firstedge=y->adjmulist[j].firstedge=p;
            s=s->next;
        }
    }
    printf("Change Completed");
}

void AdjtoM(AdjGraph* x,MGraph* y)
{
    int i,j;
    if(x->v==-1)
    {
        printf("No Have AdjGraph!\n");
        return;
    }
    y->v=x->v; y->e=x->e;
    for(i=0; i<y->v; i++)
    {
        y->VData[i]=x->vexlist[i].vertax;
        for(j=0; j<y->v; j++)
            y->EData[i][j]=0;
    }
    EdgeNode* p;
    for(i=0; i<y->v; i++)
    {
        p=x->vexlist[i].firstedge;
        while(p)
        {
            y->EData[i][p->adjvex]=p->cost;
            p=p->next;
        }
    }
    printf("Change Completed");
}

void MtoAml(MGraph* x,AmlGraph* y)
{
    int i,j;
    if(x->v==-1)
    {
        printf("No Have MGraph!\n");
        return;
    }
    y->v=x->v; y->e=x->e;
    for(i=0; i<y->v; i++)
    {
        y->adjmulist[i].Vertex=x->VData[i];
        y->adjmulist[i].firstedge=NULL;
    }
    for(i=0; i<y->v; i++)
    {
        for(j=i; j<y->v; j++)
        {
            if(x->EData[i][j]!=0)
            {
                EBox* p=(EBox*)malloc(sizeof(EBox));
                p->ivex=i; p->jvex=j; p->cost=x->EData[i][j];
                p->ilink=y->adjmulist[i].firstedge;
                p->jlink=y->adjmulist[j].firstedge;
                y->adjmulist[i].firstedge=y->adjmulist[j].firstedge=p;
            }
        }
    }
    printf("Change Completed");
}

void MtoAdj(MGraph* x,AdjGraph* y)
{
    int i,j;
    if(x->v==-1)
    {
        printf("No Have MGraph!\n");
        return;
    }
    y->v=x->v; y->e=x->e;
    EdgeNode* m;
    for(i=0; i<y->v; i++)
    {
        y->vexlist[i].vertax=x->VData[i];
        while(y->vexlist[i].firstedge)
        {
            m=y->vexlist[i].firstedge;
            y->vexlist[i].firstedge=y->vexlist[i].firstedge->next;
            free(m);
        }
    }
    for(i=0; i<x->v; i++)
    {
        for(j=i; j<x->v; j++)
        {
            if(x->EData[i][j]!=0)
            {
                EdgeNode* p=(EdgeNode*)malloc(sizeof(EdgeNode));
                if(y->vexlist[i].firstedge)
                {
                    EdgeNode* s=y->vexlist[i].firstedge;
                    while(s->next)
                        s=s->next;
                    p->adjvex=j;
                    p->cost=x->EData[i][j];
                    p->next=NULL;
                    s->next=p;
                }
                else
                {
                    p->adjvex=j;
                    p->cost=x->EData[i][j];
                    p->next=NULL;
                    y->vexlist[i].firstedge=p;
                }
                EdgeNode* q=(EdgeNode*)malloc(sizeof(EdgeNode));
                if(y->vexlist[j].firstedge)
                {
                    EdgeNode* s=y->vexlist[j].firstedge;
                    while(s->next)
                        s=s->next;
                    q->adjvex=i;
                    q->cost=x->EData[i][j];
                    q->next=NULL;
                    s->next=q;
                }
                else
                {
                    q->adjvex=i;
                    q->cost=x->EData[i][j];
                    q->next=NULL;
                    y->vexlist[j].firstedge=q;
                }
            }
        }
    }
    printf("Change Completed");
}

int LocateVex(AmlGraph* G, char v)
{
    int i;
    for(i=0; i<G->v; ++i)
    {
        if(G->adjmulist[i].Vertex==v)
            return i;
    }
    return -1;
}

void CreateAmlGraph(AmlGraph* G)
{
    char v1,v2;
    int i,j,k,num;
    FILE* fp;
    G->e=0;

    fp=fopen(FileAddress,"r");
    if(!fp)
        exit(-1);
    if(!feof(fp))
    {
        fscanf(fp,"Vertex:%d\nEdge:%d\n",&G->v,&G->e);
        for(i=0; i<G->v; i++)
        {
            G->adjmulist[i].Vertex=fgetc(fp);
            G->adjmulist[i].firstedge=NULL;
        }
        for(k=0; k<G->e; k++)
        {
            fscanf(fp,"\n[%c][%c]: %d",&v1,&v2,&num);
            i=LocateVex(G,v1); j=LocateVex(G,v2);
            EBox* p=(EBox*)malloc(sizeof(EBox));
            p->ivex=i; p->jvex=j; p->cost=num;
            p->ilink=G->adjmulist[i].firstedge;
            p->jlink=G->adjmulist[j].firstedge;
            G->adjmulist[i].firstedge=G->adjmulist[j].firstedge=p;
        }
    }
    printf("Read Completed");
    fclose(fp);

}

void CreateAdjGraph(AdjGraph* G)
{
    int i,j,k,num,d;
    char v1,v2;
    FILE* fp;
    fp=fopen(FileAddress,"r");
    if(!fp)
        exit(-1);
    if(!feof(fp))
    {
        fscanf(fp,"Vertex:%d\nEdge:%d\n",&G->v,&G->e);
        EdgeNode* m;
        for(i=0; i<G->v; i++)
        {
            G->vexlist[i].vertax=fgetc(fp);
            while(G->vexlist[i].firstedge)
            {
                m=G->vexlist[i].firstedge;
                G->vexlist[i].firstedge=G->vexlist[i].firstedge->next;
                free(m);
            }
        }
        for(k=0; k<G->e; k++)
        {
            fscanf(fp,"\n[%c][%c]: %d",&v1,&v2,&num);
            for(d=0; d<G->v; d++)
            {
                if(v1==G->vexlist[d].vertax)
                    i=d;
                if(v2==G->vexlist[d].vertax)
                    j=d;
            }
            EdgeNode* p=(EdgeNode*)malloc(sizeof(EdgeNode));
            if(G->vexlist[i].firstedge)
            {
                EdgeNode* s=G->vexlist[i].firstedge;
                while(s->next)
                    s=s->next;
                p->adjvex=j;
                p->cost=num;
                p->next=NULL;
                s->next=p;
            }
            else
            {
                p->adjvex=j;
                p->cost=num;
                p->next=NULL;
                G->vexlist[i].firstedge=p;
            }

            EdgeNode* q=(EdgeNode*)malloc(sizeof(EdgeNode));
            if(G->vexlist[j].firstedge)
            {
                EdgeNode* s=G->vexlist[j].firstedge;
                while(s->next)
                    s=s->next;
                q->adjvex=i;
                q->cost=num;
                q->next=NULL;
                s->next=q;
            }
            else
            {
                q->adjvex=i;
                q->cost=num;
                q->next=NULL;
                G->vexlist[j].firstedge=q;
            }
        }
    }
    printf("Read Completed");
    fclose(fp);
}

void CreateMGraph(MGraph* G)
{
    int i,j,k,d,num;
    char v1,v2;
    FILE* fp;
    G->e=0;

    fp=fopen(FileAddress,"r");
    if(!fp)
        exit(-1);
    if(!feof(fp))
    {
        fscanf(fp,"Vertex:%d\nEdge:%d\n",&G->v,&G->e);
        for(i=0; i<G->v; i++)
            G->VData[i]=fgetc(fp);
        for(i=0; i<G->v; i++)
            for(j=0; j<G->v; j++)
                G->EData[i][j]=0;
        for(k=0; k<G->e; k++)
        {
            fscanf(fp,"\n[%c][%c]: %d",&v1,&v2,&num);
            for(d=0; d<G->v; d++)
            {
                if(v1==G->VData[d])
                    i=d;
                if(v2==G->VData[d])
                    j=d;
            }
            G->EData[i][j]=num;
            G->EData[j][i]=num;
        }
    }
    printf("Read Completed");
    fclose(fp);
}

void PrintAmlGraph(AmlGraph* G)
{
    int i,j;
    if(G->v==-1)
    {
        printf("No Have AmlGraph!\n");
        return;
    }
    EBox* s;
    for(i=0; i<G->v; i++)
    {
        s=G->adjmulist[i].firstedge;
        while(s)
        {
            if(s->ivex==i)
            {
                printf("| %c-(%d)-%c |",G->adjmulist[i].Vertex,s->cost,G->adjmulist[s->jvex].Vertex);
                s=s->ilink;
            }
            else
            {
                printf("| %c-(%d)-%c |",G->adjmulist[i].Vertex,s->cost,G->adjmulist[s->ivex].Vertex);
                s=s->jlink;
            }
        }
        printf("\n");
    }
}

void PrintAdjGraph(AdjGraph* G)
{
    int i,j;
    if(G->v==-1)
    {
        printf("No Have AdjGraph!\n");
        return;
    }
    EdgeNode* S;
    for(i=0; i<G->v;i++)
    {
        S=G->vexlist[i].firstedge;
        printf("\n%c: ",G->vexlist[i].vertax);
        while(S)
        {
            printf(" %c(%d)",G->vexlist[S->adjvex].vertax,S->cost);
            S=S->next;
        }
    }
}

void PrintMGraph(MGraph* G)
{
    int i,j;
    if(G->v==-1)
    {
        printf("No Have MGraph!\n");
        return;
    }
    for(i=0,j=0; i<G->v;i++)
    {
        printf(" ");
        while(j<G->v)
        {
            printf(" %c",G->VData[j++]);
        }
        printf("\n");
        printf("%c",G->VData[i]);
        for(j=0; j<G->v; j++)
        {
            printf(" %d",G->EData[i][j]);
        }
    }
}

void Select(MGraph* A,AdjGraph* B,AmlGraph* C)
{

    int i,j,num;
            gotoxy(1,1);
    printf("\n[1]  Create MGraph\t\t[12] [L]DFS Travel AmlGraph\n");
    printf("[2]  Create AdjGraph\t\t[13] [R]DFS Travel MGraph\n");
    printf("[3]  Create AmlGraph\t\t[14] [R]DFS Travel AdjGraph\n");
    printf("[4]  MGraph to AdjGraph\t\t[15] [R]DFS Travel AmlGraph\n");
    printf("[5]  MGraph to AmlGraph\t\t[16] BFS Travel MGraph\n");
    printf("[6]  AdjGraph to MGraph\t\t[17] BFS Travel AdjGraph\n");
    printf("[7]  AdjGraph to AmlGraph\t[18] BFS Travel AmlGraph\n");
    printf("[8]  AmlGraph to MGraph\t\t[19] PRINT MGraphn\n");
    printf("[9]  AmlGraph to AdjGraph\t[20] PRINT AdjGraphn\n");
    printf("[10] [L]DFS Travel MGraph\t[21] PRINT AmlGraphn\n");
    printf("[11] [L]DFS Travel AdjGraph\t[0]  EXIT~\n");
    printf("\nSelect Number:");
    do{
    gotoxy(1,1);
    gotoxy(15,14);
    scanf("%d",&num);
    gotoxy(15,14);
    for(i=0; i<NumMax;i++)
        printf("\t\t\t\t\t\t\t\n");
    gotoxy(1,16);
    switch(num)
    {
    case 1:
        CreateMGraph(A);
        break;
    case 2:
        CreateAdjGraph(B);
        break;
    case 3:
        CreateAmlGraph(C);
        break;
    case 4:
        MtoAdj(A,B);
        break;
    case 5:
        MtoAml(A,C);
        break;
    case 6:
        AdjtoM(B,A);
        break;
    case 7:
        AdjtoAml(B,C);
        break;
    case 8:
        AmltoM(C,A);
        break;
    case 9:
        AmltoAdj(C,B);
        break;
    case 10:
        MGraphLoop(A);
        break;
    case 11:
        AdjGraphLoop(B);
        break;
    case 12:
        AmlGraphLoop(C);
        break;
    case 13:
        MGraphRecursive(A);
        break;
    case 14:
        AdjGraphRecursive(B);
        break;
    case 15:
        AmlGraphRecursive(C);
        break;
    case 16:
        BFSM(A);
        break;
    case 17:
        BFSAdj(B);
        break;
    case 18:
        BFSAml(C);
        break;
    case 19:
        PrintMGraph(A);
        break;
    case 20:
        PrintAdjGraph(B);
        break;
    case 21:
        PrintAmlGraph(C);
        break;
    case 0:
        system("cls");
    default:break;
    }
    }while(num!=0);
}

int main()
{
    int i=0;
    stack_h=(stack_0)malloc(sizeof(struct_));
    queue_h=(queue_0)malloc(sizeof(struct_));
    stack_h->next=NULL;
    queue_h->next=NULL;
    MGraph A;
    AdjGraph B;
    for(i=0; i<NumMax; i++)
        B.vexlist[i].firstedge=NULL;
    AmlGraph C;
    A.v=B.v=C.v=-1;
    Select(&A,&B,&C);
    return 0;
}

