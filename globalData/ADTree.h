//
//  ADTree.h
//  ADTree
//
//  Created by ustc@tll on 3/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#ifndef ADTree_h
#define ADTree_h

typedef struct ADNode {
    void **children;    /* ADVaryNode */
    int nChildren;
    int count;
} ADTreeNode;

typedef struct  VaryNode{
    void **children;    /* ADTreeNode */
    int nChildren;
    int MCV;
    int nodeI;
} ADVaryNode;

#endif /* ADTree_h */
