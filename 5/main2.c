include <stdio.h>
#include <stdlib.h>

typedef struct properties{
    long long pow;
    long long id;
    long long rank;
    long long *arr;
    long long size;
    long long add;
    long long time;
}properties;

void Attack(long long id,properties **IdArr,properties **RkArr,long long *reward,long long n){
    if(IdArr[id]->rank > 0){
        while((RkArr[(IdArr[id]->rank)]->add) < (*reward)){
            RkArr[(IdArr[id]->rank)]->pow = RkArr[(IdArr[id]->rank)]->pow + (long long)(n-IdArr[id]->rank-1);
            (RkArr[(IdArr[id]->rank)]->add)++;
        }
        while((RkArr[(IdArr[id]->rank)-1]->add) < (*reward)){
            RkArr[(IdArr[id]->rank)-1]->pow = RkArr[(IdArr[id]->rank)-1]->pow + (long long)(n-IdArr[id]->rank);
            (RkArr[(IdArr[id]->rank)-1]->add)++;
        }
        long long m = RkArr[(IdArr[id]->rank)-1]->pow - RkArr[(IdArr[id]->rank)]->pow; //紀錄差值
        //更新rank arr (執行swap)
        properties *temp = RkArr[(IdArr[id]->rank)-1];
        RkArr[(IdArr[id]->rank)-1] = RkArr[(IdArr[id]->rank)];
        RkArr[(IdArr[id]->rank)] = temp;
        //更新pow
        RkArr[(IdArr[id]->rank)-1]->pow = RkArr[(IdArr[id]->rank)]->pow ;
        //更新rank
        (RkArr[(IdArr[id]->rank)]->rank)++;
        (RkArr[(IdArr[id]->rank)-1]->rank)--;
        //紀錄更新
        if(IdArr[id]->size-1 == IdArr[id]->time){
            IdArr[id]->size = 2*IdArr[id]->size; //可能的點
            IdArr[id]->arr = (long long *)realloc(IdArr[id]->arr, sizeof(long long)*IdArr[id]->size);
        }
        IdArr[id]->time++;
        IdArr[id]->arr[IdArr[id]->time] = m +IdArr[id]->arr[IdArr[id]->time-1] ;
    }
}
void Reward(long long *reward){
    (*reward)++;
}
void Query(long long data, long long start, long long end, properties **RkArr, long long *reward, long long n){
    while((RkArr[0]->add) < (*reward)){
            RkArr[0]->pow = RkArr[0]->pow + (long long)(n-1);
            (RkArr[0]->add)++;
    } 
    if(data <= RkArr[0]->pow){
        while(start < end){
            long long m = (start+end+1)/2;
            while((RkArr[m]->add) < (*reward)){
                RkArr[m]->pow = RkArr[m]->pow + (long long)(n-m-1);
                (RkArr[m]->add)++;
                }
            if(RkArr[m]->pow < data){
                end = m-1;
            }
            else{
                start = m;
            }
        }
    printf("%lld %lld", start+1, (RkArr[start]->id)+1);
    printf("\n");
    }
    else{
        printf("0 0");
        printf("\n");
    }

}
void PowGain(long long id, properties **IdArr, long long m , long long M){
    if(m > M){
        m = M;
    }
    if((IdArr[id]->time) > m){
        printf("%lld", IdArr[id]->arr[IdArr[id]->time]-IdArr[id]->arr[IdArr[id]->time-m]);
        printf("\n");
    }
    else{
        printf("%lld",IdArr[id]->arr[IdArr[id]->time]);
        printf("\n");
    }
}
int main(){
    long long n;
    long long t;
    long long M;
    scanf("%lld",&n);
    scanf("%lld",&t);
    scanf("%lld",&M);
    properties **IdArr = (properties **)malloc(sizeof(properties *)*n);
    properties **RkArr = (properties **)malloc(sizeof(properties *)*n);
    long long reward = 0;
    for(long long i = 0;i<n;i++){
        properties *new = (properties *)malloc(sizeof(properties));
        scanf("%lld",&new->pow);
        new->id = i;
        new->rank = i;
     
        new->arr = (long long *)malloc(sizeof(long long));
        new->arr[0] = 0;
        new->time = 0;
        new->size = 1;
        new->add = 0;
        IdArr[i] = new;
        RkArr[i] = new;
    }
    getchar();
    for(int i = 0; i<t; i++){
        char line[1024];
        long long num1;
        long long num2;
        long long num3;
        int result;
        if (fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%lld %lld %lld", &num1, &num2, &num3);
            if (result == 3){
                PowGain(num2-1, IdArr, num3, M);
            }
            else if(result == 2){
                if(num1 == 1){
                    Attack(num2-1, IdArr, RkArr, &reward, n);
                }
                else
                    Query(num2, 0, n-1, RkArr, &reward, n);
            }
            else{
                Reward(&reward);
            }
        }
    }
    printf("\n");
    for(long long i = 0; i<n; i++){
        if(IdArr[i]->time != 0){
            printf("%lld ",IdArr[i]->time);
                for(long long j = 1; j<(IdArr[i]->time+1); j++)
                    printf("%lld ",(long long)IdArr[i]->arr[j]-(long long)IdArr[i]->arr[j-1]);
            }
        else 
            printf("0");
        printf("\n");
    }
}
