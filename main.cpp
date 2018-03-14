//
//  main.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include <iostream>
#include "recordRead.hpp"
//#include "ADTree_pre.hpp"
#include "datavar.h"
#include "ADTree.h"
#include "ADTree_Static.hpp"
#include "inputArg.hpp"
using namespace std;
int **net;

clock_t clock_init;
double prec;
double recall;
double dis;
ADTreeNode *root;
bool flag;
//n_cases the count of records, n_vars the count of variables
int main(int argc, char* argv[]) {
    int orderNum;
    flag=true;
    n_cases=0;
    //dataInput();
    printf("please input the number of variables:\n");
    scanf("%d",&n_vars);
    states_init();
    nstates_init();
    do{
        printf("1.input data  2.calculate MB 3.exit:\n");
        scanf("%d",&orderNum);
        if(orderNum==1) dataInput();
        if(orderNum==2) calMB();
    }while(orderNum!=3);
    
    deleteADTree(root);
    for(int i=0;i<n_vars;i++)
        delete [] net[i];
    delete [] net;
    states_del();
    nstates_del();

    return 0;
    
}
