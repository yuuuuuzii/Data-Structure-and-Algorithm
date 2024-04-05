#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    long long data;
    struct Node *child;
    struct Node *sibling;
    long long deg;
    long long id;
}Node;

Node *Merge(Node *heap1,Node *heap2);
Node *Reverse(Node *head);

Node *Union(Node *heap1,Node *heap2){
    Node *head = Merge(heap1,heap2);
    if(head == NULL)
        return head;
    Node *prev = NULL;
    Node *x = head;
    Node *next = x->sibling;
    while(next != NULL){
        if((x->deg != next->deg) || (next->sibling != NULL && (next->sibling)->deg == x->deg)){
            prev = x;
            x = next;
        }
        else{//這裡經過疊代後可能會使x為NULL?
            if(x->data >= next->data){//x當頭
                x->sibling = next->sibling;
                next->sibling = x->child;
                x->child = next;
                x->deg++;//還沒處理所有degree
            }
            else{//next 當頭
                if(prev == NULL)//直接assign head 到next
                    head = next;
                else //
                    prev->sibling = next;
                x->sibling = next->child;
                next->child = x;
                next->deg++;
                x = next;
            }
        }
        next = x->sibling;
    }
    return head;
}

Node *Merge(Node *heap1,Node *heap2){
    Node *head = NULL;
    Node *go = NULL;
    if(heap1 != NULL && heap2 != NULL){//兩個都不是NULL
        if(heap1->deg > heap2->deg){
            head = heap2;
            go = heap2;
            heap2 = heap2->sibling;
        }  
        else{
            head = heap1;
            go = heap1;
            heap1 = heap1->sibling;
        }
        while(heap1 != NULL && heap2 != NULL){
            if(heap1->deg <= heap2->deg){
                go->sibling = heap1;
                heap1 = heap1->sibling;
                go = go->sibling;
            }
            else{
                go->sibling = heap2;
                heap2 = heap2->sibling;
                go = go->sibling;
            }
        }
        if(heap1 != NULL)
            go->sibling = heap1;
        else 
            go->sibling = heap2;
        }
    else if(heap1 == NULL)//heap1 == NULL
        head = heap2;
    else //heap2 == NULL
        head = heap1;
    return head;
}
void Insert(Node **head, long long priority, long long id){
    Node *new = (Node *)malloc(sizeof(Node));
    new->child = NULL;
    new->data = priority;
    new->deg = 0;
    new->id = id;//job id
    new->sibling = NULL;
    *head = Union(*head,new);
}

long long Extract(Node **head, long long *num){
    (*num)--;
    Node *p = NULL;
    if((*head)->sibling == NULL){
        p = *head;
        *head = NULL;
    }
    else{
        Node *prev = *head;
        Node *Max = *head;
        Node *temp = (*head)->sibling;
        while(temp != NULL){
            if(temp->data > (Max->sibling)->data){
            Max = prev;
            }
            temp = temp->sibling;
            prev = prev->sibling;
        }
        if((Max->sibling)->data < (*head)->data){
            p = *head;
            (*head) = (*head)->sibling;
        }
        else{
            p = Max->sibling;
            Max->sibling = (Max->sibling)->sibling;
        }
    }
    Node *new_head = Reverse(p->child);
    *head = Union(*head,new_head);

    return p->id;
}

Node *Reverse(Node *head){
    Node *prev = NULL;
    Node *temp = head;
    Node *next = NULL;

    while(temp != NULL){
        next = temp->sibling;
        temp->sibling = prev;
        prev = temp;
        temp = next;
    }
    return prev;
}
int main(){
    long long num;
    long long op;
    Node *printers[num];
    long long num_jobs[num];
    scanf("%d",&num);
    scanf("%d",&op);
    for(int i = 0; i< num;i++){//初始化
        printers[i] = NULL;
        num_jobs[i] = 0;
    }
    getchar();
    for(int i = 0; i<op; i++){
        char line[1024];
        long long num1;
        long long num2;
        long long num3;
        long long num4;
        int result;
        if(fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%d %d %d %d", &num1, &num2, &num3, &num4);
            if (result == 4){//add
                Insert(&printers[num4-1],num3,num2);
                num_jobs[num4-1]++;
                printf("%lld jobs waiting on printer %lld",num_jobs[num4-1],num4);
                printf("\n");
            }
            else if(result == 2){//print
                if(printers[num2-1] == NULL){
                    printf("no documents in queue");
                    printf("\n");
                }
                else{
                    long long id = Extract(&printers[num2-1],&num_jobs[num2-1]);
                    printf("%lld printed",id);
                    printf("\n");
                }
            }
            else if(result == 3){//move
                num_jobs[num3-1] = num_jobs[num3-1] + num_jobs[num2-1];
                num_jobs[num2-1] = 0;
                printf("%lld jobs waiting on printer %lld after moving",num_jobs[num3-1],num3);
                printf("\n");
                printers[num3-1] = Union(printers[num3-1],printers[num2-1]);
                printers[num2-1] = NULL;
            }
        }
    }
}

