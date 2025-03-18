#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
    long long data;
    struct Node *next;
    struct Node *below;
    struct Node *prev;
}Node;
int CoinFlip(long long k, int i);
void SlowGet(Node *head,long long get){
    Node *temp = head;
    while(temp->next != NULL && get <= (temp -> next) -> data){
        temp = temp -> next;
        printf("%lld ",temp->data);
    }
    if(temp == head){
        printf("%d",-1);
    }
    printf("\n");
}

Node **FastGet(Node *head,long long get,Node *top,int LNum,int dis){//直接呼叫，或者在Insert 後記得要free()
    Node **arr = (Node **)malloc(sizeof(Node *)*(LNum));
    int i = (LNum)-1;
    Node *temp = top;//如果不是next?
    while (temp->below != NULL){//最後一層
        while(temp->next != NULL && get <= (temp -> next) -> data){
            temp = temp -> next;
            if(dis == 1 && temp->data != -1)
                printf("%lld ",temp->data);
        }
        arr[i] = temp;
        temp = temp->below;
        if(dis == 1 && temp->data != -1)
            printf("%lld ",temp->data);
        i--;
    }
    while(temp->next != NULL && get <= (temp -> next) -> data){
        temp = temp -> next;
        if(dis == 1 && temp->data != -1)
            printf("%lld ",temp->data);
    }
    arr[i] = temp;
     //如果為空，則temp為NULL
    if(temp == head && dis == 1)
        printf("%d",-1);

    if(dis == 1)
        printf("\n");
    return arr;
}

void Insert(Node *head, long long get,Node **top,int *LNum){
    Node *new = (Node *)malloc(sizeof(Node));
    new->below = NULL;
    new->next = NULL;
    new->prev = NULL;
    new->data = get;
    Node **arr = FastGet(head, get,*top,*LNum,0);

    Node *p = arr[0]->next;
    arr[0]->next = new;
    new->prev = arr[0];
    new->next = p;
    if(p != NULL)
        p->prev = new;
    int i = 1;

    while(CoinFlip(get,i)){
        if(i<(*LNum)){
            Node *p = (Node *)malloc(sizeof(Node));
            p->below = new;
            p->data = get;
            Node *temp = arr[i]->next;
            arr[i]->next = p;

            p->prev = arr[i];
            p->next = temp;
            if(temp != NULL)
                temp->prev = p;
            i++;
            new = p;
        }
        else{
            Node *new_top = (Node *)malloc(sizeof(Node));
            new_top->below = (*top);
            new_top->data = -1;
            new_top->next = (Node *)malloc(sizeof(Node));

            (*top) = new_top;
            (new_top->next)->below = new;
            (new_top->next)->prev = new_top;
            (new_top->next)->next = NULL;
            (new_top->next)->data = get;
            new = new_top->next;
            i++;
            (*LNum)++;
        }
    }
    free(arr);
}
void Remove(Node *head,Node **top,long long get,int *LNum){
    Node **arr = FastGet(head,get,*top,*LNum,0);
    int i = 0;
    while(i<(*LNum) && (arr[i]->data == get)){
        (arr[i]->prev)->next = arr[i]->next;
        if(arr[i]->next != NULL){
            (arr[i]->next)->prev = arr[i]->prev;
        }  
        if((arr[i]->prev)->data == -1 && arr[i]->next == NULL && arr[i]->prev != head){
             *top = (arr[i]->prev)->below;
            (*LNum) = i;
        }
        i++;
    }
    free(arr);
}
int CoinFlip(long long k, int i){
   if((k >> (long long)(i-1))%2 == 0)
        return 0;
    else
        return 1;//1代表要插入
}
int main(){
    //初始化
    Node *head = (Node *)malloc(sizeof(Node));
    head->below = NULL;
    head->next = NULL;
    head->prev = NULL;
    head->data = -1;
    Node *top = head;
    int LNum = 1;
    int op;
    scanf("%d",&op);
    for(int i = 0;i<op;i++){
        int type;
        long long num;
        scanf("%d",&type);
        scanf("%lld",&num);
        if(type == 1){
            SlowGet(head,num);
        }
        else if(type ==2){
            Node **arr = FastGet(head, num,top,LNum,1);
            free(arr);
        }
        else if(type == 3){
            Insert(head,num,&top,&LNum);
        }
        else if(type == 4){
            Remove(head,&top,num,&LNum);
        }
    }
    return 0;
}