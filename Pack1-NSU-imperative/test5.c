#include <stdio.h> 
 
int main(void) { 
    int n1,n2; 
    scanf("%d %d",&n1,&n2); 

    int res = n1/n2, ost = n1%n2; 
 
    if (ost != 0 && n1 < 0) res--; 
    printf("%d ", res);
    res = n1 / n2;

    if (ost != 0 && n1 > 0) res++; 
    printf("%d ", res);

    res = ost; 
    if (res < 0) res += n2; 
 
    printf("%d %d\n",n1/n2, res); 
    return 0; 
}