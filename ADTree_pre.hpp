//
//  ADTree_pre.hpp
//  ADTree
//
//  Created by ustc@tll on 2/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#ifndef ADTree_pre_hpp
#define ADTree_pre_hpp

#include <stdio.h>
#include "ADTree.h"
#include "ADTree_Static.hpp"
#include "ADTree_Sequential.hpp"

ADTreeNode * mkADTree(int *flatData[], int * tarity, int recordsNum, int arityNum,bool flag);
#endif /* ADTree_pre_hpp */
