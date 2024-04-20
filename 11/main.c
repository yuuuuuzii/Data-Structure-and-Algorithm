#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    long long length;//距離原點距離
    int tag;//編號
    int is_empty;
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
    struct treasure *next;
    struct treasure *prev;
}treasure;

void push(Node **arr, Node *n, int *top){//紀錄走訪的節點
    (*top)++;
    arr[*top] = n;
}
Node* pop(Node **arr, int *top){
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
Node *dequeue(Node **head,Node **tail){
    Node *temp = (*head);
    (*head) = (*head)->next;
    if ((*head) == NULL) {
        (*tail) = NULL; 
    }
    return temp;
}
void downstream(Node **current,Node **arr,int *top){
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
void upstream(Node **current,Node **arr, int *top, treasure **queue, treasure **tail){
    if((*current)->tag != 0){
        (*current) = (*current)->parent;
        printf("%d",(*current)->tag);
        printf("\n");
        pop(arr,top);
        
        if((*current)->child == (*current)->max_deep){
            (*current)->max_deep = ((*current)->max_deep)->next;//記得檢查是否為NULL
        }
        if((*current)->child->is_empty != 0){//還沒檢查NULL
            (*tail) = (*tail)->prev;
            if ((*tail) == NULL) {
                (*queue) = NULL; 
            }
        }
        free(dequeue(&(*current)->child,&(*current)->tail));
    }
    else{
        printf("-1");
        printf("\n");
    }
}
long long plan(Node **arr,int top, long long ti){
    if(ti >=((arr[top]->length)-(arr[0]->length))){
        return 0;
    }
    else{
        int right = top;
        int left = 0;
        while(left<=right){
            int m = (right+left)/2;
            if(((arr[right]->length)-(arr[m]->length))<ti){
                ti = ti-((arr[right]->length)-(arr[m]->length));
                right = m-1;
            }
            else if (((arr[right]->length)-(arr[m]->length))>ti){
                left = m+1;
            }
            else{
                left = m;
                break;
            }
        }
        return left;
    }
}
long long DFS(Node *root){
    if (root == NULL || root->child == NULL){
        return 0;
    }
    Node *temp = root->child;
    while(temp != NULL){
        long long local = temp->length + DFS(temp);
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
                root->max_deep_tail = temp;
            }
        }
        temp = temp->next;
    }
    root->deep_length =  (root->max_deep)->deep_length + (root->max_deep)->length-root->length;
    return root->deep_length;
}
void discover(treasure **queue, treasure **tail,Node **current, long long pi,Node **arr,Node **dungeons,int *q_num, int top){
    (*q_num)++;
    (*current)->is_empty++;
    treasure *new = (treasure *)malloc(sizeof(treasure));
    if(pi-(*current)->length >= 0){
        new->output = pi-(*current)->length;
    }
    else{
        new->output = -arr[plan(arr,top,pi)]->tag ;
    }
    new->next = NULL;
    new->prev = NULL;
    if((*queue)== NULL){
        (*queue) = new;
        (*tail) = new;
    }
    else{
        (*tail)->next = new;
        new->prev = (*tail);
        (*tail) = (*tail)->next;
    }   
    if(*q_num > top){
        treasure *temp = (*queue);
        (*queue) = (*queue)->next;
        (*q_num)--;
        if(temp->output >= 0){
            printf("value remaining is %lld",temp->output);
            printf("\n");
        }
        else{
            printf("value lost at %lld",-temp->output);
            printf("\n");
        }
    }
}
int main(){
    int n;
    int m;
    int q;
    scanf("%d",&n);
    scanf("%d",&m);
    scanf("%d",&q);
    Node **arr = (Node **)malloc(sizeof(Node *)*1000000);//用來存走過的路徑，為stack
    int top = -1;
    Node **dungeons = (Node **)malloc(sizeof(Node *)*n);
    for(int i = 0; i<n; i++){
        dungeons[i] = malloc(sizeof(Node));
        dungeons[i]->length = 0;
        dungeons[i]->tag = i;
        dungeons[i]->is_empty = 0;//0為空
        dungeons[i]->prev = NULL;
        dungeons[i]->parent = NULL;
        dungeons[i]->max_deep = NULL;
        dungeons[i]->next1 = NULL;
        dungeons[i]->deep_length = 0;
        dungeons[i]->child = NULL; //child link list
        dungeons[i]->next = NULL;
        dungeons[i]->max_deep_tail = NULL;
    }
    push(arr,dungeons[0],&top);
    getchar();
    for(int i = 0; i < m; i++){
        int u,v;
        long long l;
        scanf("%d %d %lld",&u,&v,&l);
        dungeons[v]->length = (dungeons[u]->length)+l;
        dungeons[v]->parent = dungeons[u];
        enqueue(&dungeons[u]->child,dungeons[v],&dungeons[u]->tail);
    }
    Node *current = dungeons[0];
    dungeons[0]->deep_length = DFS(dungeons[0]);
    treasure *queue  = NULL;
    treasure *tail = NULL;
    int q_num = 0;
    getchar();
    for(int i = 0; i<q; i++){
        char line[1024];
        int num1;
        int num2;
        int num3;
        int result;
        if (fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%d %d %d", &num1, &num2, &num3);
            if (result == 1){
                if(num1 == 1){//1
                    downstream(&current, arr, &top);
                }
                else if (num1 == 2){//2
                    upstream(&current,arr,&top,&queue,&tail);
         
                }
                else{//4
                if((current->max_deep)!= NULL){
                    printf("%lld",(current->max_deep)->deep_length +(current->max_deep)->length);
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
                (current->tail)->next = dungeons[num2];
                current->tail = (current->tail)->next;
                dungeons[num2]->parent = current;
                dungeons[num2]->deep_length = DFS(dungeons[num2]);
    
                dungeons[num2]->length = current->length+num3;
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
                        current->max_deep_tail->next1 =  dungeons[num2];
                        dungeons[num2]->prev = current->max_deep_tail;
                        current->max_deep_tail =  dungeons[num2];
                    }
                }
            }
        }
    }
    free(arr);
    return 0;
}