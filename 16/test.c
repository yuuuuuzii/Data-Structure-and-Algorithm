#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long *Prefix(char* str);

long long KMP(char *source, char *copy, long long *arr){
    long long n = strlen(source);
    long long m = strlen(copy);
    
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
            k = arr[k];
            //0~k 皆要+1
                s++;
        }
    }
    return s;
}

long long *Prefix(char* str){
    long long size = strlen(str);
    long long *arr = (long long *)malloc(sizeof(long long)*size);

    for(int i = 0;i<size;i++){
        arr[i] = -1;
    }
    long long k = -1;
    for(int i = 1;i<size;i++){//RE
        while(k>-1 && str[k+1] != str[i])
            k = arr[k];
        if(str[k+1] == str[i]){
            k++;
        }
        arr[i] = k;
    }
    return arr;
}
char *substring(char *copy,int start,long long n){
    char *arr = (char *)malloc(sizeof(char)*(n+1));
    strncpy(arr,copy+start,n);
    arr[n] = '\0';

    return arr;
}
long long pla(char *copy){
    long long m = strlen(copy);
    long long num = 0;
    for(int i = 0;i<m;i++){
        if(strcmp(substring(copy,0,i+1),substring(copy,m-i-1,i+1)) == 0){
            num++;
        }
    }
    return num;
}

int main(){
    char *source = (char *)malloc(sizeof(char)*5000001);
    char *copy = (char *)malloc(sizeof(char)*5000001);

    scanf("%s",source);
    scanf("%s",copy);
    
    long long m = strlen(copy);
    long long *arr = Prefix(copy);

    for(int i = 1;i<=m;i++){
        char *sub = substring(copy,0,i);
        printf("%lld",KMP(source,sub,arr)*pla(sub));
        printf("\n");
    }
}