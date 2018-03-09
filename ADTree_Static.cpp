//
//  ADTree_Static.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "ADTree_Static.hpp"
#include "stdlib.h"
#include <string>
#include "ADTreeVar.h"
#include "datavar.h"
void  deleteVaryTree(ADVaryNode *varynode);
ADVaryNode *mkADVaryNode( int nodeI, int count, int *records );
/*
 nNodes:the account of attribute
 nodeI: the index of node
 count: the sum of records
 dp:the deep length
 
 */
using namespace std;
/*
 nodeI (for ADN):from 0 to n_vars   the Index of first child of varynode(from 0 to n_vars-1 )
 */
ADTreeNode *mkADNode( int nodeI, int count, int *records) {
    int ni;
    ADTreeNode *node = new ADTreeNode[1];
    node->count = count;//记录数目
   // printf("parent1:%d\n,%x",node->count,node);
    node->nChildren = nNodes - nodeI; /* not +1 since we're 0-indexed *///孩子数目
    if(node->nChildren ==0) {
        node->children = (void **)node;
        return node;
    }
    node->children = (void**)new ADVaryNode*[node->nChildren];
    
    /* base case -- nChildren==0 => nothing more to do on this branch */
    for(ni=nodeI; ni<nNodes; ni++ ) {
        node->children[ni-nodeI] = (void*)mkADVaryNode( ni, count, records);
    }
    return node;
}
/*
 nodeI:the index of varynode(from 0 to n_vars-1)
 */

ADVaryNode *mkADVaryNode( int nodeI, int count, int *records ) {
    int ki, ri, maxCount, MCV;
    ADVaryNode *node = new ADVaryNode[1];
    //ADVaryNode *node = (ADVaryNode *)malloc(sizeof(ADVaryNode));
    int **memoryBaton;
    int *memoryBatonLength = new int[arity[nodeI]];
    memset(memoryBatonLength, 0, arity[nodeI]*sizeof(int));
    //memoryBatonLength[arity[nodeI]]={0};
    /*
     memoryBatonLength: 存放同一个value的记录个数
     tempRecordList:每行代表同一value的记录的index(memoryBaton)
     
     */
    for( ri=0; ri<count; ri++ ) {
        int v = (int)data[records[ri]][nodeI];
        tempRecordList[v][memoryBatonLength[v]++] = records[ri];
    }
    MCV = 0;
    maxCount = 0; /* find the MCV */
    for( ki=0; ki<arity[nodeI]; ki++ ) {
        if( memoryBatonLength[ki] > maxCount ) {
            maxCount = memoryBatonLength[ki];
            MCV = ki;
        }
    }
    node->MCV = MCV;
    node->nodeI = nodeI;
    
    /* so that our lists don't get overwritten  by a recursive call
     // can't think of any way around this, but better than "mallocing as we go" (building the lists) */
    memoryBaton = new int*[arity[nodeI]];
    for( ki=0; ki<arity[nodeI]; ki++ ) {
        if( memoryBatonLength[ki]!=0 && ki!=MCV) {
            memoryBaton[ki] = new int[memoryBatonLength[ki]];
            memcpy( memoryBaton[ki], tempRecordList[ki], memoryBatonLength[ki]*sizeof(int) );
        }
    }
    
    node->nChildren = arity[nodeI];
    node->children = (void **)new ADTreeNode*[node->nChildren];
    //node->children = (void **)malloc(node->nChildren*sizeof(ADTreeNode*));
    //memset(node->children, 0, node->nChildren*sizeof( ADTreeNode *) );
    for( ki=0; ki<arity[nodeI]; ki++ ) {
        if( memoryBatonLength[ki]==0 || ki==MCV )
            node->children[ki] = NULL;
        else {
            node->children[ki] = (void*)mkADNode( nodeI+1, memoryBatonLength[ki], memoryBaton[ki] );
            delete [] memoryBaton[ki];
        }
    }
    delete [] memoryBatonLength;
    delete [] memoryBaton;
    
    
    return node;
}
void deleteADTree(ADTreeNode * node){
    //printf("address:%x,flag:%d,rnode:%x\n",varynode,flag,rnode);
   // if(node==NULL) return;
    if(node->nChildren==0){
        delete node;
        return;
    }
    for(int i=0;i<node->nChildren;i++){
        
        deleteVaryTree((ADVaryNode *)node->children[i]);
        
    }
    delete []node->children;
    delete node;
    //free(node->children);
    //free(node);
}
void  deleteVaryTree(ADVaryNode *varynode){
    for(int i=0;i<varynode->nChildren;i++){
        if(varynode->children[i]!=NULL){
            deleteADTree((ADTreeNode *)varynode->children[i]);
        }
    }
    delete []varynode->children;
    delete varynode;
    //free(varynode->children);
    //free(varynode);
}
