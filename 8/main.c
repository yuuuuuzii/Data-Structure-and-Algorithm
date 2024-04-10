#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

void FCD(Node *head){
    Node *hare = head;
    Node *tortoise = head;
    while(hare != NULL && hare->next != NULL){
        printf("%d ",hare->data);
        hare = (hare->next)->next;
        tortoise = tortoise->next;
        if (hare == tortoise){
            printf("%d ",hare->data);
            break; 
        }
    }
    if(hare != NULL && hare->next == NULL)
        printf("%d ",hare->data);
}
int main(){
    int num;
    scanf("%d",&num);
    Node *head = NULL;
    Node *arr[num];
    int nextArr[num];
    for(int i = 0;i<num;i++){
        Node *new = (Node *)malloc(sizeof(Node));
        new->next = NULL;
        arr[i] = new;
        int data;
        int next;
        scanf("%d",&data);
        scanf("%d",&next);
        arr[i]->data = data;
        nextArr[i] = next;
        if(i == 0)
            head = arr[i];
    }
    for(int i = 0;i<num;i++){
        if(nextArr[i] != 0)
            arr[i]->next = arr[nextArr[i]-1];
    }
    FCD(head);
}