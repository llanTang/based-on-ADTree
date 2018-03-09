//
//  recordRead.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "recordRead.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "globaldef.h"

/////////*var*///////////
int *n_states;//the count for every variable
char ***states;//the original value for every variable
int **data;//stores all the records
int n_cases, n_vars, max_max_cond_size;
double alpha;
//n_cases the count of records, n_vars the count of variables
using namespace std;

/////////*function*///////////
void parse_data(char *data_file,bool flag,int casenum);
//read the original file to data
int state_index(int var, char *state);
//find the value corresponding to the original value
int states_init();
int states_del();
//initiate or delete the array states
int nstates_init();
int nstates_del();
//initiate or delete the array n_states
int data_init();
int data_del();
//initiate or delete the array data

/*function name:states_init
 function:initiate the array states which stores the original states value
 */
int states_init(){
    int i,j;
    states=new char**[n_vars];
    for(i=0;i<n_vars;i++)
    {
        states[i]=new char*[(int)MAX_N_STATES];
        for(j=0;j<(int)MAX_N_STATES;j++)
            states[i][j]=new char[(int)MAX_STATE_LENGTH];
    }
    return 1;
}
/*function name:states_del
 function:delete the array states which stores the original states value
 */
int states_del(){
    int i,j;
    for(i=0;i<n_vars;i++)
    {
        for(j=0;j<(int)MAX_N_STATES;j++)
            delete [] states[i][j];
        delete [] states[i];
    }
    
    delete [] states;
    return 1;
}

/*function name:nstates_init
 function:initiate the array  n_states which stores the number of states value
 */
int nstates_init(){
    int i;
    n_states=new int[n_vars];
    for(i=0;i<n_vars;i++)
        n_states[i]=0;
    return 1;
}
/*function name:nstates_del
 function:delete the array  n_states which stores the number of states value
 */
int nstates_del(){
    delete [] n_states;
    return 1;
}

/*function name:data_init
 function:initiate the array  data which stores the record
 */
int data_init(){
    int i;
    data=new int*[n_cases];//记录数据行为属性列为记录
    for(i=0;i<n_cases;i++)
        data[i]=new int[n_vars];
    return 1;
}
/*function name:data_del
 function:delete the array  data which stores the record
 */
int data_del(){
    int i;
    for(i=0;i<n_cases;i++)
        delete [] data[i];
    delete [] data;
    return 1;
}



/*function name:parse_data
 input:
        data_file  data file name
        flag       is the first data stream
 function:read the original file to data
 */
void parse_data(char *data_file,bool flag,int casenum)

{
    int i, j, min_n_states;
    char buffer[(int)MAX_LINE_LENGTH];
    char *token;
    const char *separators=" ,\t\n\r";
    FILE *f_in;

    //if flag is true, this is the first stream of data
    //data_init();
    f_in=fopen(data_file,"r");
    if (!f_in)
    {
        perror("Failed to open file");
        exit(1);
    }
    
    for(i=0;i<casenum;i++)
    {
        fgets(buffer,(int)MAX_LINE_LENGTH,f_in);
        if((int)strlen(buffer)==(int)MAX_LINE_LENGTH-1)
        {
            printf("\n\n Exceeding MAX_LINE_LENGTH. \n\n");
            exit(0);
        }
        
        
        token=strtok(buffer,separators);
        for(j=0;j<n_vars;j++)
        {
            if((int)strlen(token)>(int)MAX_STATE_LENGTH-1)
            {
                printf("\n\n Exceeding MAX_STATE_LENGTH. \n\n");
                exit(0);
            }
            
            data[i][j]=state_index(j,token);
            
            token=strtok(0,separators);
        }
    }
    
    fclose(f_in);
    
    min_n_states=0;
    for(i=0;i<n_vars;i++)
        if(n_states[i]>1 && (min_n_states==0 || n_states[i]<min_n_states))
            min_n_states=n_states[i];
    
    if(min_n_states==0)
    {
        printf("\n\n Only one state for all the variables. \n\n");
        exit(0);
    }
    
    max_max_cond_size=(int)(log((double)n_cases/(double)((int)N_CASES_PER_DF*(min_n_states-1)*(min_n_states-1)))/log((double)min_n_states)); //min_n_states may not be representative.

    //data_del();
  
}

int state_index(int var, char *state)

{int i;
    
    for(i=0;i<n_states[var];i++)
        if(strcmp(states[var][i],state)==0)
            return i;
    
    if(i>(int)MAX_N_STATES-1)
    {
        printf("\n\n Exceeding MAX_N_STATES. \n\n");
        exit(0);
    }
    
    strcpy(states[var][i],state);
    n_states[var]++;
    
    return i;
}
