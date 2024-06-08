#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int num;
    int rank;
    struct Node *p;
}Node;

void MakeSet(Node *x){
    x->p = x;
    x->rank = 0;
}

Node *FindSet(Node *x){
    if(x != x->p)
        x->p = FindSet(x->p);
    return x->p;
}

void Link(Node *x,Node *y){
    if(x->rank >y->rank)
        y->p = x;
    else{
        x->p = y;
        if(x->rank == y->rank)
            y->rank++;
    }
}

void Union(Node *x,Node *y){
    Node *v = FindSet(x);
    Node *w = FindSet(y);
    if(v->num != w->num){
        Link(v,w);
    }
}


void PrintPath(Node *x){
    Node *temp = x;
    while(temp != temp->p){
        printf("%d ",temp->num);
        temp = temp->p;
    }
    printf("%d",temp->num);
}
int main(){
    int n;
    int m;
    scanf("%d",&n);
    scanf("%d",&m);
    Node **set = (Node **)malloc(sizeof(Node *)*n);
    for(int i = 0;i<n;i++){
        set[i] = (Node *)malloc(sizeof(Node));
        set[i]->num = i+1;
        MakeSet(set[i]);
    }
    getchar();
    for(int i = 0;i<m;i++){
        char line[1024];
        char op;
        int num1;
        int num2;
        int result;
        if (fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%c %d %d\n",&op,&num1, &num2);
            if(result == 2){
                if(op == 'F'){
                    FindSet(set[num1-1]);
                }
                else{
                    PrintPath(set[num1-1]);
                    printf("\n");
                }
                    
            }
            else
                Union(set[num1-1],set[num2-1]);
        }
    }
}