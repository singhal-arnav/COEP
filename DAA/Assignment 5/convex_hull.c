#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point *pts;
    int size;
} Hull;

int cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int compareX(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if(p1->x != p2->x)
    {
        return (p1->x > p2->x) - (p1->x < p2->x);
    }
    return (p1->y > p2->y) - (p1->y < p2->y);
}

Hull bruteHull(Point *points, int n) {
    Hull h;
    h.pts = (Point *)malloc(2 * n * sizeof(Point));
    h.size = 0;
    if(n == 0)
    {
        return h;
    }
    qsort(points, n, sizeof(Point), compareX);
    if(n < 3)
    {
        for(int i = 0; i < n; i++)
        {
            h.pts[h.size++] = points[i];
        }
        return h;
    }
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        while(k >= 2 && cross(h.pts[k - 2], h.pts[k - 1], points[i]) <= 0)
        {
            k--;
        }
        h.pts[k++] = points[i];
    }
    for(int i = n - 2, t = k + 1; i >= 0; i--)
    {
        while(k >= t && cross(h.pts[k - 2], h.pts[k - 1], points[i]) <= 0)
        {
            k--;
        }
        h.pts[k++] = points[i];
    }
    h.size = k - 1;
    return h;
}

int rightmost(Hull h) {
    int idx = 0;
    for(int i = 1; i < h.size; i++)
    {
        if(h.pts[i].x > h.pts[idx].x || (h.pts[i].x == h.pts[idx].x && h.pts[i].y > h.pts[idx].y))
        {
            idx = i;
        }
    }
    return idx;
}

int leftmost(Hull h) {
    int idx = 0;
    for(int i = 1; i < h.size; i++)
    {
        if(h.pts[i].x < h.pts[idx].x || (h.pts[i].x == h.pts[idx].x && h.pts[i].y < h.pts[idx].y))
        {
            idx = i;
        }
    }
    return idx;
}

Hull mergeHull(Hull left, Hull right) {
    int n1 = left.size;
    int n2 = right.size;
    int ri = rightmost(left);
    int li = leftmost(right);
    int upper_l = ri, upper_r = li;
    int done = 0;
    while(!done)
    {
        done = 1;
        while(cross(left.pts[upper_l], right.pts[upper_r], right.pts[(upper_r - 1 + n2) % n2]) > 0)
        {
            upper_r = (upper_r - 1 + n2) % n2;
            done = 0;
        }
        while(cross(right.pts[upper_r], left.pts[upper_l], left.pts[(upper_l + 1) % n1]) < 0)
        {
            upper_l = (upper_l + 1) % n1;
            done = 0;
        }
    }
    int lower_l = ri, lower_r = li;
    done = 0;
    while(!done)
    {
        done = 1;
        while(cross(left.pts[lower_l], right.pts[lower_r], right.pts[(lower_r + 1) % n2]) < 0)
        {
            lower_r = (lower_r + 1) % n2;
            done = 0;
        }
        while(cross(right.pts[lower_r], left.pts[lower_l], left.pts[(lower_l - 1 + n1) % n1]) > 0)
        {
            lower_l = (lower_l - 1 + n1) % n1;
            done = 0;
        }
    }
    Hull h;
    h.pts = (Point *)malloc((n1 + n2) * sizeof(Point));
    h.size = 0;
    int curr = upper_l;
    h.pts[h.size++] = left.pts[curr];
    while(curr != lower_l)
    {
        curr = (curr + 1) % n1;
        h.pts[h.size++] = left.pts[curr];
    }
    curr = lower_r;
    h.pts[h.size++] = right.pts[curr];
    while(curr != upper_r)
    {
        curr = (curr + 1) % n2;
        h.pts[h.size++] = right.pts[curr];
    }
    free(left.pts);
    free(right.pts);
    return h;
}

Hull divideHull(Point *points, int n) {
    if(n <= 5)
    {
        return bruteHull(points, n);
    }
    int mid = n / 2;
    Hull leftHull = divideHull(points, mid);
    Hull rightHull = divideHull(points + mid, n - mid);
    return mergeHull(leftHull, rightHull);
}

int main() {
    int n;
    printf("Enter number of points: ");
    if(scanf("%d", &n) != 1)
    {
        return 0;
    }
    Point *points = (Point *)malloc(n * sizeof(Point));
    printf("Enter the coordinates for %d points (x y):\n", n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    qsort(points, n, sizeof(Point), compareX);
    Hull result = divideHull(points, n);
    printf("\nConvex Hull Points:\n");
    for(int i = 0; i < result.size; i++)
    {
        printf("(%d, %d)\n", result.pts[i].x, result.pts[i].y);
    }
    free(result.pts);
    free(points);
    return 0;
}
