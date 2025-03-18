#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX 10
#define L_MAX 10
#define TI_MAX 10
#define PI_MAX 10

// Function to generate a random number within a range
long long rand_range(long long min, long long max) {
    return (rand() % (max - min + 1)) + min;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int N = rand_range(2, N_MAX);
    int M = rand_range(5, N - 1);
    int Q = rand_range(1, 10);
    printf("%d %d %d\n", N, M, Q);

    // Array to keep track of which nodes v have already been used as a child
    int *used_v = calloc(N, sizeof(int)); // Initialize all to 0

    for (int i = 0; i < M; i++) {
        int u, v;
        long long l;
        do {
            u = rand_range(0, N - 2); // u can be from 0 to N-2
            v = rand_range(1, N - 1); // v must not be 0 and must be unique
        } while (used_v[v] || u == v); // Ensure v is unique and not equal to u
        used_v[v] = 1; // Mark v as used
        l = rand_range(1, L_MAX);
        printf("%d %d %lld\n", u, v, l);
    }

    free(used_v); // Free the memory

    // Generate Q instructions
    for (int i = 0; i < Q; i++) {
        int instruction_type = rand_range(1, 5);
        switch (instruction_type) {
            case 1:
            case 2:
            case 4: {
                int v = rand_range(1, N - 1); // v must not be 0
                printf("%d %d\n", instruction_type, v);
                break;
            }
            case 3: {
                long long ti = rand_range(0, TI_MAX);
                printf("%d %lld\n", instruction_type, ti);
                break;
            }
            case 5: {
                long long pi = rand_range(0, PI_MAX);
                printf("%d %lld\n", instruction_type, pi);
                break;
            }
            // Type 6 instructions are not handled here. You can implement it if needed.
        }
    }

    return 0;
}