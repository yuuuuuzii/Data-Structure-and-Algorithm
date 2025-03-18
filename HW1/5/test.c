#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    // 比较函数，用于qsort，从大到小排序
    return (*(long long*)b - *(long long*)a);
}

int main() {
    long long N = 100000;
    long long T = 500000;
    long long M = 500000;
    long long powers[N]; // 存储生成的随机数

    // 用于生成随机数的种子
    srand(time(NULL));

    printf("%d %d %d\n", N, T, M);
    for(long long i = 0; i < N; ++i) {
        powers[i] = rand() % 1000000000 + 1; // 生成1到10^9之间的随机数
    }

    // 使用qsort函数进行排序
    qsort(powers, N, sizeof(long long), compare);

    // 打印排序后的结果
    for(int i = 0; i < N; ++i) {
        printf("%lld ", powers[i]);
    }
    printf("\n");

    for(int i = 0; i < T; ++i) {
        long long type = rand() % 4 + 1; // 随机选择一个事件类型(1到4)
        long long id = rand() % N + 1; // 随机选择一个玩家ID(1到N)
        
        switch (type) {
            case 1: // Attack
                printf("1 %lld\n", id);
                break;
            case 2: // Reward
                printf("2\n");
                break;
            case 3: // Query
                printf("3 %lld\n", (long long)rand() % 1000000000000000000LL + 1); // 生成1到10^18之间的随机数
                break;
            case 4: // PowGain
                printf("4 %lld %lld\n", id, M);
                break;
        }
    }

    return 0;
}





