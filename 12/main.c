#include <stdio.h>
#include <stdlib.h>
void Increase(int *arr,int i,int key);
void Swap(int *arr,int i,int j);

void Insert(int *arr,int key,int i){
    arr[i+1] = 0;
    Increase(arr,i,key);
}

void Increase(int *arr,int i,int key){
    arr[i] = key;
    while(i>0 && arr[i/2]<arr[i]){
        Swap(arr,i/2,i);
        i = i/2;
    }
}
void Swap(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
int main(){
    int size;
    scanf("%d",&size);
    int arr[size+1];
    for(int i = 0;i<size;i++){
        int num;
        scanf("%d",&num);
        Insert(arr,num,i);
    }
    for(int i = 0;i<size;i++){
        printf("%d ",arr[i]);
    }
}