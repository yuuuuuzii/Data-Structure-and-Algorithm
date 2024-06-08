#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int index;
    char edge;
}Node;

typedef struct Graph{
    int vertex_num;
    char *color;
    struct Node ***List;
    int *degree;
    int *dis;
}Graph;

void DFS_visit(Graph *graph,int u,int *time){
    graph->color[u] = 'G';
    (*time)++;
    graph->dis[u] =(*time);
    for(int i = 0;i<graph->degree[u];i++){
        if(graph->color[graph->List[u][i]->index] == 'W'){
            DFS_visit(graph,graph->List[u][i]->index,time);
            graph->List[u][i]->edge = 'T';
        }
        else if(graph->color[graph->List[u][i]->index] == 'G')
            graph->List[u][i]->edge = 'B';
        else{
            if(graph->dis[graph->List[u][i]->index]>graph->dis[u])
                graph->List[u][i]->edge = 'F';
            else
                 graph->List[u][i]->edge = 'C';
        }
    }
    graph->color[u] = 'B';
    (*time)++;
    
}

void DFS(Graph *graph){
    int time = 0;
    for(int i = 0;i<graph->vertex_num;i++){
        if(graph->color[i]=='W'){
            DFS_visit(graph,i,&time);
        }
    }
}

int main(){
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    scanf("%d",&graph->vertex_num);
    graph->color = (char *)malloc(sizeof(char)*graph->vertex_num);
    graph->List = (Node ***)malloc(sizeof(Node **)*graph->vertex_num);
    graph->degree = (int *)malloc(sizeof(int)*graph->vertex_num);
    graph->dis = (int *)malloc(sizeof(int)*graph->vertex_num);
    
    for(int i = 0;i<graph->vertex_num;i++){
        scanf("%d",&graph->degree[i]);
        graph->color[i] = 'W';
        graph->List[i] = (Node **)malloc(sizeof(Node *)*graph->degree[i]);
        for(int j = 0;j<graph->degree[i];j++){
            graph->List[i][j] = (Node *)malloc(sizeof(Node));
            scanf("%d",&graph->List[i][j]->index);
            graph->List[i][j]->index--;
        }
    }

    DFS(graph);
    for(int i = 0;i<graph->vertex_num;i++){
        printf("%d ",i+1);
        for(int j = 0;j<graph->degree[i];j++){
            printf("%c",graph->List[i][j]->edge);
        }
        printf("\n");

    }
}