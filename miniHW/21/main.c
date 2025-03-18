#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int key;
    char color;//0是紅色，1是黑色

    struct Node *left;
     struct Node *right;
      struct Node *parent;
}Node;
void InsertNode(Node *root,Node *new){
    Node *temp = root;
    
    while(1){
        if(temp->key > new->key){
            if(temp->left == NULL){//插入
                temp->left = new;
                new->parent = temp;
                break;
            }
            else
                temp = temp->left;
        }
        else{
            if(temp->right == NULL){//插入
                temp->right = new;

                new->parent = temp;
                break;
            }
            else
                temp = temp->right;
        }
    }
}
void Left_rotate(Node **root,Node *x){
    Node *y = x->right;
    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == NULL)
        (*root) = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    
}
void Right_rotate(Node **root, Node *x) {
    Node *y = x->left;        
    x->left = y->right;       
    if (y->right != NULL)     
        y->right->parent = x;
    y->parent = x->parent;   
    if (x->parent == NULL)  
        (*root) = y;
    else if (x == x->parent->right)  
        x->parent->right = y;
    else                     
        x->parent->left = y;
    y->right = x;            
    x->parent = y;
}

Node *Find(Node *root,int key,int *b_depth,int *depth){
    Node *temp = root;
    while(temp->key != key){
        if(temp->color == 'B')
            (*b_depth)++;
        if(temp->key > key)
            temp = temp->left;
        else
            temp = temp->right;
        
        (*depth)++;
    }
    return temp;
}

int main(){
    int n;
    scanf("%d",&n);
    Node *root = NULL;
    for(int i = 0;i<n;i++){
        Node *new = (Node *)malloc(sizeof(Node));
        scanf("\n%c",&new->color);
        scanf(" %d",&new->key);
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
        
        if(root == NULL)
            root = new;
        else{
            InsertNode(root,new);
        }
    }
    int m;
    scanf("%d",&m);
    for(int i = 0;i<m;i++){
        char op;
        int key;
        scanf("\n%c",&op);
        scanf(" %d",&key);
        int b_depth = 0;
        int depth = 0;
        Node *target = Find(root,key,&b_depth,&depth);
        if(op == 'L')
            Left_rotate(&root,target);
        else if(op == 'R')
            Right_rotate(&root,target);
        else{
            if(target->left != NULL)
                printf("%d ",target->left->key);
            else
                printf("-1 ");
            if(target->right != NULL)
                printf("%d ",target->right->key);
            else
                printf("-1 ");
            printf("%d %d",b_depth,depth);
            printf("\n");
        }
    }
}