//
//  main.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include <iostream>
#include "recordRead.hpp"
#include "ADTree_pre.hpp"
#include "IAMB.hpp"
#include "ADTree.h"
#include "ADTree_Static.hpp"
#include "ADTreeVar.h"
#include "datavar.h"
#include "readNet.hpp"
#include <time.h>
using namespace std;
int **net;
char *data_file;
clock_t clock_init;
double prec;
double recall;
double dis;
ADTreeNode *root;
//n_cases the count of records, n_vars the count of variables
int main(int argc, char* argv[]) {
    int i, target;
    
    double dep1;
    char *net_file;
    int *cond1;
    prec=0;
    recall=0;
    dis=0;
    if(argc!=7)
    {
        printf("\n\n Usage: data_file n_cases n_vars target(-1=all) alpha. \n\n");
        exit(0);
    }
    
    data_file=argv[1];//数据文件
    n_cases=atoi(argv[2]);//记录数目
    n_vars=atoi(argv[3]);//属性数目
    
    target=atoi(argv[4]);//目标属性数目
    alpha=atof(argv[5]);//显著水平
    n_states=new int[n_vars];//属性的状态数目
    net_file=argv[6];
    
    data_init();
    states_init();
    nstates_init();
    
    printf("starting  to read data.....\n");
    parse_data(data_file,true,n_cases);//read data sets
    
    printf("read data is over...............\n");
    printf("starting  to preform algoirhtms.....\n");
    
    root = mkADTree(data,n_states, n_cases, n_vars,true);
    
    data_del();

    int casenum=1280;
    n_cases+=casenum;
    data_init();
    data_file="/Users/ustctll/Desktop/data10000/1.txt";
    parse_data(data_file, false,casenum);
    mkADTree(data, n_states, casenum, n_vars, false);
    data_del();

    casenum=213;
    n_cases+=casenum;
    data_init();
    data_file="/Users/ustctll/Desktop/data10000/2.txt";
    parse_data(data_file, false,casenum);
    mkADTree(data, n_states, casenum, n_vars, false);
    data_del();
    
    cond1=new int[max_max_cond_size];
    
    for(i=0;i<max_max_cond_size;i++)
        
    {cond1[i]=-1;
        
    }
    srand((unsigned)time(NULL));
    clock_init=clock();
    
    read_net(net_file);
    for(target=0;target<n_vars;target++)
     interiamb(target);
    prec/=n_vars;
    recall/=n_vars;
    dis/=n_vars;
    printf("prec=%.2f,recall=%.2f,dis=%.2f",prec,recall,dis);
    
    printf(" time:%f\n",(double)(clock()-clock_init)/CLOCKS_PER_SEC);
    deleteADTree(root);
    for(int i=0;i<n_vars;i++)
        delete [] net[i];
    delete [] net;
    states_del();
    nstates_del();
    delete []cond1;
    return 0;
    
}
