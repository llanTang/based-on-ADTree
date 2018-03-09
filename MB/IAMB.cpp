//
//  IAMB.cpp
//  ADTree
//
//  Created by ustc@tll on 28/2/18.
//  Copyright © 2018 ustc@tll. All rights reserved.
//

#include "IAMB.hpp"
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include<algorithm>
#include "globaldef.h"
#include "datavar.h"
#include "testRep.hpp"
//#include "ADTree.h"
extern int n_vars,max_max_cond_size，n_cases;
extern int *n_states;
extern ADTreeNode *root;
extern double alpha;

int k_greedy(double *dep);
double compute_dep(int var, int target, int *cond);
int search_element(int *querArry,int len, int element,int *dex);

using namespace std;
void interiamb(int target)

//interIAMB(target).

{int i, j, k, stop, stop2, n_conds, aux;
    int *pc, *mb, *removals, *cond;
    double *dep;
  
    pc=new int[n_vars];        //the set of parent and children
    mb=new int[n_vars];       //the set of PC and spouse
    removals=new int[n_vars];
    
    /*Initiate:
     if this isn't an element of MB , then set mb array -1
     or else set 0;
     all pc,removals are equal to 0;
     */
    for(i=0;i<n_vars;i++)
    {pc[i]=0;
        if(n_states[i]>1 && n_states[target]>1)
            mb[i]=0;
        else
            mb[i]=-1;
        removals[i]=0;
    }
    mb[target]=-1;
    
    n_conds=0;
    cond=new int[max_max_cond_size+1];
    for(i=0;i<max_max_cond_size+1;i++)
        cond[i]=-1;
    
    dep=new double[n_vars];
    
    /*for the forward phase of IAMB algorithm, we stop until MB set won't
     change;
     for the backward, we check out every element of candidate of mb.
     */
    do
    {stop=1;
        
        if(n_conds<=max_max_cond_size)
        {
            for(i=0;i<n_vars;i++)
                dep[i]=(double)0.0;//dep array stores dependence
            
            for(i=0;i<n_vars;i++)
                if(mb[i]==0)
                {
                    //printf("%d\n",i);
                    dep[i]=compute_dep(i,target,cond);
                    //printf("stp1:%d,%f\n",i,dep[i]);
                    if(dep[i]>=(double)1.0)
                        stop=0;
                }
        }
        
        if(stop==0)
        {aux=k_greedy(dep);
            
            mb[aux]=1;
            cond[n_conds]=aux;
            n_conds++;
            
            //printf("\n Adding %d with dependence %.2f",aux,dep[aux]);
        }
        else
            do
            {stop2=1;
                
                for(i=0;i<n_vars;i++)
                    dep[i]=(double)0.0;
                
                for(i=0;i<n_vars;i++)
                    if(mb[i]==1 && removals[i]<10)
                    {
                        for(j=0;j<n_conds;j++)
                            if(cond[j]==i)
                            {
                                for(k=j;k<n_conds-1;k++)
                                    cond[k]=cond[k+1];
                                cond[n_conds-1]=-1;
                                
                                j=n_conds;
                            }
                        
                        dep[i]=compute_dep(i,target,cond);
                        //printf("stp2:%d,%f\n",i,dep[i]);
                        cond[n_conds-1]=i;
                        
                        if(dep[i]<=(double)(-1.0))
                        {
                            dep[i]=(double)1.0;
                            stop=0;
                            stop2=0;
                        }
                        else
                            dep[i]=(double)0.0;
                    }
                
                if(stop2==0)
                {
                    aux=k_greedy(dep);
                    
                    mb[aux]=0;
                    removals[aux]++; //To avoid endless loop.
                    for(j=0;j<n_conds;j++)
                        if(cond[j]==aux)
                        {for(k=j;k<n_conds-1;k++)
                            cond[k]=cond[k+1];
                            cond[n_conds-1]=-1;
                            
                            j=n_conds;
                        }
                    n_conds--;
                    
                    //printf("\n Removing %d",aux);
                }
            }
        while(stop2==0);
    }
    while(stop==0);
    

    
    for(i=0;i<n_vars;i++)
        if(mb[i]==-1)
            mb[i]=0;
     for(i=0;i<n_vars;i++)
     if(mb[i]==1)
     printf(" %d ",i);
    report(target, mb);
    delete [] pc;
    delete [] mb;
    delete [] removals;
    delete [] cond;
    delete [] dep;
}

//calculate the dependence
double compute_dep(int var, int target, int *cond)

{int i, n_cond_states,  df, df_first, df_second;
    double statistic, dep, aux;
    int *ss_cond;
    int *ss_first, *ss_second;
    int *ss;
    int first,second;
    int part_one,part_two,part_three,part_four,part_five;
    int first_part,second_part;
    int index=0;
    
    n_cond_states=1;
    for(i=0;i<max_max_cond_size;i++)
        if(cond[i]!=-1)
            n_cond_states=n_cond_states*n_states[cond[i]];
    if(n_cond_states*(n_states[target]-1)*(n_states[var]-1)*(int)N_CASES_PER_DF>n_cases)
    {
        return (double)0.0;
    }
    //n_cond_states stores the number
    int num_cond_states=0;
    for(i=0;i<max_max_cond_size;i++)
        if(cond[i]!=-1)
        {
            // printf(",%d",cond[i]);
            num_cond_states++;
        }
    
    //printf(",,,,,%d,%d",var,target);
    
    
    int * quer=(int *)malloc(sizeof(int)*(num_cond_states+2));
    //int queryIndex=0;
    for(int i=0;i<num_cond_states;i++)
        quer[i]=cond[i];//add all condition to quer set
    if(var<target){
        first=var;
        second=target;
    }
    else{
        first=target;
        second=var;
    }
    
    quer[num_cond_states]=first;
    quer[num_cond_states+1]=second;
    sort(quer,quer+num_cond_states,less<double>());//sort the quer set
    ss_cond=freFunction(root,n_states,quer,num_cond_states);//the contingency table of all condition elements
    
    //calculate the contingency table of all condition elements and first
    sort(quer,quer+num_cond_states+1,less<double>());
    ss_first=freFunction(root,n_states,quer,num_cond_states+1);
    
    //search for the first element
    int first_part_two=search_element(quer,num_cond_states+1, first,&index);
    
    quer[index]=second;
    //calculate the contingency table of all condition elements and second
    sort(quer,quer+num_cond_states+1,less<double>());
    ss_second=freFunction(root,n_states,quer,num_cond_states+1);
    
    //search for the second element
    int second_part_two=search_element(quer, num_cond_states+1, second,&index);
    
    //calculate the contingency table of all condition elements and var and target
    quer[num_cond_states+1]=first;
    sort(quer,quer+num_cond_states+2,less<double>());
    
    ss=freFunction(root,n_states,quer,num_cond_states+2);
    
    if(quer!=NULL) free(quer);
    
    //calculate all parts when put target and var into sets
    part_one=first_part_two/n_states[first];
    part_two=second_part_two*n_states[first]/n_states[second];
    part_three=part_two/first_part_two;
    part_four=second_part_two*n_states[first];
    part_five=n_cond_states*n_states[second]/second_part_two;
    first_part=first_part_two/n_states[first];
    second_part=second_part_two/n_states[second];
    
    //G^2 statistic based on observed and expected frequencies.
    
    statistic=(double)0.0;
    
    for(int i=0;i<part_one;i++)
        for(int j=0;j<part_three;j++)
            for(int k=0;k<part_five;k++)
                if(ss_cond[k*second_part+j*first_part+i]>0)
                    for(int m=0;m<n_states[first];m++)
                        if(ss_first[k*part_two+j*first_part_two+m*part_one+i]>0)
                            for(int n=0;n<n_states[second];n++)
                                if(ss[k*part_four+n*part_two+j*first_part_two+m*part_one+i]>0)
                                {
                                    aux=(double)(ss_first[k*part_two+j*first_part_two+m*part_one+i]*ss_second[k*second_part_two+n*second_part+j*part_one+i])/(double)(ss_cond[k*second_part+j*first_part+i]);
                                    statistic=statistic+(double)ss[k*part_four+n*part_two+j*first_part_two+m*part_one+i]*(log((double)ss[k*part_four+n*part_two+j*first_part_two+m*part_one+i])-log(aux));
                                    //printf("%f %f\n",aux,statistic);
                                }
    
    statistic=statistic*(double)2.0;
    
    
    //Reduced df due to zero marginals.
    
    df=0;
    
    for(int i=0;i<part_one;i++)
        for(int j=0;j<part_three;j++)
            for(int k=0;k<part_five;k++)
                if(ss_cond[k*second_part+j*first_part+i]>0){
                    df_first=0;
                    for(int m=0;m<n_states[first];m++)
                        if(ss_first[k*part_two+j*first_part_two+m*part_one+i]>0)
                            df_first++;
                    df_second=0;
                    for(int n=0;n<n_states[second];n++)
                        if(ss_second[k*second_part_two+n*second_part+j*part_one+i]>0)
                            df_second++;
                    df+=(df_first-1)*(df_second-1);
                }
    delete [] ss_cond;
    delete [] ss_first;
    delete [] ss_second;
    delete [] ss;
    
    
    
    if(statistic<(double)0.0) //statistic sometimes takes values -0.0. Due to loss of precision ?
        statistic=(double)0.0;
    
    if(df<=0) //Naive ?
        df=1;
    
    dep=gammq((double)0.5*(double)df,(double)0.5*statistic);
    
    if(dep<(double)0.0) //Just in case.
        dep=(double)0.0;
    else
        if(dep>(double)1.0)
            dep=(double)1.0;
    
    if(dep<=alpha)
    {dep=(double)2.0-dep;
        
        if(dep==(double)2.0)
            dep=(double)2.0+statistic/(double)df;
        
        return dep;
    }
    else
    {dep=(double)(-1.0)-dep;
        
        if(dep==(double)(-2.0))
            dep=(double)(-2.0)-statistic/(double)df;
        
        return dep;
    }
}

int search_element(int *querArry,int len, int element,int *dex){
    int before_element_states=1;
    for(int i=0;i<len;i++){
        before_element_states*=n_states[*(querArry+i)];
        if(*(querArry+i)==element){
            *dex=i;
            return before_element_states;
        }
    }
    return before_element_states;
}
int k_greedy(double *dep)

//k-greedy (maximization) over the nodes with dep[] >= 1.0.
//It returns the index of the maximum.

{int i, j, k, n_cands, n_cands_left, max;
    int *cand;
    
    n_cands=0;
    for(i=0;i<n_vars;i++)
        if(dep[i]>=(double)1.0)
            n_cands++;
    
    cand=new int[n_cands];
    
    j=0;
    for(i=0;i<n_vars;i++)
        if(dep[i]>=(double)1.0)
        {cand[j]=i;
            
            j++;
        }
    
    n_cands_left=n_cands;
    
    n_cands=(int)((double)n_cands*1);
    //n_cands=(int)((double)n_cands*k_tradeoff);
    if(n_cands<1)
        n_cands=1;
    
    for(i=0;i<n_cands;i++)
    {j=rand()%n_cands_left;
        
        //
        if(i==0 || dep[cand[j]]>dep[max])
            max=cand[j];
        
        for(k=j;k<n_cands_left-1;k++)
            cand[k]=cand[k+1];
        
        n_cands_left--;
    }
    
    delete [] cand;
    
    return max;
}


