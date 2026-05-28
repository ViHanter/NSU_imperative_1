#include <stdio.h>
#include <math.h>

double f(double t,
         double l,
         double cx[4],
         double cy[4],
         double cz[4]) {

    double dt = t - l;

    double dx = cx[1] + 2*cx[2]*dt + 3*cx[3]*dt*dt;
    double dy = cy[1] + 2*cy[2]*dt + 3*cy[3]*dt*dt;
    double dz = cz[1] + 2*cz[2]*dt + 3*cz[3]*dt*dt;

    return sqrt(dx*dx + dy*dy + dz*dz);
}

double simpson(double l, double r,
               double cx[4],
               double cy[4],
               double cz[4]) {

    int n = 100;
    double h = (r - l) / n;

    double sum = f(l, l, cx, cy, cz) + f(r, l, cx, cy, cz);

    for (int i = 1; i < n; i++) {
        double t = l + i * h;

        if (i % 2 == 0)
            sum += 2 * f(t, l, cx, cy, cz);
        else
            sum += 4 * f(t, l, cx, cy, cz);
    }

    return sum * h / 3.0;
}
int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    int N;
    fscanf(in, "%d", &N);

    double total = 0.0;

    for (int i = 0; i < N; i++) {
        double l, r;
        fscanf(in, "%lf %lf", &l, &r);

        double cx[4], cy[4], cz[4];

        for (int j = 0; j < 4; j++) fscanf(in, "%lf", &cx[j]);
        for (int j = 0; j < 4; j++) fscanf(in, "%lf", &cy[j]);
        for (int j = 0; j < 4; j++) fscanf(in, "%lf", &cz[j]);

        total += simpson(l, r, cx, cy, cz);
    }

    fprintf(out, "%.15lf\n", total);

    return 0;
}