#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n;
    scanf("%d",&n);

    double x1,y1,x2,y2,x3,y3;
    double vec,scal;
    double x;
    
    for (int i=0;i<n;i++){
        scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3);
        vec = fabs((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1));
        scal = (x2-x1)*(x3-x1) + (y2-y1)*(y3-y1);
        printf("%.20g\n", atan2(vec,scal)*180/PI);
    }
    return 0;
}
