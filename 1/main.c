#include <stdio.h>
#include <stdlib.h>

void change(int *arr,int start, int i);
void Remake(int*arr,int start,int i);
void zigzag(int *arr, int start, int end, int **result, int *count);
int compare(const void *a, const void *b);
//主要複雜度可能來自進行recursion前後，移動陣列所花的時間
int main() {
    int num;
    scanf("%d", &num);
    int *arr = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, num, sizeof(int), compare); 
    int **result = (int **)malloc(sizeof(int *) * 200002); //用來存所有可能的結果
    int count = 0;
    zigzag(arr, 0, num - 1, result, &count);
    printf("%d",count); //印出所有可能的數量
    printf("\n");
    for (int i = 0; i < count; i++) {
        for (int j = 0; result[i][j] != -1000000001; j++) {
            printf("%d ", result[i][j]); //印出所有組合
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
    return (int)(*(long long *)a - *(long long*)b);
} 

void change(int *arr,int start, int i) { //把陣列中的每個元素，輪流移至陣列首
    int temp = arr[i];
    for(int j = i; j > start;j--){
        arr[j] = arr[j-1];
    }
    arr[start] = temp;
}
void Remake(int*arr,int start,int i){ //回復成原本陣列
    int temp = arr[start];
    for(int j = start; j < i ;j++){
        arr[j] = arr[j+1];
    }
    arr[i] = temp;
}
void zigzag(int *arr, int start, int end, int **result, int *count) {
    //如果成功跑到最後面，則判斷最後一個元素是否也符合zigzag
    if (start == end && ((long long)((long long)arr[start] - (long long)arr[start - 1]) * (long long)((long long)arr[start - 1] - (long long)arr[start - 2])) < 0) {
            result[*count] = (int *)malloc(sizeof(int) * (end + 1));
            for (int i = 0; i <= end; i++) {
                result[*count][i] = arr[i];
            }
            result[*count][end + 1] = -1000000001;//因為a[n]的範圍為10^9，所以用這個數字來判斷陣列的最末端
            (*count)++;
    } else {
        for (int i = start; i <= end; i++) {
            if( i == 0 ||(arr[i] != arr[i-1])){
                change(arr,start, i);//開始recursion，輪流當頭
                if (end < 2) {//如果陣列數量小於2，則直接存入
                        result[*count] = (int *)malloc(sizeof(int) * (end + 1));
                        for (int j = 0; j <= end; j++) {
                            result[*count][j] = arr[j];
                        }
                        result[*count][end + 1] = -1000000001;
                        (*count)++;
                } else if (start < 2 || ((long long)((long long)arr[start] - (long long)arr[start - 1]) * (long long)((long long)arr[start - 1] - (long long)arr[start - 2]) < 0)) {
                    zigzag(arr, start + 1, end, result, count);//如果條件符合，才會進入recursion，避免印出不可能的結果
                }
                Remake(arr,start,i);//回復陣列
            }
        }
    }
}

