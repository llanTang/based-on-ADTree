//
//  inputArg.cpp
//  ADTree
//
//  Created by ustc@tll on 9/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//
#include "recordRead.hpp"
#include "datavar.h"
#include "filRead.hpp"
#include "inputArg.hpp"
#include "readNet.hpp"
#include "IAMB.hpp"
#include<time.h>
void dataInput(){
    char *data_file;
    int numcase;
    char moreData;
    data_file=new char[1000];
    printf("please input the directory of record file:\n");
    scanf("%s",data_file);
    printf("%s",data_file);
    printf("please input the number of records:\n");
    scanf("%d",&numcase);

    preArg(numcase, data_file);
    flag=false;
    delete [] data_file;
    
}

void calMB(){
    char targetCh;
    char *net_file,*mb_file;
    int target;
    prec=0;
    recall=0;
    dis=0;
    printf("please input the incredible level:\n");
    scanf("%lf",&alpha);
    scanf("%c",&targetCh);
    printf("do you want to set the target?\n");
    scanf("%c",&targetCh);
    if(targetCh=='Y'||targetCh=='y'){
        printf("please set the target:\n");
        scanf("%d",&target);
        
    }
    net_file=new char[1000];
    printf("please input the directory of the net:\n");
    scanf("%s",net_file);
    
    mb_file=new char[1000];
    printf("please input the directory of the result file:\n");
    scanf("%s",mb_file);
    srand((unsigned)time(NULL));
    clock_init=clock();
    printf("%s,%s",net_file,mb_file);
    read_net(net_file);
    if(targetCh=='Y'||targetCh=='y'){
        interiamb(target,mb_file);
    }
    else{
        for(target=0;target<n_vars;target++)
            interiamb(target,mb_file);
    }
    prec/=n_vars;
    recall/=n_vars;
    dis/=n_vars;
    printf("prec=%.2f,recall=%.2f,dis=%.2f",prec,recall,dis);
    printf(" time:%f\n",(double)(clock()-clock_init)/CLOCKS_PER_SEC);
    delete [] net_file;
    delete [] mb_file;
   
}
