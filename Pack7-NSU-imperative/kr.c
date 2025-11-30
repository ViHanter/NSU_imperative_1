#include <stdio.h>

#define MAX_LENGTH 100000

typedef enum {
    PRINT,
    SORT,
    SEARCH,
    XOR
} commands;

commands choose_command(const char* str) {
    return str[0] == 'p' ? PRINT :
        (str[0] == 'x' ? XOR : 
            (str[1] == 'o' ? SORT : SEARCH));
}

void sort(int* nums, int n) {
    int buckets[MAX_LENGTH] = { 0 };
    for (int i = 0; i < n; i++) {
        buckets[nums[i]] += 1;
    } 

    int a = 0;

    for (int i = 0; i < n; i++) {
        while(!buckets[a])
            a++;
        nums[i] = a;
        buckets[a]--;
    }
}

int binarySearch(int *arr, int len, int target) {
    int l = 0;
    int r = len - 1;
    int i=-1;
    
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (arr[m] == target) {
            i = m;
            break;
        } else if (arr[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    
    if (i==-1 ) return -1;
    if (i==0) return 0;
    
    while(arr[i]==target) i--; 
    return i+1;
}

void print(int *arr, int len){
    for (int i=0;i<len;i++){
        if (i==len-1) {printf("%d",arr[i]); break;}
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int nums1[MAX_LENGTH];
    int nums2[MAX_LENGTH];

    int num=0,len=0;

    while (num!=-1){
        scanf("%d",&num);
        if (num==-1) break;
        nums1[len]=num;
        len++;
    }
    for (int i=0;i<len;i++){
        scanf("%d",&num);
        nums2[i]=num;
    }

    char command[8];
    while (scanf("%s",command)!=EOF){

        switch (choose_command(command))
        {
        case PRINT:
            print(nums1,len);
            print(nums2,len);
            break;
        
        case SORT:
            sort(nums1,len);
            sort(nums2,len);
            break;
        case SEARCH:
            scanf("%d",&num);
            if (binarySearch(nums1,len,num)!=-1){
                printf("%d %d\n",1,binarySearch(nums1,len,num)+1);
            } else if (binarySearch(nums2,len,num)!=-1){
                printf("%d %d\n",2,binarySearch(nums2,len,num)+1);
            } else printf("-1\n");
            break;
        }

    }



    return 0;
}