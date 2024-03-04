#include <stdio.h>
#include <stdlib.h>
int GetMin(int *arr,int l,int r){
    int m = l;
    for(int i =l+1;i<=r; i++){
        if(arr[m]>arr[i])
            m = i;
    }
    return m;
}
void Swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
int S_sort(int *arr,int size,int budget){
    int op = 0;
    for(int i = 0; op<budget; i++){
        int m = GetMin(arr,i,size-1);
        if(i != m){
            Swap(&arr[i],&arr[m]);
            op++;
        }
        if(i == size-1){
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
    int times = S_sort(arr,size,budget);
    printf("The array is ");
    for(int i = 0; i<size; i++){
        printf("%d ",arr[i]);
    }
    printf("after %d swaps.",times);
    free(arr);
    return 0;
}