#include <stdio.h>
#include <string.h>

typedef struct Label_s {
    char name[16];
    int age;
} Label;

typedef struct NameStats_s {
    int cntTotal;
    int cntLong;
} NameStats;

typedef struct AgeStats_s {
    int cntTotal;
    int cntAdults;
    int cntKids;
} AgeStats;

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    Label labels[1000];
    NameStats nStats;
    AgeStats aStats;

    int n;
    scanf("%d",&n);

    for (int i=0;i<n;i++){
        scanf("%s %d let", labels[i].name,&labels[i].age);
    }
    calcStats(labels,n,&nStats,&aStats);
    printf("names: total = %d\nnames: long = %d\n",nStats.cntTotal,nStats.cntLong);
    printf("ages: total = %d\nages: adult = %d\nages: kid = %d",aStats.cntTotal,aStats.cntAdults,aStats.cntKids);
    
    return 0;
}

void calcStats(const Label *arr, int cnt, NameStats *oNames, AgeStats *oAges){
    int cntAdults=0;
    int cntKids=0;
    int cntLong=0;

    oNames->cntTotal = cnt;
    oAges->cntTotal = cnt;
    for (int i=0;i<cnt;i++){
        if (strlen(arr[i].name)>10) cntLong++;
        if (arr[i].age>=18) cntAdults++;
        if (arr[i].age<14) cntKids++;
    }
    oAges->cntAdults = cntAdults;
    oAges->cntKids = cntKids;
    oNames->cntLong = cntLong;
}