/*
+-----------------------------------------------------------+
|                                                           |
|                                                           |
|   this is a procedure to caculate standard deviation.     |
|                                                           |
|   Author:lzs                                              |
|                                                           |
|   wish it can help me from my phsical lab report.         |
|                                                           |
|                                                           |
|                                           ^ v ^           |
|                                                           |
+-----------------------------------------------------------+
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct SNode{
    double *data;//use to stored data
    double  aver;
    double  sum;
    double  std_dev;//标准差
    int cnt;//count of data
};
typedef struct SNode *PtrS;

PtrS Stored_Data(PtrS S){

    printf("Here to print the count of data : ");
    scanf("%d",&(S->cnt));
    S->data=(double *)malloc(sizeof(double)*S->cnt);
    S->sum=0;

    for(int i=0;i<S->cnt;i++){
        printf("Here to print data%d : ",i);
        scanf("%lf",&(S->data[i]));
        S->sum+=S->data[i];
    }

    return S;
}

PtrS Caculate_StdDev (PtrS S){
    double result = 0;

    S->aver=1.0*S->sum/S->cnt;
    for(int i=0;i<S->cnt;i++){
        result+=((S->data[i]-S->aver)*(S->data[i]-S->aver));
    }
    result=1.0*result/(S->cnt-1);
    S->std_dev=sqrt(result);

    return S;
}

int main()
{
    PtrS S=(PtrS)malloc(sizeof(struct SNode));
    S=Stored_Data(S);
    S=Caculate_StdDev(S);
    printf("This group data `s standard deviation is %.6f .\n",S->std_dev);

    return 0;
}