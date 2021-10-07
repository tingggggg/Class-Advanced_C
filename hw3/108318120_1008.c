#include <stdio.h>
#include <stdlib.h>

typedef struct num_list{
    int counts;
    int *pList;
}tNumList;

void bubbleSort(tNumList *list);

void merge(tNumList *list1, tNumList *list2);

int main(){
    int cnt_1 = 0, cnt_2 = 0;
    printf("Please enter how many numbers in list1: ");
    scanf("%d", &cnt_1);
    tNumList *list1;
    list1 = (tNumList*)malloc(sizeof(tNumList));
    list1->counts = cnt_1;
    list1->pList = (int*)malloc(sizeof(int) * cnt_1);

    int *ori = list1->pList;
    while(cnt_1) {
        
        scanf("%d", list1->pList);
        list1->pList++;
        cnt_1--;
    }
    list1->pList = ori;

    printf("Please enter how many numbers in list2: ");
    scanf("%d", &cnt_2);
    tNumList *list2;
    list2 = (tNumList*)malloc(sizeof(tNumList));
    list2->counts = cnt_2;
    list2->pList = (int*)malloc(sizeof(int) * cnt_2);
    

    ori = list2->pList;

    while(cnt_2) {
        scanf("%d", list2->pList);
        list2->pList++;
        cnt_2--;
    }
    list2->pList = ori;

    printf("sorted list1:  ");
    bubbleSort(list1);

    printf("sorted list2:  ");
    bubbleSort(list2);

    printf("merged list:  ");
    merge(list1, list2);

    return 0;
}

void bubbleSort(tNumList *list){
    int n = list->counts;
    int i,j,k;
    int *p = list->pList;
    for(i=0;i<n;i++){
        for(k=i,j=k+1;j<n;j++)
            if(p[k]>p[j])
                k=j;
        if(k-i)
            j=p[k],p[k]=p[i],p[i]=j;
    }
    
    for(i = 0; i < n; i++) {
        printf("%d ", *p);
        p++;
    }
    printf("\n");
}

void merge(tNumList *list1, tNumList *list2){
    int total = list1->counts + list2->counts;
    int one = list1->counts, two = list2->counts;

    tNumList *listall;
    listall->counts = total;
    listall->pList = (int*)malloc(sizeof(int) * total);
    int *onet = list1->pList, *twot = list2->pList;

    int *ori = listall->pList;
    while(one){
        *listall->pList = *(list1->pList);
        listall->pList++;
        list1->pList++;
        one--;
    }
    list1->pList = onet;
    while(two){
        *listall->pList = *(list2->pList);
        listall->pList++;
        list2->pList++;
        two--;
    }
    list2->pList = twot;

    listall->pList = ori;
    bubbleSort(listall);
}