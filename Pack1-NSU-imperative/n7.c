#include <stdio.h>
#include <math.h>

int main(void) {
    int f_app, s_app, pod, flo, flocount;
    int app_count,res_pod,res_flo;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    scanf("%d",&f_app);
    scanf("%d %d %d %d",&s_app,&pod,&flo,&flocount);

    app_count = ceil( (s_app*1.00) / (flocount*(pod-1) + flo ));
    res_pod = ceil( (floor((f_app*1.00) / app_count) * 1.00) / flocount);
    res_flo = (floor((f_app*1.00) / app_count) * 1.00) - flocount*(res_pod-1);



    printf("%d %d",res_pod,res_flo);
    return 0;
}