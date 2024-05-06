#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long *Prefix(char* str, long long *arr, long long size);

long long *KMP(char *source, char *copy, long long *arr,long long m,long long *pla){
    long long n = strlen(source);
    
    long long k = -1;
    long long *s = (long long *)malloc(sizeof(long long)*m);

    for(int i = 0;i<m;i++){
        s[i] = 0;
    }
    for(int i = 0;i<n;i++){
        while(k>-1 && copy[k+1] != source[i]){
            k = arr[k];
        }
        if(copy[k+1]== source[i]){
            k++;
            s[k]++;
        }
        if(k+1== m){
            k = arr[k];
        }
    }
    for(int i = m-1;i>=0;i--){
        if(arr[i] != -1){
            s[arr[i]] = s[arr[i]] + s[i];
        }
        s[i] = s[i]*pla[i];
    }
    return s;
}

long long *Prefix(char* str, long long *arr, long long size){

    long long *pla = (long long *)malloc(sizeof(long long)*size);
    for(int i = 0;i<size;i++){
        arr[i] = -1;
        pla[i] = 1;
    }
    long long k = -1;
    for(int i = 1;i<size;i++){
        while(k>-1 && str[k+1] != str[i])
            k = arr[k];
        if(str[k+1] == str[i]){
            k++;
        }
        arr[i] = k;
        if(arr[i] != -1){
            pla[i] = pla[arr[i]]+1;
        }
    }
    return pla;
}

int main(){
    char *source = (char *)malloc(sizeof(char)*5000001);
    char *copy = (char *)malloc(sizeof(char)*5000001);

    scanf("%s",source);
    scanf("%s",copy);
    
    long long m = strlen(copy);
    long long *arr = (long long *)malloc(sizeof(long long)*m);
    long long *pla = Prefix(copy,arr,m);
    long long *s = KMP(source,copy,arr,m,pla);

    for(int i = 0;i<m;i++){
        printf("%lld",s[i]);
        printf("\n");
    }
}