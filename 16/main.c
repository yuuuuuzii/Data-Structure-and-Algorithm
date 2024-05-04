#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long long *Prefix(char* str,long long *arr);

long long *KMP(char *source, char *copy, long long *arr){
    long long n = strlen(source);
    long long m = strlen(copy);
    
    long long k = -1;
    long long *s = (long long *)malloc(sizeof(long long)*m);
    long long *diff = (long long *)malloc(sizeof(long long)*(m+1));
    for(int i = 0;i<m;i++){
       s[i] = 0;
       diff[i] = 0;
    }
    diff[m] = 0;
    for(int i = 0;i<n;i++){
        while(k>-1 && copy[k+1] != source[i]){
            k = arr[k];
        }
        if(copy[k+1]== source[i]){
            k++;
            if(k == 0)
                s[0]++;
            
            diff[k]++;
            diff[k+1]--;
            
        }
        if(k+1== m){
            k = arr[k];
            //0~k 皆要+1
            if(k != -1){
                s[0]++;
                diff[0]++;
                diff[k+1]--;
            }
        }
        if(i==n-1){
            while(k != -1){
                k = arr[k];
                if(k != -1){
                    s[0]++;
                    diff[0]++;
                    diff[k+1]--;
                }
            }
        }
    }
    for(int i = 1;i<m;i++){
        s[i] = s[i-1]+ diff[i];
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
            pla[i] = pla[i-1];
            if(str[i]==str[0]){
                pla[i]++;
            }
        }

        arr[i] = k;
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
    /*for(int i = 0;i<m;i++){
        printf("%lld ",arr[i]);
    }

    
    for(int i = 0;i<m;i++){
        printf("%lld ",s[i]);
    }
    printf("\n");
    for(int i = 0;i<m;i++){
        printf("%lld ",pla[i]);
    }
    printf("\n");*/
    for(int i = 0;i<m;i++){
        printf("%lld",s[i]*pla[i]);
        printf("\n");
    }
}