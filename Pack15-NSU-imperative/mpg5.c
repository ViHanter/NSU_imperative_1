#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x, y;
} Point;

long long orientation(Point p, Point q, Point r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

long long dist_sq(Point p, Point q) {
    long long dx = p.x - q.x;
    long long dy = p.y - q.y;
    return dx * dx + dy * dy;
}

int find_start_point(Point* points, int n) {
    int start = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[start].x || 
            (points[i].x == points[start].x && points[i].y < points[start].y)) {
            start = i;
        }
    }
    return start;
}

int convex_hull(Point* points, int n, Point* hull) {
    if (n < 3) return 0;
    
    int start = find_start_point(points, n);
    
    int hull_size = 0;
    int current = start;
    
    do {
        hull[hull_size++] = points[current];

        int next = (current + 1) % n;
        for (int i = 0; i < n; i++) {
            if (i == current) continue;
            
            long long orient = orientation(points[current], points[i], points[next]);
            
            if (orient > 0) {
                next = i;
            } else if (orient == 0) {
                long long dist_to_i = dist_sq(points[current], points[i]);
                long long dist_to_next = dist_sq(points[current], points[next]);
                
                if (dist_to_i > dist_to_next) {
                    next = i;
                }
            }
        }
        
        current = next;
        
    } while (current != start);
    
    return hull_size;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Point* points = (Point*)malloc(n * sizeof(Point));
    Point* hull = (Point*)malloc(n * sizeof(Point));
    
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }
    
    int hull_size = convex_hull(points, n, hull);

    printf("%d\n", hull_size);
    for (int i = 0; i < hull_size; i++) {
        printf("%lld %lld\n", hull[i].x, hull[i].y);
    }
    
    free(points);
    free(hull);
    
    return 0;
}