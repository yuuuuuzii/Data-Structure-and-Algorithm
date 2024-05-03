#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long *Prefix(char* str);

long long KMP(char *source,char *copy){
    long long n = strlen(source);
    long long m = strlen(copy);
    long long *arr = Prefix(copy);

    long long k = -1;
    long long s = 0;
    for(int i = 0;i<n;i++){
        while(k>-1 && copy[k+1] != source[i]){
            k = arr[k];
        }
            
        if(copy[k+1]== source[i]){
            k++;
        }
            
        if(k+1== m){
            s++;
            k = arr[k];
        }
    }
    return s;
}

long long *Prefix(char* str){
    long long size = strlen(str);
    long long *arr = (long long *)malloc(sizeof(long long)*size);
    arr[0] = -1;
    long long k = -1;
    for(int i = 1;i<size;i++){
        while(k>-1 && str[k+1] != str[i])
            k = arr[k];
        if(str[k+1] == str[i])
            k++;
        arr[i] = k;
    }
    return arr;
}
char *substring(char *copy,long long n){
    char *arr = (char *)malloc(sizeof(char)*(n+1));
    strncpy(arr,copy,n);
    arr[n] = '\0';
    return arr;
}
int main(){
    char *source = (char *)malloc(sizeof(char)*5000001);
    char *copy = (char *)malloc(sizeof(char)*5000001);

    scanf("%s",source);
    scanf("%s",copy);
    
    long long m = strlen(copy);
    
    for(int i = 1;i<=m;i++){
        char *sub = substring(copy,i);

        long long *arr = Prefix(sub);
        long long s = KMP(source,sub);

        printf("%lld",s*(arr[i-1]+2));
        printf("\n");
        free(arr);
    }
}