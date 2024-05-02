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
    int *group;
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
    graph->group = (int *)malloc(sizeof(int)*block_num);
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
        graph->group[i] = -1;
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
void DFS_visit_r(int *group, Node ** List,int *color,int i, int num1,int *num2){
    color[i] = 0;
    group[i] = num1;
    Node *temp = List[i];
    while(temp != NULL){
        if(num1 >=1 && num1 == group[temp->tag]+1){
            *num2 = 1;
        }
        if(color[temp->tag] == -1){
            DFS_visit_r(group,List,color,temp->tag,num1,num2);
        }
        temp = temp->next;
    }
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
    int num2 = 1;
    for(int i = b-1;i>-1;i--){
        int num3 = 0;
        if(graph->color_r[graph->Order[i]] == -1){
            DFS_visit_r(graph->group,graph->reverse_adjList,graph->color_r,graph->Order[i],num1, &num3);
            if(num1>0 && num3 == 0){//沒有連通
                num2 = 0;
            }
            num1++;
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