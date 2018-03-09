//
//  ADTree_Sequential.hpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#ifndef ADTree_Sequential_hpp
#define ADTree_Sequential_hpp

#include <stdio.h>
#include "ADTree.h"
#include "ADTree_Static.hpp"

ADTreeNode *CorrectADNode(ADTreeNode *node,int *newRecord,int newRecordsNum);
void ADtreeCorrectMCV(ADTreeNode *node,int nodeI);
#endif /* ADTree_Sequential_hpp */
