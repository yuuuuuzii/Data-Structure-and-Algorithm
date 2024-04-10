#include <stdio.h>
#include <stdlib.h>

void Swap(int *arr,int i,int j);

void Increase(int *arr,int i,int key){
    arr[i] = key;
    while(i > 1 && (arr[i/2] < arr[i])){
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
    int arr[size+1];//開大一格
    for(int i = 1;i<=size;i++){
        int num;
        scanf("%d",&num);
        Increase(arr,i,num);
    }
    for(int i = 1;i<=size;i++){
        printf("%d ",arr[i]);
    }
}