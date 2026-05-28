#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void binary_search(int *,int,int,int *, int *);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N,n,num;
    scanf("%d",&N);
    int *buff = (int*)malloc(N * sizeof(int));
    for (int i=0;i<N;i++) {scanf("%d",&buff[i]);}
    
    scanf("%d",&n);
    for (int i=0;i<n;i++) {
        scanf("%d",&num);
        int idx, dist;
        binary_search(buff, N, num, &idx, &dist);
        printf("%d %d\n", idx, dist);
    }

    return 0;
}

void binary_search(int *arr, int len, int target, int *index, int *distance) {
    int left = 0, right = len - 1;
    int i = -1;
    
    // Сначала ищем точное совпадение или позицию для вставки
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            // Нашли точное совпадение
            i = mid;
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (i!=-1){
        while (i>=0 && arr[i]==target) i--;
        *index = i+1;
        *distance = 0;
        return;
    }
    
    // После цикла:
    // left указывает на последний элемент < target (или -1 если все >= target)
    // right указывает на первый элемент >= target (или len если все < target)
    
    // Рассматриваем двух кандидатов: right и left
    int candidate1 = -1, candidate2 = -1;
    int dist1 = 2000000000, dist2 = 2000000000; // Большое начальное значение
    
    if (right >= 0) {
        candidate1 = right;
        dist1 = abs(arr[right] - target);
    }
    
    if (left < len) {
        candidate2 = left;
        dist2 = abs(arr[left] - target);
    }
    
    // Выбираем лучшего кандидата
    if (candidate1 == -1) {
        *index = candidate2;
        *distance = dist2;
    } else if (candidate2 == -1) {
        *index = candidate1;
        *distance = dist1;
    } else if (dist1 < dist2) {
        *index = candidate1;
        *distance = dist1;
    } else if (dist2 < dist1) {
        *index = candidate2;
        *distance = dist2;
    } else {
        // Если расстояния равны, выбираем любой индекс (по условию можно любой)
        *index = candidate2;
        *distance = dist1;
    }
}