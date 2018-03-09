//
//  datavar.h
//  adTreem
//
//  Created by ustc@tll on 2/3/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#ifndef datavar_h
#define datavar_h
#include <time.h>
extern int *n_states;//the count for every variable

extern char ***states;//the original value for every variable
extern int **data;//stores all the records
extern int n_cases, n_vars, max_max_cond_size;
//n_cases the count of records, n_vars the count of variables
extern double alpha;
extern clock_t clock_init;
extern int **net;
extern double prec;
extern double recall;
extern double dis;
#endif /* datavar_h */
