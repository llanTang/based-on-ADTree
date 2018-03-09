//
//  contingencyTable.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "contingencyTable.hpp"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "stdlib.h"



int *query;
int queryLength;
int *arities;
int *result;
int nNodesm;

int **dimMultiplier;
using namespace std;
void mkContab( int queryOffset, ADTreeNode *node, int index );

int * freFunction(ADTreeNode * root,int * tarities,int *queryPtr,int len) {
    /* mkContab( ADTreeRootPtr, queryVars, arities ) */
    
    int maxArity;
    int ci, vi;
    int prod;
    
    
    //double t1, t2;
    
    
    nNodesm = root->nChildren;
    
    
    queryLength = len;
    query=new int[queryLength];
    
    for( ci=0; ci<queryLength; ci ++) {
        query[ci] = (int)queryPtr[ci]; /* 0/1 indexing */
    }
    arities=new int[queryLength];
   
    maxArity = 0;
    
    for( ci=0; ci<queryLength; ci++ ) {
        arities[ci] = (int)tarities[query[ci]];
        if( arities[ci]>maxArity ) maxArity = arities[ci];
    }
    
    prod = 1;
    dimMultiplier=new int*[queryLength];
    for( ci=0; ci<queryLength; ci++ ) {
        dimMultiplier[ci]=new int [arities[ci]];
        for( vi=0; vi<arities[ci]; vi++ ) {
            dimMultiplier[ci][vi] = prod * vi;
        }
        prod *= arities[ci];
    }
    result=new int[prod];
    memset(result, 0, prod*sizeof(int) );
    
    mkContab( 0, root, 0 );
    
    for( ci=0; ci<queryLength; ci++ ) {
        delete []dimMultiplier[ci];
    }
    delete []dimMultiplier;
    
    delete [] arities;
    delete [] query;
    return result;
}

void cleanupContab( int queryOffset, int index, int mcvIndex ) {
    int v;
    
    if( queryOffset==queryLength ) {
        result[mcvIndex] -= result[index];
        return;
    }
    
    for( v=0; v<arities[queryOffset]; v++ ) {
        cleanupContab( queryOffset+1, index + dimMultiplier[queryOffset][v], mcvIndex + dimMultiplier[queryOffset][v] );
    }
}


void mkContab( int queryOffset, ADTreeNode *node, int index ) {
    
    ADVaryNode *varyNode;
    int MCV;
    int v, k;
    //int sum;
    int MCVindex;
    
    if( queryOffset==queryLength ) { /* base case */
        result[index] += node->count;
        return;
    }
    
    /* find the a_i(1) subnode of node */
    //k = 0;
    for( k=0; k<node->nChildren; k++ )
        if( ((ADVaryNode*)node->children[k])->nodeI == query[queryOffset] )
            break;
    
    varyNode = (ADVaryNode*)node->children[k];
    MCV = varyNode->MCV;
    
    /* MCV */
    MCVindex = index + dimMultiplier[queryOffset][MCV];
    mkContab( queryOffset+1, node, MCVindex );
    
    /* recurse */
    for( v=0; v<arities[queryOffset]; v++ ) {
        ADTreeNode *nextNode;
        
        if( v==(MCV) )
            continue;
        
        nextNode = (ADTreeNode*)varyNode->children[v];
        if( nextNode != NULL ) {
            mkContab( queryOffset+1, nextNode, index + dimMultiplier[queryOffset][v] );
            cleanupContab( queryOffset+1, index + dimMultiplier[queryOffset][v], MCVindex );
        }
    }
    
}


