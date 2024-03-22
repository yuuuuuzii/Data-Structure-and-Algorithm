#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    // 比较函数，用于qsort，从大到小排序
    return (*(int*)b - *(int*)a);
}

int main() {
    int N = 1000;
    int T = 50000;
    int M = 5000000;
    int powers[N]; // 存储生成的随机数

    // 用于生成随机数的种子
    srand(time(NULL));

    printf("%d %d %d\n", N, T, M);
    for(int i = 0; i < N; ++i) {
        powers[i] = rand() % 1000000000 + 1; // 生成1到10^9之间的随机数
    }

    // 使用qsort函数进行排序
    qsort(powers, N, sizeof(int), compare);

    // 打印排序后的结果
    for(int i = 0; i < N; ++i) {
        printf("%d ", powers[i]);
    }
    printf("\n");

    for(int i = 0; i < T; ++i) {
        int type = rand() % 4 + 1; // 随机选择一个事件类型(1到4)
        int id = rand() % N + 1; // 随机选择一个玩家ID(1到N)
        
        switch (type) {
            case 1: // Attack
                printf("1 %d\n", id);
                break;
            case 2: // Reward
                printf("2\n");
                break;
            case 3: // Query
                printf("3 %lld\n", (long long)rand() % 1000000000000000000LL + 1); // 生成1到10^18之间的随机数
                break;
            case 4: // PowGain
                printf("4 %d %d\n", id, M);
                break;
        }
    }

    return 0;
}





