//
//  ADTree_Sequential.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "ADTree_Sequential.hpp"
#include "ADTreeVar.h"
#include "datavar.h"
#include <string>
//extern  int **newdata;
//extern int **tempRecordList;
//extern int nNodes;

ADTreeNode *CorrectADNode(ADTreeNode *node,int *newRecord,int newRecordsNum);
ADVaryNode * CorrectVaryNode(ADVaryNode *node,int *newRecord,int newRecordsNum);
void ADtreeCorrectMCV(ADTreeNode *node,int nodeI);
void VaryCorrectMCV(ADTreeNode *node,ADVaryNode *varyNode,int nodeI);
ADTreeNode *ADtreeBuildMCV(ADTreeNode *node,ADVaryNode *varyNode,int nodeI);
ADTreeNode *CopyTree(ADTreeNode *node,int nodeI);
ADTreeNode *CopyADNode(ADTreeNode *node);
ADVaryNode *CopyVaryTree(ADVaryNode *varyNode);
ADVaryNode *CopyVaryTree(ADVaryNode *varyNode);
void ADtreeSub(ADTreeNode *nodeA,ADTreeNode *nodeB,int nodeI);
void varySub(ADVaryNode *varyA,ADVaryNode *varyB,ADTreeNode *node,int nodeI);

using namespace std;

ADTreeNode *CorrectADNode(ADTreeNode *node,int *newRecord,int newRecordsNum){
    node->count +=newRecordsNum;
    if(node->nChildren==0) return node;
    for(int i=0;i<node->nChildren;i++){
        //printf("parent:%d,%x,%d\n",node->count,node,((ADVaryNode *)node->children[i])->nodeI);
        CorrectVaryNode((ADVaryNode *)node->children[i], newRecord, newRecordsNum);
    }
    return (ADTreeNode *)node;
}
ADVaryNode * CorrectVaryNode(ADVaryNode *node,int *newRecord,int newRecordsNum){
    // int *memoryRecord;
    int **memoryBaton;
    int *memoryBatonLength= new int[node->nChildren];
    memset(memoryBatonLength, 0, node->nChildren*sizeof(int) );
    for(int i=0;i<newRecordsNum;i++){
        int v = (int)data[newRecord[i]][node->nodeI];
        tempRecordList[v][memoryBatonLength[v]++] = newRecord[i];
    }
    memoryBaton = new int*[node->nChildren];
    for( int ki=0; ki<node->nChildren; ki++ ) {
        //printf("length:%d,%d,%d\n",memoryBatonLength[ki],ki,node->MCV);
        if( memoryBatonLength[ki]!=0 && ki!=node->MCV) {
            memoryBaton[ki] = new int[memoryBatonLength[ki]];
            // memoryBaton[ki] = (int*)malloc(memoryBatonLength[ki]*sizeof(int));
            memcpy( memoryBaton[ki], tempRecordList[ki], memoryBatonLength[ki]*sizeof(int) );
            
        }
    }
    for(int i=0;i<node->nChildren;i++){
        if((i!=node->MCV)&&(memoryBatonLength[i]!=0)){
            if(node->children[i]!=NULL){
                CorrectADNode((ADTreeNode*)node->children[i], memoryBaton[i], memoryBatonLength[i]);
            }
           else{
              // printf("cccccccc\n");
                node->children[i]=mkADNode(node->nodeI+1,memoryBatonLength[i],memoryBaton[i]);
            }
            delete [] memoryBaton[i];
        }
            
    }
    
    delete [] memoryBaton;
    delete []memoryBatonLength;
    return node;
}

void ADtreeCorrectMCV(ADTreeNode *node,int nodeI){
    
    for(int i=0;i<node->nChildren;i++){
            VaryCorrectMCV(node, (ADVaryNode *)node->children[i], i+nodeI);
    }
}
void VaryCorrectMCV(ADTreeNode *node,ADVaryNode *varyNode,int nodeI){
    int oldMCV = node->count;
    int max=0;
    int mm;
    int maxIdx=0;
    if(varyNode->children[varyNode->MCV]!=NULL)
    {
        deleteADTree((ADTreeNode *)varyNode->children[varyNode->MCV]);
        varyNode->children[varyNode->MCV]=NULL;
    }
    //if(varyNode->children[varyNode->MCV]!=NULL)
     //   deleteADTree((ADTreeNode *)varyNode->children[varyNode->MCV]);
    for(int i=0;i<varyNode->nChildren;i++){
        if((varyNode->children[i]!=NULL)&&(i!=varyNode->MCV)){
            oldMCV-=((ADTreeNode *)varyNode->children[i])->count;
        }
    }
    if(oldMCV<=0){
        printf("ccccccccc%d,%d,%d",oldMCV,node->count,varyNode->MCV);
        for(int i=0;i<varyNode->nChildren;i++){
            if((varyNode->children[i]!=NULL)&&(i!=varyNode->MCV))
            printf(",%d,,,,%d",((ADTreeNode *)varyNode->children[i])->count,i);
        }
        printf("\n");
    }
    max=oldMCV;
    maxIdx=varyNode->MCV;
    for(int i=0;i<varyNode->nChildren;i++){
        if((varyNode->children[i]!=NULL)){
            if(((ADTreeNode *)varyNode->children[i])->count>max){
                max=((ADTreeNode *)varyNode->children[i])->count;
                maxIdx=i;
            }
        }
    }
    
    if(oldMCV<max){
        varyNode->children[varyNode->MCV]=ADtreeBuildMCV(node,varyNode,nodeI+1);
        deleteADTree((ADTreeNode *)varyNode->children[maxIdx]);
        varyNode->children[maxIdx]=NULL;
        varyNode->MCV=maxIdx;
    }
    
    for(int i=0;i<varyNode->nChildren;i++){
        if(varyNode->children[i]!=NULL)
            ADtreeCorrectMCV((ADTreeNode *)varyNode->children[i], nodeI+1);
    }
}

ADTreeNode *ADtreeBuildMCV(ADTreeNode *node,ADVaryNode *varyNode,int nodeI){
    ADTreeNode *adnNew;
    int tmpCount = node->count;
    for(int i=0;i<varyNode->nChildren;i++){
        if((varyNode->children[i]!=NULL)&&(i!=varyNode->MCV)){
            tmpCount-=((ADTreeNode *)varyNode->children[i])->count;
        }
    }
    if(tmpCount!=0){
        if(nodeI==nNodes){
            adnNew = new ADTreeNode[1];
            //adnNew=(ADTreeNode *)malloc(sizeof(ADTreeNode));
            adnNew->count=tmpCount;
            adnNew->nChildren=0;
            adnNew->children=(void **)adnNew;
        }
        else{
            adnNew=CopyTree(node, nodeI);
            for(int i=0;i<varyNode->nChildren;i++){
                if((varyNode->children[i]!=NULL)&&(i!=varyNode->MCV)){
                    ADtreeSub(adnNew, (ADTreeNode *)varyNode->children[i], nodeI);
                }
            }
        }
    }
    else adnNew=NULL;
    return adnNew;
}
ADTreeNode *CopyTree(ADTreeNode *node,int nodeI){
    ADTreeNode *adnNew=new ADTreeNode[1];
    //ADTreeNode *adnNew=(ADTreeNode *)malloc(sizeof(ADTreeNode));
    adnNew->count = node->count;
    adnNew->nChildren = nNodes-nodeI;
    adnNew->children=(void**)new ADVaryNode *[nNodes-nodeI];
    // adnNew->children=(void **)malloc((nNodes-nodeI)*sizeof(ADVaryNode *));
    for(int i =nodeI;i<nNodes;i++){
        ADVaryNode *varyNode=(ADVaryNode *)node->children[i-nNodes+node->nChildren];
        adnNew->children[i-nodeI]=CopyVaryTree(varyNode);
    }
    //printf("kkkkkkkkkkkkkkkkkkkkk:%x\n",adnNew,adnNew->count);
    return adnNew;
}
ADTreeNode *CopyADNode(ADTreeNode *node){
    ADTreeNode *adnNew=NULL;
    if(node!=NULL){
        //adnNew=(ADTreeNode *)malloc(sizeof(ADTreeNode));
        adnNew= new ADTreeNode[1];
        adnNew->nChildren=node->nChildren;
        adnNew->count=node->count;
        if(adnNew->nChildren==0)
            adnNew->children=(void **)adnNew;
        else
            adnNew->children=(void **)new ADVaryNode*[node->nChildren];
            //adnNew->children=(void **)malloc(node->nChildren*sizeof(ADVaryNode *));
        for(int i=0;i<node->nChildren;i++){
           // if(node->children[i]!=NULL)
            adnNew->children[i]=CopyVaryTree((ADVaryNode *)node->children[i]);
        }
        //printf("hhhhhhhhhhhhhhhhhhhhhhh:%x,%d\n",adnNew,adnNew->count);
    }
    
    return adnNew;
}
ADVaryNode *CopyVaryTree(ADVaryNode *varyNode){
    ADVaryNode *advNew=NULL;
    if(varyNode!=NULL){
        //advNew=(ADVaryNode *)malloc(sizeof(ADVaryNode));
        advNew = new ADVaryNode[1];
        advNew->MCV=varyNode->MCV;
        advNew->nChildren=varyNode->nChildren;
        advNew->nodeI=varyNode->nodeI;
        advNew->children=(void **)new  ADTreeNode *[varyNode->nChildren];
        //advNew->children=(void **)malloc(varyNode->nChildren*sizeof(ADTreeNode *));
        for(int i =0;i<varyNode->nChildren;i++){
            advNew->children[i]=CopyADNode((ADTreeNode *)varyNode->children[i]);
        }
    }
    //printf("mmmmmmmmmmmmmmmmmmmmmmmm:%x\n",advNew);
    return advNew;
}

void ADtreeSub(ADTreeNode *nodeA,ADTreeNode *nodeB,int nodeI){
   if((nodeB==NULL)||(nodeA==NULL)) return;
    nodeA->count-=nodeB->count;
   // printf("nodeA->count:%d\n",nodeA->count);
    //int cc=nNodes-nodeA->nChildren;
    //if((nodeA->nChildren!=0)&&(nodeB->nChildren!=0)){
        for(int i=0;i<nodeA->nChildren;i++){
            varySub((ADVaryNode *)nodeA->children[i], (ADVaryNode *)nodeB->children[i], nodeB, i+nNodes-nodeA->nChildren);
        }
    //}
}
void varySub(ADVaryNode *varyA,ADVaryNode *varyB,ADTreeNode *node,int nodeI){
  
    //if((varyB==NULL)||(varyA==NULL)||(node==NULL)) return;
    for(int i=0;i<varyA->nChildren;i++){
       // bool flag=false;
        if((varyA->children[i]!=NULL)&&(i==varyB->MCV)){
            varyB->children[i]=ADtreeBuildMCV(node, varyB, nodeI+1);
          //  flag=true;
        }
        if((varyA->children[i]!=NULL)&&(varyB->children[i]!=NULL)){
            if(((ADTreeNode *)varyB->children[i])->count==((ADTreeNode *)varyA->children[i])->count){
                deleteADTree((ADTreeNode *)varyA->children[i]);
                varyA->children[i]=NULL;
            }
            else{
               // printf("varyA->NodeI:%d,varyB->nodeI:%d\n",varyA->nodeI,varyB->nodeI);
                ADtreeSub((ADTreeNode *)varyA->children[i], (ADTreeNode *)varyB->children[i], nodeI+1);
            }
        }
       /* if(flag==true){
            deleteADTree((ADTreeNode *)varyB->children[i]);
            varyB->children[i]=NULL;
        }*/
       
        
    }
}


