#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    long long point;
    struct Node *prev;
    struct Node *next;
}Node;

typedef struct properties{
    long long pow;
    long long id;
    long long rank;
    Node *head;
    Node *tail;
    Node *temp;
    long long time; 
    long long add;
}properties;

void Attack(long long id,properties **IdArr,properties **RkArr,long long *reward,long long n, long long p){
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
        Node *new = (Node *)malloc(sizeof(Node));
        new -> prev = NULL;
        new -> next = NULL;
        if ((IdArr[id]->head)->next == NULL){
            (IdArr[id]->head)->next = new;
            ((IdArr[id]->head)->next)->prev = (IdArr[id]->head);
            IdArr[id]->tail = new;
            new -> point = m;
        }
        else{
            (IdArr[id]->tail)->next = new;
            new ->prev = IdArr[id]->tail;
            new -> point = m + (IdArr[id]->tail)->point;
            IdArr[id]->tail = new;
        }
        IdArr[id]->time ++;
        if(IdArr[id]->time > p){
            IdArr[id]->temp = (IdArr[id]->temp)->next;
        }
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

void PowGain(long long id, properties **IdArr){
    if((IdArr[id]->tail) != NULL){
        printf("%lld",((IdArr[id]->tail)->point)-((IdArr[id]->temp)->point));
        printf("\n");
    }
    else{
        printf("%lld",0);
        printf("\n");
    }
}
int main(){
    long long n;
    long long t;
    long long m;
    scanf("%lld",&n);
    scanf("%lld",&t);
    scanf("%lld",&m);
    properties **IdArr = (properties **)malloc(sizeof(properties *)*n);
    properties **RkArr = (properties **)malloc(sizeof(properties *)*n);
    long long reward = 0;
    for(long long i = 0;i<n;i++){
        properties *new = (properties *)malloc(sizeof(properties));
        scanf("%lld",&new->pow);
        new->id = i;
        new->rank = i;
        new->head = (Node *)malloc(sizeof(Node));
        new->tail = NULL;
        new->temp = new->head;
        (new->head)->point = 0;
        (new->head)->next = NULL;
        new->time = 0;
        new->add = 0;
        IdArr[i] = new;
        RkArr[i] = new;
    }
    getchar();
    for(long long i = 0; i<t; i++){
        char line[1024];
        long long num1,num2,num3;
        long long result;
        if (fgets(line, sizeof(line), stdin)){
            result = sscanf(line, "%lld %lld %lld", &num1, &num2, &num3);
            if (result == 3){
                PowGain(num2-1, IdArr);
            }

            else if(result == 2){
                if(num1 == 1){
                    Attack(num2-1, IdArr, RkArr, &reward, n, m);
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
    for(int i = 0; i<n; i++){
        if(IdArr[i]->time != 0){
            Node *temp = (IdArr[i]->head)->next;
            printf("%d ",IdArr[i]->time);
            while(temp != NULL){
                printf("%lld ",(temp->point)-(temp->prev)->point);
                temp = temp->next;
            }
        }
        else 
            printf("0");
        printf("\n");
    }
}