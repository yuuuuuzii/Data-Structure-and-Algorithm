#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int tag;
    struct Node *next;
    
}Node;

typedef struct Graph{
    int vertex_num;
    Node **adjList;
    Node **reverse_adjList;
    int *color;
    int *color_r;
    int *color_a;
    int *Order;
}Graph;

Node *CreateNode(int id){
    Node *new = (Node*)malloc(sizeof(Node));
    new->tag = id;
    new->next = NULL;

    return new;
}

Graph *CreateGraph(int block_num){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertex_num = block_num;
    graph->adjList = (Node **)malloc(sizeof(Node *)*block_num);
    graph->reverse_adjList = (Node **)malloc(sizeof(Node *)*block_num);
    graph->color = (int *)malloc(sizeof(int)*block_num);
    graph->color_r = (int *)malloc(sizeof(int)*block_num);
    graph->color_a = (int *)malloc(sizeof(int)*block_num);
    graph->Order = (int *)malloc(sizeof(int)*block_num);
    for(int i = 0; i<block_num; i++){
        graph->adjList[i] = NULL;
        graph->reverse_adjList[i] = NULL;
        graph->color[i] = -1;
        graph->color_r[i] = -1;
        graph->color_a[i] = -1;
    }

    return graph;
}

void addEdge(Graph *graph,int u, int v){
    Node *new1 = CreateNode(v);//建正常圖
    new1->next = graph->adjList[u];
    graph->adjList[u] = new1;

    Node *new2 = CreateNode(u);//建Reverse圖
    new2->next = graph->reverse_adjList[v];
    graph->reverse_adjList[v] = new2;
}

void DFS_visit(Graph *graph, int i, int *j){
    graph->color[i] = 0;
    Node *temp = graph->adjList[i];
    while(temp != NULL){
        if(graph->color[temp->tag] == -1){
            DFS_visit(graph,temp->tag,j);
        }
        temp = temp->next;
    }
    graph->color[i] = 1;
    graph->Order[*j] = i;
    (*j)++;
}
int DFS_visit_r(Node ** List,int *color,int i){
    color[i] = 0;
    Node *temp = List[i];
    int num3 = 0;
    int num4 = 0;
    while(temp != NULL){
        if(color[temp->tag] == -1){
            num4 = DFS_visit_r(List,color,temp->tag);
            num3++;
        }
        temp = temp->next;
    }
    color[i] = 1;
    if(num3-1 == 0 && num4 ==0)//沒有分支
        return 0;
    else //有分支
        return 1;
}
int main(){
    int b;
    int a;
    int mode;
    scanf("%d",&b);
    scanf("%d",&a);
    scanf("%d",&mode);
    Graph *graph = CreateGraph(b);
    for (int i = 0; i<a; i++){
        int u;
        int v;
        scanf("%d",&u);
        scanf("%d",&v);
        addEdge(graph,u-1,v-1);
    }
    int j  = 0;
    for(int i = 0;i<b;i++){//紀錄順序
        if(graph->color[i] == -1){
            DFS_visit(graph,i, &j);
        }
    }
    int num1 = 0;
    int num2 = 0;
    for(int i = b-1;i>-1;i--){
        if(graph->color_r[graph->Order[i]] == -1){
            DFS_visit_r(graph->reverse_adjList,graph->color_r,graph->Order[i]);
            num1++;
        }
        if(graph->color_a[graph->Order[i]] == -1){
            int num3 = DFS_visit_r(graph->adjList,graph->color_a,graph->Order[i]);
            num2 = num2+num3;
        }
    }
    printf("%d",num1);
    printf("\n");
    if(mode == 2){
        if(num2 == 1){
            printf("1");
        }
        else
            printf("0");
    }
}