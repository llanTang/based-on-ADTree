//
//  filRead.cpp
//  ADTree
//
//  Created by ustc@tll on 6/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "filRead.hpp"
#include "datavar.h"
#include "recordRead.hpp"
#include "ADTree_pre.hpp"
void preArg(int casenum,char *data_file){
    n_cases+=casenum;
    data_init();
    parse_data(data_file, casenum);
    mkADTree(data, n_states, casenum, n_vars,flag);
    data_del();
}
