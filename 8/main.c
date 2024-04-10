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
}
int main(){
    int num;
    scanf("%d",&num);
    Node *head = NULL;
    Node *temp = NULL;
    int data = 0;
    int next = 0;
    for(int i = 1;i<=num;i++){
        Node *new = (Node *)malloc(sizeof(Node));
        new->next = NULL;
        scanf("%d",&data);
        new->data = data;
        if(i == 1){
            head = new;
            temp = new;
        }
        if(next == i){
            temp->next = new;
            temp = temp->next;
        }
        scanf("%d",&next);
        if(next != 0 && next != i+1){
            Node *run  = head;
            for(int j = 0;j<(next-1);j++){
                run = run->next;
            }
            new->next = run;
        }
    }
    FCD(head);
}