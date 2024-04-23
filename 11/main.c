#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    long long length;//距離原點距離
    long long tag;//編號
    long long is_empty;
    long long deep_length;//子孫往葉節點的值
    struct Node *max_deep;//維護deep 最大值list
    struct Node *max_deep_tail;
    struct Node *prev;
    struct Node *next1;

    //下列為處理祖先、孩子的tree
    struct Node *parent;
    //下列為child link list
    struct Node *child;//head
    struct Node *tail;
    struct Node *next;
}Node;

typedef struct treasure{
    long long output;
    int tag;
    struct treasure *next;
    struct treasure *prev;
}treasure;

void push(Node **arr, Node *n, long long *top){//紀錄走訪的節點
    (*top)++;
    arr[*top] = n;
}
Node* pop(Node **arr, long long *top){
    Node *data = arr[*top];
    (*top)--;
    return data;
}
void enqueue(Node **head, Node *child, Node **tail){
    if((*head) == NULL){
        (*head) = child;
        (*tail) = child;
    }
    else{
        (*tail)->next = child;
        (*tail) = (*tail)->next;
    }
}
/*Node *dequeue(Node **head,Node **tail){
    Node *temp = (*head);
    (*head) = (*head)->next;
    if ((*head) == NULL) {
        (*tail) = NULL; 
    }
    return temp;
}*/
void downstream(Node **current,Node **arr,long long *top){
    if((*current)->child != NULL){
        printf("%d",((*current)->child)->tag);
        printf("\n");
        (*current) = (*current)->child;
        push(arr,(*current),top);
    }
    else{
        printf("-1");
        printf("\n");
    }
}

void upstream(Node **current,Node **arr, long long *top, treasure **queue,long long *q_num, treasure **tail){
    if((*current)->tag != 0){
        //Node *temp = (*current);
        if(((*current)->is_empty)>1)
            ((*current)->parent)->is_empty = (*current)->parent->is_empty + ((*current)->is_empty)-1;
        
        (*current) = (*current)->parent;
        printf("%d",(*current)->tag);
        printf("\n");
        pop(arr,top);
        
        if((*current)->child == (*current)->max_deep){
            (*current)->max_deep = ((*current)->max_deep)->next1;//7:54
            if((*current)->max_deep== NULL){
                (*current)->max_deep_tail = NULL;
            }
        }

        if((*current)->child->is_empty != 0){//還沒檢查NULL
            (*q_num)--;
            (*tail) = (*tail)->prev;
            if ((*tail) == NULL) {
                (*queue) = NULL; 
            }
        }

        if((*current)->child->next != NULL){
            (*current)->child = (*current)->child->next;
        }
        else{
            (*current)->child = NULL;
            (*current)->tail = NULL;
        }
    }
    else{
        printf("-1");
        printf("\n");
    }
}
long long plan(Node **arr,long long top, long long ti){
    if(ti >=((arr[top]->length)-(arr[0]->length))){
        return 0;
    }
    else{
        long long right = 0;
        long long left = top;
        while(left-1 != right){

            long long m = (right+left)/2;
            if((ti-((arr[left]->length)-(arr[m]->length)))>=0){
                ti = ti-((arr[left]->length)-(arr[m]->length));
                left = m;
            }
            else if (ti-((arr[left]->length)-(arr[m]->length)) < 0){
                right = m;
            }
        }
        /*printf("%lld,%lld",left,right);
        printf("\n");*/
        return left;
    }
}
long long DFS(Node *root){
    if (root->child == NULL){
        return 0;
    }
    Node *temp = root->child;
    while(temp != NULL){
        temp->length = temp->length+root->length;
        /*printf("d%lld length is %lld",temp->tag,temp->length);
        printf("\n");*/
        long long local = temp->length-root->length + DFS(temp);
        if(root->max_deep == NULL){
            root->max_deep = temp;
            root->max_deep_tail = temp;
        }
        else{
            while(root->max_deep_tail != NULL && local > ((root->max_deep_tail)->deep_length+(root->max_deep_tail)->length-root->length)){
                root->max_deep_tail =  root->max_deep_tail->prev;
            }
            //add
            if(root->max_deep_tail == NULL){
                root->max_deep_tail = temp;
                root->max_deep = temp;
            }
            else{
                root->max_deep_tail->next1 = temp;
                temp->prev = root->max_deep_tail;
                root->max_deep_tail = root->max_deep_tail->next1;
            }
        }
        temp = temp->next;
    }
    root->deep_length =  (root->max_deep)->deep_length + (root->max_deep)->length-root->length;
   /*printf("d%lld deep length is %lld",root->tag,root->deep_length);
    printf("\n");
    printf("d%lld max dep length is %lld",root->tag,root->max_deep->length);
    printf("\n");*/
    return root->deep_length;
}
void discover(treasure **queue, treasure **tail,Node **current, long long pi,Node **arr,Node **dungeons,long long *q_num, long long top){
    (*q_num)++;
    (*current)->is_empty++;
    treasure *new = (treasure *)malloc(sizeof(treasure));
    new->next = NULL;
    new->prev = NULL;
    if(pi-(*current)->length >= 0){
        new->tag = 1;
        new->output = pi-(*current)->length;
    }
    else{
        new->tag = 0;
        new->output = arr[plan(arr,top,pi)-1]->tag;
    }
 
    if((*queue)== NULL){
        (*queue) = new;
        (*tail) = new;
    }
    else{//add
        (*tail)->next = new;
        new->prev = (*tail);
        (*tail) = (*tail)->next;
    }   
    if(*q_num > top){
        treasure *temp = (*queue);
        (*queue) = (*queue)->next;
        if((*queue)== NULL){//7:00
            (*tail) = NULL;
        }
        (*q_num)--;
        if(temp->tag == 1){
            printf("value remaining is %lld",temp->output);
            printf("\n");
        }
        else{
            printf("value lost at %lld",temp->output);
            printf("\n");
        }
    }
}
int main(){
    long long n;
    long long m;
    long long q;
    scanf("%lld",&n);
    scanf("%lld",&m);
    scanf("%lld\n",&q);
    Node **arr = (Node **)malloc(sizeof(Node *)*1000000);//用來存走過的路徑，為stack
    long long top = -1;
    Node **dungeons = (Node **)malloc(sizeof(Node *)*n);
    for(int i = 0; i<n; i++){
        dungeons[i] = (Node *)malloc(sizeof(Node));
        dungeons[i]->length = 0;
        dungeons[i]->tag = i;
        dungeons[i]->is_empty = 0;//0為空
        dungeons[i]->prev = NULL;
        dungeons[i]->parent = NULL;
        dungeons[i]->max_deep = NULL;
        dungeons[i]->max_deep_tail = NULL;
        dungeons[i]->next1 = NULL;
        dungeons[i]->deep_length = 0;
        dungeons[i]->child = NULL; //child link list
        dungeons[i]->next = NULL;
        dungeons[i]->tail = NULL;
    }
    push(arr,dungeons[0],&top);
  
    for(int i = 0; i < m; i++){
        long long u,v;
        long long l;
        scanf("%lld %lld %lld\n",&u,&v,&l);
        dungeons[v]->length = l;
        dungeons[v]->parent = dungeons[u];
        enqueue(&dungeons[u]->child,dungeons[v],&dungeons[u]->tail);
    }
    Node *current = dungeons[0];
    dungeons[0]->deep_length = DFS(dungeons[0]);
    treasure *queue  = NULL;
    treasure *tail = NULL;
    long long q_num = 0;
  
    for(long long i = 0; i<q; i++){
        char line[1024];
        long long num1;
        long long num2;
        long long num3;
        int result;
        if (fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%lld %lld %lld\n", &num1, &num2, &num3);
            if (result == 1){
                if(num1 == 1){//1
                    downstream(&current, arr, &top);
                }
                else if (num1 == 2){//2
                    upstream(&current,arr,&top,&queue,&q_num,&tail);
         
                }
                else{//4
                    if((current->max_deep)!= NULL){
                        printf("%lld",(current->max_deep)->deep_length +(current->max_deep)->length-(current)->length);
                        printf("\n");

                    }
                    else{
                        printf("0");
                        printf("\n");
                    }
                }
            }
            else if(result == 2){
                if(num1 == 3){//3
                    printf("%lld",arr[plan(arr,top,num2)]->tag);
                    printf("\n");
                }
                else{//5
                    discover(&queue,&tail,&current,num2,arr,dungeons,&q_num,top);
                }
            }
            else{//6
                if(current->child == NULL){
                    current->child = dungeons[num2];
                    current->tail = dungeons[num2];
                }
                (current->tail)->next = dungeons[num2];
                current->tail = (current->tail)->next;
                dungeons[num2]->parent = current;
                dungeons[num2]->length = num3;
                dungeons[num2]->deep_length = DFS(dungeons[num2]);
    
                
                if(current->max_deep == NULL){
                    current->max_deep = dungeons[num2];
                    current->max_deep_tail = dungeons[num2];
                }
                else{
                    while(current->max_deep_tail != NULL && dungeons[num2]->deep_length+dungeons[num2]->length > (current->max_deep_tail)->deep_length-current->length){
                        current->max_deep_tail =  current->max_deep_tail->prev;
                    }
                    //add
                    if(current->max_deep_tail == NULL){
                        current->max_deep_tail = dungeons[num2];
                        current->max_deep = dungeons[num2];
                    }
                    else{
                        current->max_deep_tail->next1 = dungeons[num2];
                        dungeons[num2]->prev = current->max_deep_tail;
                        current->max_deep_tail =  dungeons[num2];
                    }
                }
            }
        }
    }

    return 0;
}