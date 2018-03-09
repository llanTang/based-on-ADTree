//
//  recordRead.hpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#ifndef recordRead_hpp
#define recordRead_hpp
#include <stdio.h>
//#include "datavar.h"
void parse_data(char *data_file,bool flag,int casenum);
int data_init();
int data_del();
int states_init();
int states_del();
//initiate or delete the array states
int nstates_init();
int nstates_del();
#endif /* recordRead_hpp */
