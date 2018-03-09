//
//  ADTree_Static.hpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#ifndef ADTree_Static_hpp
#define ADTree_Static_hpp

#include <stdio.h>
#include "ADTree.h"

ADTreeNode *mkADNode( int nodeI, int count, int *records) ;
void deleteADTree(ADTreeNode * node);
#endif /* ADTree_Static_hpp */
