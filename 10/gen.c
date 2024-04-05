#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_N 5000
#define MAX_M 5000 // 假设M较小，以便演示
#define MAX_ID 1000000000

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

    int N = rand() % MAX_N + 1;
    int M = rand() % MAX_M + 1;
    printf("%d %d\n", N, M);

    int *job_ids = malloc(M * sizeof(int));
    int *priorities = malloc(M * sizeof(int));
    int job_id_count = 0;
    int priority_count = 0;

    for (int i = 0; i < M; i++) {
        int op_type = rand() % 3 + 1;
        int job_id, priority, printer_id, printer_id2;

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

                printer_id = rand() % N + 1;
                printf("1 %d %d %d\n", job_id, priority, printer_id);
                break;
            case 2:
                printer_id = rand() % N + 1;
                printf("2 %d\n", printer_id);
                break;
            case 3:
                printer_id = rand() % N + 1;
                do {
                    printer_id2 = rand() % N + 1;
                } while (printer_id == printer_id2);
                printf("3 %d %d\n", printer_id, printer_id2);
                break;
        }
    }

    free(job_ids);
    free(priorities);
    return 0;
}