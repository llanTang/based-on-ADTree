//
//  ADTree_pre.cpp
//  ADTree
//
//  Created by ustc@tll on 2/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "ADTree_pre.hpp"
#include "Header.h"
#include <string>
int **tempRecordList; /* CHildnumssk from moore '98 */

int maxArity;
int *arity;
int nNodes, nRecords;
//int **newdata;


using namespace std;
ADTreeNode * mkADTree(int *flatData[], int * tarity, int recordsNum, int arityNum,bool flag){
    int ci,ri;
    int *records;
    nRecords = recordsNum;//记录数目
    nNodes = arityNum;//属性数目
    
    arity = new int[nNodes];//the number of values for every attribute
    
    maxArity = 0;//最多取值的属性数目
    for(ci = 0; ci < nNodes; ci++){
        arity[ci] = (int) tarity[ci];
        if(arity[ci]>maxArity) maxArity = arity[ci];
    }
   /* newdata =new int*[nRecords];
    
    for( ci=0; ci<nRecords; ci++ ) {
        newdata[ci] = flatData[ci];
        
    }*/
    tempRecordList=new int*[maxArity];
    if(tempRecordList == NULL){
        printf("内存申请错误");
        return 0;
    }
    for(ri=0;ri<maxArity;ri++){
        tempRecordList[ri]=new int[nRecords];
        memset(tempRecordList[ri], 0, nRecords*sizeof(int));
    }
    records=new int[nRecords];
    
    for(ri=0;ri<nRecords;ri++)
        records[ri]=ri;
    if(flag==true)
        root = mkADNode(0, nRecords, records);
    else{
        root=CorrectADNode(root, records, nRecords);
        //printf("dfffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
        ADtreeCorrectMCV(root, 0);
    }
    
    for(ri =0 ;ri<maxArity;ri++)
        delete[]tempRecordList[ri];
    delete [] tempRecordList;
    delete [] records;
    delete []arity;
    //delete []newdata;
    return root;
    
}
