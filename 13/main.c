#include <stdio.h>
#include <stdlib.h>
int partition(int *arr,int l,int r,int budget, int *time);
void qqsort(int *arr,int l,int r,int budget,int *time){
    if(l<r){
        int m = partition(arr,l,r,budget,time);
        qqsort(arr,l,m-1,budget,time);
        qqsort(arr,m+1,r,budget,time);
    }
}

void swap(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int *arr,int l,int r,int budget, int *time){
    int pivot = arr[l];
    int i = l+1;
    int j = r;
    while(i<j){
        while(i<=r && arr[i]<=pivot)
            i++;
        while(j>=l && arr[j]>pivot)
            j--;
        if (i>=j)
            break;
        if(budget> (*time)){
            swap(arr,i,j);
            (*time)++;
        }
        else
            break;
    }
    if (l<j && arr[l]>arr[j] && budget>(*time)){
        swap(arr,l,j);
        (*time)++;
    }
    return j;
}

int main(){
    int size,budget;
    int time = 0;
    scanf("%d",&size);
    scanf("%d",&budget);
    int arr[size];
    for(int i = 0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    qqsort(arr,0,size-1,budget,&time);
    printf("The array is ");
    for(int i = 0;i<size;i++){
        printf("%d ",arr[i]);
    }
    printf("after %d swaps.",time);
}