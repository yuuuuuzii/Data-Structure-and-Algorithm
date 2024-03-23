#include <stdio.h>
#include <stdlib.h>
//我現在錯的測資大概剩10個TLE，DC群說那幾筆特定測資是測overflow，但我全部把int 改成long long 還是沒過
//我猜有兩種可能，第一種是哪裡運算沒改到long long，造成overflow，所以TLE，第二種是我哪裡執行太久(我猜可能是realloc 那邊)
typedef struct properties{
    long long pow; //該玩家的pow,id,rank
    long long id;
    long long rank;
    long long *arr; // attack 歷史紀錄的 array
    long long size; //現在開的attack 歷史紀錄的 array size
    long long add; //用來記錄現在被2(reward)幾次
    long long time; // 紀錄attack 的次數
}properties;

void Attack(long long id,properties **IdArr,properties **RkArr,long long *reward,long long n){
    if(IdArr[id]->rank > 0){
        //兩個while 迴圈先執行reward (可先看reward 函數的說明)
        while((RkArr[(IdArr[id]->rank)]->add) < (*reward)){//發動Attack 的玩家
            RkArr[(IdArr[id]->rank)]->pow = RkArr[(IdArr[id]->rank)]->pow + (long long)(n-IdArr[id]->rank-1);
            (RkArr[(IdArr[id]->rank)]->add)++;
        }
        while((RkArr[(IdArr[id]->rank)-1]->add) < (*reward)){//被attack 的玩家
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

        //如果一次開T的大小，會MLE，所以採用要超過時再將size*2，理論上分攤為O(1)? 這我不確定，我覺得可能是這裡很慢
        if(IdArr[id]->size-1 == IdArr[id]->time){
            IdArr[id]->size = 2*IdArr[id]->size; //可能的點
            IdArr[id]->arr = (long long *)realloc(IdArr[id]->arr, sizeof(long long)*IdArr[id]->size);
        }
        IdArr[id]->time++; //紀錄attack的次數
        IdArr[id]->arr[IdArr[id]->time] = m +IdArr[id]->arr[IdArr[id]->time-1] ;//紀錄前綴和，這樣可以一次取到所有attack 所得的和
    }
}
void Reward(long long *reward){
    (*reward)++;
    //因為不一定每個陣列元素都會用到，所以先不reward，只紀錄reward幾次，
    //因為Reward 只跟位子有關，所以等到 Attack 和 Query 時，才將reward 補回去，可以降低複雜度(從O(n)->O(1))
}
void Query(long long data, long long start, long long end, properties **RkArr, long long *reward, long long n){
    while((RkArr[0]->add) < (*reward)){//先reward 0的位子，來確認下面的if
            RkArr[0]->pow = RkArr[0]->pow + (long long)(n-1);
            (RkArr[0]->add)++;
    }
    if(data <= RkArr[0]->pow){
        while(start < end){//binary search 找到>=qi 的值
            long long m = (start+end+1)/2;

            while((RkArr[m]->add) < (*reward)){//到某個元素時，再reward 判斷
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
        //如果次數大於M，則相減前綴和(例如1 2 3 這個 數列，存到array 裡面變成 1 3 6 ，要取3則用 6-3得到)
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
        //初始化
        new->id = i;
        new->rank = i;
        new->arr = (long long *)malloc(sizeof(long long)*4096);
        new->arr[0] = 0;
        new->time = 0;
        new->size = 4096;
        new->add = 0;
        IdArr[i] = new;
        RkArr[i] = new;
    }
    getchar();
    for(long long i = 0; i<t; i++){
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
    return 0;
}