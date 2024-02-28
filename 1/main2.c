#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);
void zigzag(int *arr, int start, int end, int **result, int *count);
int compare(const void *a, const void *b);
int CompareArr(int *arr,int **result,int end,int *count);
int main() {
    int num;
    scanf("%d", &num);
    int *arr = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &arr[i]);
    }

    qsort(arr, num, sizeof(int), compare);

    int **result = (int **)malloc(sizeof(int *) * 20); 
    int count = 0;
    zigzag(arr, 0, num - 1, result, &count);
    printf("%d",count);
    printf("\n");
    for (int i = 0; i < count; i++) {
        for (int j = 0; result[i][j] != -1; j++) {
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

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
int CompareArr(int *arr,int **result,int end,int *count){
    for(int i = 0; i <= end; i++){
        if(*count == 0 || result[*count-1][i] != arr[i]){
            return 0;
        } //不等於assign 為 0;
    }
    return 1;
}
void zigzag(int *arr, int start, int end, int **result, int *count) {
    if (start == end && ((arr[start] - arr[start - 1]) * (arr[start - 1] - arr[start - 2])) < 0) {
        if(CompareArr(arr,result,end,count) == 0){
            result[*count] = (int *)malloc(sizeof(int) * (end + 1));
            for (int i = 0; i <= end; i++) {
                result[*count][i] = arr[i];
            }
            result[*count][end + 1] = -1; // Marking end of the array
            (*count)++;
        }
    } else {
        for (int i = start; i <= end; i++) {
            swap(&arr[start], &arr[i]);
            if (end < 2) {
                // Allocate memory for storing the result
                result[*count] = (int *)malloc(sizeof(int) * (end + 1));
                for (int j = 0; j <= end; j++) {
                    result[*count][j] = arr[j];
                }
                result[*count][end + 1] = -1; // Marking end of the array
                (*count)++;
            } else if (start <= 2 || ((arr[start] - arr[start - 1]) * (arr[start - 1] - arr[start - 2])) < 0) {
                zigzag(arr, start + 1, end, result, count);
            }
            swap(&arr[start], &arr[i]);
        }
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}