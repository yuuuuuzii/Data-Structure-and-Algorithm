#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node *left;
    struct Node *right;
    long long data;
    long long priority;
    long long sum;
    long long size; //包含root 的size

}Node;
long long Get_index(Node *root,long long base);
long long Range_of_sub_tree(Node *root,long long l,long long r, long long index){//index 為root位置

    long long left = (root->left != NULL) ? index - root->left->size : index;
    long long right = (root->right != NULL) ? index + root->right->size : index;

    return (left == l && right == r);
}

long long Calculate_Sum(Node *root, long long l, long long r,long long index){
    if(Range_of_sub_tree(root,l,r,index)){
        return root->sum;
    }
    long long sum = 0;
    
    if((l<=index) && (index<=r))
        sum = sum + root->data;
    if(l<index){//去左邊找
        long long min = (index-1 < r)? index-1:r;

        sum = sum + Calculate_Sum(root->left,l,min,Get_index(root->left,index-Get_index(root,0)));
    }
    if(r>index){

        long long max = (l>index+1)? l: index+1;

        sum = sum + Calculate_Sum(root->right,max,r,Get_index(root->right,index));
    }
    return sum;
}

long long Get_index(Node *root,long long base){
    long long index = 0;
    if(root != NULL){
        if(root->left == NULL)
            index = base +1;
        else
            index = root->left->size + 1 + base;
    }
    return index;
}
void Sum(Node *root){
        root->sum = root->data;
        root->size = 1;
        if(root->left != NULL){
            root->sum = root->sum + root->left->sum;
            root->size = root->size +root->left->size;
        }
        if(root->right != NULL){
            root->sum = root->sum + root->right->sum;
            root->size = root->size + root->right->size;
        }
}
Node **Split(Node *root,long long k,long long index){//index 是 root 位置
    Node **arr = (Node **)malloc(sizeof(Node *)*2);
    arr[0] = NULL;
    arr[1] = NULL;
    if(root != NULL){
        if(index <= k){ //去右邊找
            arr[0] = root;
            Node **temp = Split(root->right,k,Get_index(root->right,index));
            root->right = temp[0];
            arr[1] = temp[1];
            free(temp);
        }
        if(index > k){
            arr[1] = root;
            Node **temp = Split(root->left,k,Get_index(root->left,index-Get_index(root,0)));
            root->left = temp[1];
            arr[0] = temp[0];
            free(temp);
        }
        Sum(root);
    }
    return arr;
}
Node *Merge(Node *left,Node *right){
    if(left == NULL)
        return right;
    if(right == NULL)
        return left;
        
    if(left != NULL && right != NULL){
        if(left->priority > right->priority){
            left->right = Merge(left->right,right);
            Sum(left);
            return left;
        }
        else{
            right->left = Merge(left,right->left);
            Sum(right); 
            return right;
        }
    }
}
void Inorder(Node *root){
    if(root == NULL)
        return;
     
    Inorder(root->left);
    printf("%lld ",root->data);
    Inorder(root->right);
}
int main(){
    long long n;
    long long t;
    scanf("%lld",&n);
    scanf("%lld",&t);
    
    Node *root = NULL;
    for(int i= 0;i<n;i++){
        Node *new = (Node *)malloc(sizeof(Node));
        new->priority = rand();
        scanf("%lld",&new->data);
        new->left = NULL;
        new->right = NULL;
        new->size = 1;
        new->sum = new->data;
        root = Merge(root,new);
    }
    getchar();
    
    for(int i = 0;i<t;i++){
        
        char line[1024];
        long long num1;
        long long num2;
        long long num3;
        
        int result;
        if (fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%lld %lld %lld", &num1, &num2, &num3);
            if(result == 2){//delete
                if(num2 == 0){
                    Node **temp1 = Split(root,1,Get_index(root,0));
                    root = temp1[1];
                }
                else if(num2 == root->size){
                    Node **temp1 = Split(root,num2-1,Get_index(root,0));

                    root = temp1[0];
                }
                else{
                    Node **temp1 = Split(root,num2, Get_index(root,0));
                    Node **temp2 = Split(temp1[0],num2-1, Get_index(temp1[0],0));
            
                    root = Merge(temp2[0],temp1[1]);
                }
            
            }
            else{
                if(num1 == 2){
                    Node *new = (Node *)malloc(sizeof(Node));
                    new->data = num3;
                    new->left = NULL;
                    new->right = NULL;
                    new->priority = rand();
                    new->size = 1;
                    new->sum = num3;
                    if(num2 == 0){
                        root = Merge(new,root);
                    }
                    else if(num2 == root->size){
                        root = Merge(root,new);
                    }
                    else{
                        
                        Node **temp = Split(root,num2,Get_index(root,0));
                        root = Merge(Merge(temp[0],new),temp[1]);
                    }
                    
                }
                else{
                    long long sum = Calculate_Sum(root,num2,num3,Get_index(root,0));
                    printf("%lld",sum);
                    printf("\n");
                }
            }
        }
    }
    if(root != NULL){
        printf("%lld",root->size);
        printf("\n");
    }
    else{
        printf("0");
        printf("\n");
    }
    
    Inorder(root);
}