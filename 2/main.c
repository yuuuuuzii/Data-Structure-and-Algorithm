#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}Node;

void Add(Node **head, int new_data,Node **tail,int *count) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if(*tail == NULL){
        *tail = new_node;
    }
    new_node->data = new_data;
    new_node->next = *head;
    *head = new_node;
    (*count)++;
    //printf("%s","add ok");
}
void Remove(Node **head,Node **tail,int *count) {
    if(*head != NULL){
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        (*count)--;
    }
    if(*head == NULL)
        *tail = NULL;
    //printf("%s","Re ok");
}
Node *Move(Node **head1,Node **head2,Node **tail1,Node **tail2,int *count1,int *count2){
    (*count2) = (*count2)+ (*count1);
    (*count1) = 0;
    if(*head1 != NULL && *head2 != NULL){
        (*tail1)->next = *head2;
        Node *temp = *head1;
        *head1 = NULL;
        *tail1 = NULL;
        return temp;
    }
    else if(*head1 == NULL && *head2 != NULL){
        return *head2;
    }
    else if(*head1 != NULL && *head2 == NULL){
        *tail2 = *tail1;
        Node *temp = *head1;
        *head1 = NULL;
        *tail1 = NULL;
        return temp;
    }
}
Node *Merge(Node **head1,Node **head2,Node **tail1,Node **tail2,int *count1,int *count2){
    *count2 = (*count2)+(*count1);
    *count1 = 0;
    Node* temp1 = *head1;
    Node* temp2 = *head2;
    while((temp1 != NULL && temp2 != NULL)){
        Node *p1 = temp1->next;
        temp1->next = temp2;
        temp1 = p1;
        if(temp1 != NULL){
            Node *p2 = temp2->next;
            temp2->next = temp1;
            temp2 = p2;
        }
    }
    if(temp1 != NULL && temp2 == NULL){
        *tail2 = *tail1;    
    }   
    
    if(*head1 != NULL){
        temp1 = *head1;
        *head1 = NULL;
        *tail1 = NULL;
        return temp1;
    }
    else{
        return *head2;
    }
   
}
int main(){
    int num;
    int op;
    scanf("%d",&num);
    scanf("%d",&op);
    getchar();
    Node **head = (Node **)malloc(sizeof(Node *)*num);
    Node **tail = (Node **)malloc(sizeof(Node *)*num);
    int *count = (int *)malloc(sizeof(int)*num);
    for(int i = 0; i<num; i++){
        head[i] = NULL;
        tail[i] = NULL;
        count[i] = 0;
   }
    for(int i = 0; i < op; i++){
        char line[1024]; // 存儲用戶輸入的緩衝區
        int num1, num2, num3;
        int result;

    if (fgets(line, sizeof(line), stdin)) { // 讀取一行輸入
        // 嘗試解析三個整數
        result = sscanf(line, "%d %d %d", &num1, &num2, &num3);
        if (result == 3) {
            if(num1 == 1){
                Add(&head[num2-1],num3,&tail[num2-1],&count[num2-1]);
            }
            else if(num1 == 3){
                head[num3-1] = Move(&head[num2-1],&head[num3-1],&tail[num2-1],&tail[num3-1],&count[num2-1],&count[num3-1]);
            }
            else if(num1 == 4){
                head[num3-1] = Merge(&head[num2-1],&head[num3-1],&tail[num2-1],&tail[num3-1],&count[num2-1],&count[num3-1]);
            }
        } else if (result == 2) {
                Remove(&head[num2-1],&tail[num2-1],&count[num2-1]);
        }
    }
   }
    for(int i = 0; i< num; i++){
        printf("%d ",count[i]);
        if(head[i] != NULL){
            Node *temp = head[i];
            for(int j = 0;j<count[i];j++){
                printf("%d ",temp->data);
                Node *clear = temp;
                temp = temp->next;
                free(clear);
            }
        }
        printf("\n");
    }
   free(head);
   free(tail);
   free(count);
   return 0;
}