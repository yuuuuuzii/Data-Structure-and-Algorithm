#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long *Prefix(char* str,long long *arr);

long long *KMP(char *source, char *copy, long long *arr){
    long long n = strlen(source);
    long long m = strlen(copy);
    
    long long k = -1;
    long long *s = (long long *)malloc(sizeof(long long)*m);
    long long *sum = (long long *)malloc(sizeof(long long)*m);
    for(int i = 0;i<m;i++){
        s[i] = 0;
        sum[i] = 0;
    }
    for(int i = 0;i<n;i++){
        while(k>-1 && copy[k+1] != source[i]){
            k = arr[k];
        }
        if(copy[k+1]== source[i]){
            k++;
            s[k]++;

            /*long long o = arr[k];
            if(o!= -1){
                sum[o]++;
            }*/
        }
        if(k+1== m){
            k = arr[k];
        }
    }
    for(int i = m-1;i>=0;i--){
        if(arr[i] != -1){
            s[arr[i]] = s[arr[i]] + s[i];
        }

    }
    return s;
}


long long *Prefix(char* str, long long *arr){
    long long size = strlen(str);
    long long *pla = (long long *)malloc(sizeof(long long)*size);

    for(int i = 0;i<size;i++){
        arr[i] = -1;
        pla[i] = 1;
    }
    long long k = -1;
    for(int i = 1;i<size;i++){//RE
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
    long long *pla = Prefix(copy,arr);
    long long *s = KMP(source,copy,arr);

    for(int i = 0;i<m;i++){
        printf("%lld",s[i]*pla[i]);
        printf("\n");
    }
}