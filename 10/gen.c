#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_M 10000 // 假设M较小，以便演示
#define MAX_ID 1000000

int isUnique(int *array, int len, int value) {
    for (int i = 0; i < len; i++) {
        if (array[i] == value) {
            return 0;
        }
    }
    return 1;
}

int main() {
    srand(time(0)); 

    int N = 1; // N 固定为 1
    int M = rand() % MAX_M + 1; // 隨機生成 1 到 MAX_M 的 M
    printf("%d %d\n", N, M);

    int *job_ids = malloc(M * sizeof(int));
    int *priorities = malloc(M * sizeof(int));
    int job_id_count = 0;
    int priority_count = 0;

    for (int i = 0; i < M; i++) {
        int op_type = rand() % 2 + 1; // 随机选择操作类型 1 或 2，因为没有移动操作
        int job_id, priority, printer_id = 1; // 只有一个打印机，所以 printer_id 总是 1

        switch (op_type) {
            case 1:
                do {
                    job_id = rand() % MAX_ID + 1;
                } while (!isUnique(job_ids, job_id_count, job_id));
                job_ids[job_id_count++] = job_id;

                do {
                    priority = rand() % MAX_ID + 1;
                } while (!isUnique(priorities, priority_count, priority));
                priorities[priority_count++] = priority;

                printf("1 %d %d %d\n", job_id, priority, printer_id);
                break;
            case 2:
                printf("2 %d\n", printer_id);
                break;
        }
    }

    free(job_ids);
    free(priorities);
    return 0;
}