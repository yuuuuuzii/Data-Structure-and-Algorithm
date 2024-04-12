#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void push(char *arr,char data,int *top){
    (*top)++;
    arr[*top] = data;
}
void push1(long long *arr,long long data,int *top){
    (*top)++;
    arr[*top] = data;
}

char pop(char *arr,int *top){
    char data  = arr[*top];
    (*top)--;
    return data;
}
long long pop1(long long *arr,int *top){
    long long data  = arr[*top];
    (*top)--;
    return data;
}
char peep(char *arr,int *top){
    return arr[*top];
}

int table(char op){
    switch(op){
        case '(':return 0;
        case '+':case '-':return 1;
        case '*':case '/':case '%':return 2;
    }
}
void ItoP(char *Infix,char *arr,int *top,char *result,int *top2){
    for(int i = 0;Infix[i]!= '\0';i++){
        if(isdigit(Infix[i])){
            push(result,Infix[i],top2);
            printf("%c",Infix[i]);
        }
        else{
            push(result,'_',top2);
            if(Infix[i] == '('){//OK
                push(arr,Infix[i],top);
            }
            else if(Infix[i] == ')'){
                while((*top) > -1 && peep(arr,top) != '('){
                    push(result,peep(arr,top),top2);
                    printf("%c",pop(arr,top));
                }
                pop(arr,top);
            }
            else{
                while((*top) > -1 && table(peep(arr,top))>=table(Infix[i])){
                    push(result,peep(arr,top),top2);
                    printf("%c",pop(arr,top));
                }
                push(arr,Infix[i],top);
            }
        }
    }
    while((*top) > -1){
        push(result,'_',top2);
        push(result,peep(arr,top),top2);
        printf("%c",pop(arr,top));
    }
    push(result,'\0',top2);
    /*int i = 0;
    printf("\n");
    while(result[i]!='\0'){
        printf("%c",result[i]);
        i++;
    }*/
}
long long eval(char *result,int *top2, long long *cal, int *top3){
    int i = 0;
    char temp[4000];
    int top4 = -1;
    while(result[i] != '\0'){
        if(isdigit(result[i])){
            push(temp,result[i],&top4);
        }
        else if(result[i] == '_'){
            if(top4 > -1){
                push(temp,'\0',&top4);
                push1(cal,(unsigned long long)strtoul(temp, NULL, 10),top3);
                top4 = -1;
            }
        }
        else{
            long long n1 = pop1(cal,top3);
            //printf("%lld",n2);
            long long n2 = pop1(cal,top3);
            //printf("%lld",n1);
            switch(result[i]){
                case '+': push1(cal,n2+n1,top3);break;
                case '-': push1(cal,n2-n1,top3);break;
                case '*': push1(cal,n2*n1,top3);break;
                case '/': push1(cal,n2/n1,top3);break;
                case '%': push1(cal,n2%n1,top3);break;
            }
        }
        i++;
    }
    return pop1(cal,top3);
}
int main(){
    for(int i = 0;i<3; i++){
        char str[4000];
        char arr[4000];
        char result[8000];
        long long cal[4000];
        int top = -1;
        int top2 = -1;
        int top3 = -1;
        scanf("%s",str);
        ItoP(str,arr,&top, result,&top2);
        printf("=%lld",eval(result, &top2, cal, &top3));
        printf("\n");
    }
}