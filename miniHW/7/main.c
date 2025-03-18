#include <stdio.h>
#include <stdlib.h>

int BinSearch(int *arr, int key, int l, int r){
    printf("Searching %d in range [%d, %d].",key,l+1,r+1);
    printf("\n");
    while(l <= r){
        int m;
        m = (l+r)/2;
        if (arr[m] == key){
            return m;
        } 
        else if (arr[m] > key){
            r = m-1;
            printf("Searching %d in range [%d, %d].",key,l+1,r+1);
            printf("\n");
        }
        else if (arr[m] < key){
            l = m+1;
            printf("Searching %d in range [%d, %d].",key,l+1,r+1);
            printf("\n");
        }
    }
    return -1;
}

int main(){
    int n;
    int key;
    scanf("%d",&n);
    scanf("%d", &key);
    int *arr = (int *)malloc((sizeof(int))*n);
    for (int i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }
    int num = BinSearch(arr, key, 0, n-1);
    if(num != -1)
        printf("Found at index %d.",num+1);
    else
        printf("Not found.");
}