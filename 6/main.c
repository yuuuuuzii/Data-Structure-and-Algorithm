#include <stdio.h>
#include <stdlib.h>
void Insert(int *arr,int m,int budget,int *op){
    int data = arr[m];
    int i = m-1;
    while (i >= 0 && arr[i]>data && (*op) < budget){
        arr[i+1] = arr[i];
        i = i-1;
        (*op)++;
    }
    arr[i+1] = data;
}
int I_sort(int *arr,int size,int budget){
    int op = 0;
    for(int i = 0; i<size; i++){
        Insert(arr,i,budget,&op);
        if(op == budget){
            break;
        }
    }
    return op;
}

int main(){
    int size;
    int budget;
    scanf("%d",&size);
    scanf("%d",&budget);
    int *arr = (int *)malloc(sizeof(int)*size);
    for(int i = 0; i<size; i++){
        scanf("%d",&arr[i]);
    }
    int times = I_sort(arr,size,budget);
    printf("The array is ");
    for(int i = 0; i<size; i++){
        printf("%d ",arr[i]);
    }
    printf("after %d back-moves.",times);
    free(arr);
    return 0;
}