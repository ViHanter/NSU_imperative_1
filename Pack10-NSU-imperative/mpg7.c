#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    int x;
    int y;
    double distance;
} Point;

int compare(const void* a, const void* b) {
    Point* pointA = (Point*)a;
    Point* pointB = (Point*)b;
    
    if (pointA->distance < pointB->distance) return -1;
    if (pointA->distance > pointB->distance) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int k, n = 0;
    scanf("%d", &k);
    
    Point* points = (Point*)malloc(1000000 * sizeof(Point));
    
    while (scanf("%d %d", &points[n].x, &points[n].y) == 2) {
        points[n].distance = points[n].x * points[n].x + points[n].y * points[n].y;
        n++;
    }
    
    qsort(points, n, sizeof(Point), compare);
    
    for (int i = 0; i < k && i < n; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }
    
    free(points);
    return 0;
}