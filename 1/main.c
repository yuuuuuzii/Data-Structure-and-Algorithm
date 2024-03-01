#include <stdio.h>
#include <stdlib.h>

void change(int *arr,int start, int i);
void Remake(int*arr,int start,int i);
void zigzag(int *arr, int start, int end, int **result, int *count);
int compare(const void *a, const void *b);
//int compare1(const void *a, const void *b);
int main() {
    int num;
    scanf("%d", &num);
    int *arr = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, num, sizeof(int), compare);
    int **result = (int **)malloc(sizeof(int *) * 200000); 
    int count = 0;
    zigzag(arr, 0, num - 1, result, &count);
    printf("%d",count);
    printf("\n");
    //qsort(result, count, sizeof(int *), compare1);
    for (int i = 0; i < count; i++) {
        for (int j = 0; result[i][j] != -1000000001; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    free(arr);
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
} 

void change(int *arr,int start, int i) {
    int temp = arr[i];
    for(int j = i; j > start;j--){
        arr[j] = arr[j-1];
    }
    arr[start] = temp;
}
void Remake(int*arr,int start,int i){
    int temp = arr[start];
    for(int j = start; j < i ;j++){
        arr[j] = arr[j+1];
    }
    arr[i] = temp;
}
void zigzag(int *arr, int start, int end, int **result, int *count) {
    if (start == end && ((long long)((long long)arr[start] - (long long)arr[start - 1]) * (long long)((long long)arr[start - 1] - (long long)arr[start - 2])) < 0) {
        int tag = 1;
        // 检查是否已经存在相同的数组
        for (int k = 0; k < *count; k++) {
            int same = 1;
            for (int i = 0; i <= end; i++) {
                if (result[k][i] != arr[i]) {
                    same = 0;
                    break;
                }
            }
            if (same) {
                tag = 0;
                break;
            }
        }
        if (tag) {
            result[*count] = (int *)malloc(sizeof(int) * (end + 1));
            for (int i = 0; i <= end; i++) {
                result[*count][i] = arr[i];
            }
            result[*count][end + 1] = -1000000001;
            (*count)++;
        }
    } else {
        for (int i = start; i <= end; i++) {
            change(arr,start, i);
            if (end < 2) {
                // 检查是否已经存在相同的数组
                int tag = 1;
                for (int k = 0; k < *count; k++) {
                    int same = 1;
                    for (int j = 0; j <= end; j++) {
                        if (result[k][j] != arr[j]) {
                            same = 0;
                            break;
                        }
                    }
                    if (same) {
                        tag = 0;
                        break;
                    }
                }
                if (tag) {
                    result[*count] = (int *)malloc(sizeof(int) * (end + 1));
                    for (int j = 0; j <= end; j++) {
                        result[*count][j] = arr[j];
                    }
                    result[*count][end + 1] = -1000000001;
                    (*count)++;
                }
            } else if (start < 2 || ((long long)((long long)arr[start] - (long long)arr[start - 1]) * (long long)((long long)arr[start - 1] - (long long)arr[start - 2])) < 0) {
                zigzag(arr, start + 1, end, result, count);
            }
            Remake(arr,start,i);
        }
    }
}

